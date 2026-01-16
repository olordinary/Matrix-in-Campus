
//实现rtc会话的管理，管理连接、信令、通道、状态，不负责采集和展示
#include "webrtcManager.h"
#include "websocketclient.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

WebRTCManager::WebRTCManager(WebSocketClient *signaling, QObject *parent)
    : QObject(parent)
    , m_signaling(signaling)
    , m_connected(false)
    , m_audioEnabled(true)
    , m_videoEnabled(true)
    , m_mediaStarted(false)
    , m_isOfferer(false)
{
    // 配置STUN服务器
    m_config.iceServers.emplace_back("stun:stun.l.google.com:19302");

    // 连接信令服务器的信号
    connect(m_signaling, &WebSocketClient::offerReceived,
            this, &WebRTCManager::handleOffer);
    connect(m_signaling, &WebSocketClient::answerReceived,
            this, &WebRTCManager::handleAnswer);
    connect(m_signaling, &WebSocketClient::iceCandidateReceived,
            this, &WebRTCManager::handleIceCandidate);
}

WebRTCManager::~WebRTCManager()
{

    stopLocalMedia();
}

void WebRTCManager::startLocalMedia()
{
    if (m_mediaStarted) {

        return;
    }

    try {

        qDebug() << "Local media started";
        m_mediaStarted = true;
        emit localStreamReady();
    }
    catch (const std::exception &e) {
        qWarning() << "Failed to start local media:" << e.what();
        emit errorOccurred(QString("Failed to start local media: %1").arg(e.what()));

    }
}

void WebRTCManager::stopLocalMedia()
{
    if (!m_mediaStarted) {
        return;
    }

    m_mediaStarted = false;
    qDebug() << "Local media stopped";
    emit statusChanged("本地媒体已停止");
}

//逻辑层的音视频开关，不管理实际的设备，而是停止发送
bool WebRTCManager::toggleAudio()
{
    m_audioEnabled = !m_audioEnabled;
    qDebug() << "Audio toggled:" << m_audioEnabled;
    emit audioStateChanged();
    emit statusChanged(m_audioEnabled ? "音频已启用" : "音频已禁用");
    return m_audioEnabled;
}

bool WebRTCManager::toggleVideo()
{
    m_videoEnabled = !m_videoEnabled;
    qDebug() << "Video toggled:" << m_videoEnabled;
    emit videoStateChanged();
    emit statusChanged(m_videoEnabled ? "视频已启用" : "视频已禁用");
    return m_videoEnabled;
}

void WebRTCManager::setupPeerConnection(bool isOfferer)
{
    m_isOfferer = isOfferer;

    if (m_pc) {
        return;
    }

    try {

        m_pc = std::make_shared<rtc::PeerConnection>(m_config);
        setupCallbacks();

        if (isOfferer) {
            qDebug() << "Setting up as offerer, creating data channels";
            //只有offer方才需要创建datachannel
            createDataChannels();
            emit statusChanged("正在创建连接...");
        } else {
            qDebug() << "Setting up as answerer, waiting for data channels";
            emit statusChanged("等待对方连接...");
        }

    } catch (const std::exception &e) {
        qCritical() << "Failed to create peer connection:" << e.what();
        emit errorOccurred(QString("创建连接失败: %1").arg(e.what()));
    }
}


//设置回调函数 监听sdp、ice、dc以及pc的状态
void WebRTCManager::setupCallbacks()
{
    // 本地SDP描述回调
    m_pc->onLocalDescription([this](rtc::Description desc) {
        std::string sdp = std::string(desc);
        std::string type = desc.typeString();

        qDebug() << "本地描述生成:" << QString::fromStdString(type);

        QString sdpStr = QString::fromStdString(sdp);

        if (desc.type() == rtc::Description::Type::Offer) {
            qDebug() << "Sending offer";
            // 发送offer到对方，这里需要知道对方的ID
            if (!m_peerId.isEmpty()) {
                m_signaling->sendOffer(m_peerId, sdpStr);
            }
            emit statusChanged("已发送Offer");
        } else if (desc.type() == rtc::Description::Type::Answer) {
            qDebug() << "Sending answer";
            if (!m_peerId.isEmpty()) {
                m_signaling->sendAnswer(m_peerId, sdpStr);
            }
            emit statusChanged("已发送Answer");
        }
    });

    // 本地ICE候选回调
    m_pc->onLocalCandidate([this](rtc::Candidate cand) {
        std::string candidate = std::string(cand);

        qDebug() << "ICE候选生成";

        QString candidateStr = QString::fromStdString(candidate);

        if (!m_peerId.isEmpty()) {
            m_signaling->sendIceCandidate(m_peerId, candidateStr);
        }
    });

    // 连接状态回调
    m_pc->onStateChange([this](rtc::PeerConnection::State state) {
        QString stateStr;
        switch (state) {
        case rtc::PeerConnection::State::New:
            stateStr = "New";
            emit statusChanged("连接状态: 新建");
            break;
        case rtc::PeerConnection::State::Connecting:
            stateStr = "Connecting";
            emit statusChanged("连接状态: 正在连接");
            break;
        case rtc::PeerConnection::State::Connected:
            stateStr = "Connected";
            m_connected = true;
            emit connectedChanged();
            emit statusChanged("WebRTC连接已建立");
            break;
        case rtc::PeerConnection::State::Disconnected:
            stateStr = "Disconnected";
            m_connected = false;
            emit connectedChanged();
            emit statusChanged("WebRTC连接已断开");
            break;
        case rtc::PeerConnection::State::Failed:
            stateStr = "Failed";
            m_connected = false;
            emit connectedChanged();
            emit statusChanged("WebRTC连接失败");
            emit errorOccurred("WebRTC连接失败");
            break;
        case rtc::PeerConnection::State::Closed:
            stateStr = "Closed";
            m_connected = false;
            emit connectedChanged();
            emit statusChanged("WebRTC连接已关闭");
            break;
        }

        qDebug() << "连接状态:" << stateStr;
        emit peerConnectionStateChanged(stateStr);
    });

    // 数据通道回调（answerer接收）
    if (!m_isOfferer) {
        m_pc->onDataChannel([this](std::shared_ptr<rtc::DataChannel> dc) {
            std::string label = dc->label();
            qDebug() << "收到数据通道:" << QString::fromStdString(label);

            if (label == "video") {
                m_videoChannel = dc;
                setupDataChannelCallbacks(dc, label);
            } else if (label == "audio") {
                m_audioChannel = dc;
                setupDataChannelCallbacks(dc, label);
            }
        });
    }
}

void WebRTCManager::createDataChannels()
{
    try {
        // 创建视频数据通道
        m_videoChannel = m_pc->createDataChannel("video");
        setupDataChannelCallbacks(m_videoChannel, "video");

        // 创建音频数据通道
        m_audioChannel = m_pc->createDataChannel("audio");
        setupDataChannelCallbacks(m_audioChannel, "audio");

        qDebug() << "Data channels created";

    } catch (const std::exception &e) {
        qCritical() << "创建数据通道失败:" << e.what();
        emit errorOccurred(QString("创建数据通道失败: %1").arg(e.what()));
    }
}

//设置数据通道回调
void WebRTCManager::setupDataChannelCallbacks(std::shared_ptr<rtc::DataChannel> dc,
                                              const std::string &label)
{
    QString labelStr = QString::fromStdString(label);

    // 通道打开回调
    dc->onOpen([this, labelStr]() {
        qDebug() << "数据通道已打开:" << labelStr;

        // 检查两个通道是否都已打开
        if (m_videoChannel && m_videoChannel->isOpen() &&
            m_audioChannel && m_audioChannel->isOpen()) {
            m_connected = true;
            emit connectedChanged();
            emit statusChanged("视频通话已建立");
            emit remoteStreamReady();
        }
    });

    // 通道关闭回调
    dc->onClosed([this, labelStr]() {
        qDebug() << "数据通道已关闭:" << labelStr;
        m_connected = false;
        emit connectedChanged();
        emit statusChanged("连接已断开");
    });

    // 消息接收回调
    dc->onMessage([this, label](auto data) {
        if (std::holds_alternative<std::vector<std::byte>>(data)) {
            auto bytes = std::get<std::vector<std::byte>>(data);
            QByteArray qdata(reinterpret_cast<const char*>(bytes.data()),
                             static_cast<int>(bytes.size()));

            if (label == "video") {
                emit videoReceived(qdata);
            } else if (label == "audio") {
                emit audioReceived(qdata);
            }
        }
    });

    // 错误回调
    dc->onError([this, labelStr](const std::string &error) {
        qWarning() << "数据通道错误:" << labelStr << QString::fromStdString(error);
    });
}

//关闭pc
void WebRTCManager::closePeerConnection()
{
    if (m_pc) {
        m_pc->close();
        m_pc.reset();
    }

    m_videoChannel.reset();
    m_audioChannel.reset();

    m_connected = false;
    emit connectedChanged();

    qDebug() << "Peer connection closed";
    emit statusChanged("连接已关闭");
}

//收到offer
void WebRTCManager::handleOffer(const QString &fromId, const QString &sdp)
{
    qDebug() << "Received offer from:" << fromId;

    m_peerId = fromId;  // 保存对方ID

    // 作为answerer创建PeerConnection
    if (!m_pc) {
        setupPeerConnection(false);
    }

    try {
        //填写远程sdp——Description(const string &sdp, string typeString);
        rtc::Description offer(sdp.toStdString(), rtc::Description::Type::Offer);
        m_pc->setRemoteDescription(offer);

        emit statusChanged("已接收Offer，正在创建Answer");

    } catch (const std::exception &e) {
        qCritical() << "设置远程描述失败:" << e.what();
        emit errorOccurred(QString("处理Offer失败: %1").arg(e.what()));
    }
}

//处理answer

void WebRTCManager::handleAnswer(const QString &fromId, const QString &sdp)
{
    qDebug() << "Received answer from:" << fromId;


    if (!m_pc) {
        qWarning() << "No peer connection found";

        return;
    }

    try {

        rtc::Description answer(sdp.toStdString(), rtc::Description::Type::Answer);
        m_pc->setRemoteDescription(answer);

        emit statusChanged("已接收Answer");

    } catch (const std::exception &e) {
        qCritical() << "设置远程描述失败:" << e.what();
        emit errorOccurred(QString("处理Answer失败: %1").arg(e.what()));

    }
}

void WebRTCManager::handleIceCandidate(const QString &fromId, const QString &candidate)
{
    qDebug() << "Received ICE candidate from:" << fromId;


    if (!m_pc) {
        qWarning() << "No peer connection found";

        return;
    }

    try {

        rtc::Candidate rtcCandidate(candidate.toStdString());
        m_pc->addRemoteCandidate(rtcCandidate);

    } catch (const std::exception &e) {
        qWarning() << "添加ICE候选失败:" << e.what();
    }
}

void WebRTCManager::onvideoFrameReady(const QByteArray &data)
{
    sendVideo(data);
}

void WebRTCManager::sendVideo(const QByteArray &data)
{
    if (!m_videoEnabled) {
        return;
    }

    if (m_videoChannel && m_videoChannel->isOpen() && m_connected) {
        try {
            std::vector<std::byte> bytes(data.size());
            std::memcpy(bytes.data(), data.data(), data.size());
            m_videoChannel->send(bytes);
        } catch (const std::exception &e) {
            // 静默忽略发送错误，避免日志刷屏
        }
    }
}

void WebRTCManager::sendAudio(const QByteArray &data)
{
    if (!m_audioEnabled) {
        return;
    }

    if (m_audioChannel && m_audioChannel->isOpen() && m_connected) {
        try {
            std::vector<std::byte> bytes(data.size());
            std::memcpy(bytes.data(), data.data(), data.size());
            m_audioChannel->send(bytes);
        } catch (const std::exception &e) {
            // 静默忽略发送错误，避免日志刷屏
        }
    }
}
