//实现rtc会话的管理，管理连接、信令、通道、状态，不负责采集和展示
#include "webrtcmanager.h"
#include "websocketclient.h"
#include "mediacontroller.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaObject>


WebRTCManager::WebRTCManager(WebSocketClient *signaling, MediaController* mediaController,QObject *parent)
    : QObject(parent)
    , m_signaling(signaling)
    ,m_mediaController(mediaController)
    , m_connected(false)
    , m_audioEnabled(true)
    , m_videoEnabled(true)
    , m_mediaStarted(false)
    , m_isOfferer(false)
{
    // 配置STUN服务器
    m_config.iceServers.emplace_back("stun:stun.l.google.com:19302");

     connect(m_mediaController, &MediaController::videoFrameReady, this, &WebRTCManager::onVideoFrameReady);

    // 连接信令服务器的信号
    connect(m_signaling, &WebSocketClient::peerJoined, this, &WebRTCManager::onPeerJoined);
    connect(m_signaling, &WebSocketClient::offerReceived,
            this, &WebRTCManager::handleOffer);
    connect(m_signaling, &WebSocketClient::answerReceived,
            this, &WebRTCManager::handleAnswer);
    connect(m_signaling, &WebSocketClient::iceCandidateReceived,
            this, &WebRTCManager::handleIceCandidate);
    qDebug() << "WebRTCManager created succsessfully";
}

WebRTCManager::~WebRTCManager()
{
    closePeerConnection();
    stopLocalMedia();
}

void WebRTCManager::startLocalMedia()
{

    qDebug() << "";
    if (m_mediaStarted) {
        qDebug() << "Local media already started";
         return;
    }

    if (!m_dataChannelsReady) {
        qDebug() << "DataChannels not ready yet, waiting...";
        return;
    }

    try {
        m_mediaController->startCapture();
        qDebug() << "开始捕获视频帧";
        m_mediaStarted = true;
        emit localStreamReady();
        emit statusChanged("本地已经开始捕获");
    }
    catch (const std::exception &e) {
        qWarning() << "Failed to start local media:" << e.what();
        emit errorOccurred(QString("Failed to start local media: %1").arg(e.what()));
    }
}

void WebRTCManager::stopLocalMedia()
{
    if (!m_mediaStarted) { return; }

    m_mediaController->stopCapture();
    m_mediaStarted = false;
    qDebug() << "Local media stopped";
    emit statusChanged("本地媒体已停止");
}

void WebRTCManager::setupPeerConnection(bool isOfferer)
{
    m_isOfferer = isOfferer;

    if (m_pc) {
        qDebug() << "pc已经存在";
        return;
    }

    try {

        m_pc = std::make_shared<rtc::PeerConnection>(m_config);
        //设置回调函数
        setupCallbacks();

        if (isOfferer) {
             //只有offer方才需要创建datachannel
            qDebug() << "作为offerer初始化，正在创建dc";
            createDataChannels();
            emit statusChanged("正在创建连接...");
        } else {
            qDebug() << "作为ansewerer,正在等待dc";
            emit statusChanged("等待对方连接...");
        }

    } catch (const std::exception &e) {
        qCritical() << "创建pc失败：" << e.what();
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
        QString typeStr = QString::fromStdString(type);

        QMetaObject::invokeMethod(this, [this, sdpStr, typeStr]() {
            if (typeStr == "offer") {
                qDebug() << "Sending offer";
                if (!m_peerId.isEmpty()) {
                    m_signaling->sendOffer(m_peerId, sdpStr);
                } else {
                    qWarning() << "未获取peerId，无法发送 Offer";
                }
                emit statusChanged("已发送Offer");
            } else if (typeStr == "answer") {
                qDebug() << "Sending answer";
                if (!m_peerId.isEmpty()) {
                    m_signaling->sendAnswer(m_peerId, sdpStr);
                } else {
                    qWarning() << "未获取peerId，无法发送 Answer";
                }
                emit statusChanged("已发送Answer");
            }
        }, Qt::QueuedConnection);
    });

    // 本地ICE候选回调
    m_pc->onLocalCandidate([this](rtc::Candidate cand) {
        std::string candidate = std::string(cand);

        qDebug() << "ICE候选生成";

        QString candidateStr = QString::fromStdString(candidate);

        QMetaObject::invokeMethod(this, [this, candidateStr]() {
            if (!m_peerId.isEmpty()) {
                m_signaling->sendIceCandidate(m_peerId, candidateStr);
            } else {
                qWarning() << "未获取peerId，无法发送 iceCandidate";
            }
        }, Qt::QueuedConnection);
    });

    // 连接状态回调
    m_pc->onStateChange([this](rtc::PeerConnection::State state) {
        QMetaObject::invokeMethod(this, [this, state]() {
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
                qDebug() << "pc已经建立，等待dc...";
                break;
            case rtc::PeerConnection::State::Disconnected:
                stateStr = "Disconnected";
                m_connected = false;
                m_dataChannelsReady = false;
                stopLocalMedia();
                emit connectedChanged();
                emit statusChanged("WebRTC连接已断开");
                break;
            case rtc::PeerConnection::State::Failed:
                stateStr = "Failed";
                m_connected = false;
                m_dataChannelsReady = false;
                stopLocalMedia();
                emit connectedChanged();
                emit statusChanged("WebRTC连接失败");
                emit errorOccurred("WebRTC连接失败");
                break;
            case rtc::PeerConnection::State::Closed:
                stateStr = "Closed";
                m_connected = false;
                m_dataChannelsReady = false;
                stopLocalMedia();
                emit connectedChanged();
                emit statusChanged("WebRTC连接已关闭");
                break;
            }

            qDebug() << "连接状态:" << stateStr;
            emit peerConnectionStateChanged(stateStr);
        }, Qt::QueuedConnection);
    });

    // 数据通道回调（answerer接收）
    if (!m_isOfferer) {
        m_pc->onDataChannel([this](std::shared_ptr<rtc::DataChannel> dc) {
            std::string label = dc->label();
            qDebug() << "收到数据通道:" << QString::fromStdString(label);

        QMetaObject::invokeMethod(this, [this, dc, label]() {
                qDebug() << "收到数据通道:" << QString::fromStdString(label);

                if (label == "video") {
                    m_videoChannel = dc;
                    setupDataChannelCallbacks(dc, label);
                } else if (label == "audio") {
                    m_audioChannel = dc;
                    setupDataChannelCallbacks(dc, label);
                }
            }, Qt::QueuedConnection);
        });
    }
}

void WebRTCManager::createDataChannels()
{
    try {
        // 创建视频数据通道
        m_videoChannel = m_pc->createDataChannel("video");
        setupDataChannelCallbacks(m_videoChannel, "video");

        // 创建音频数据通道，不使用音频通道进行发送
        m_audioChannel = m_pc->createDataChannel("audio");
        setupDataChannelCallbacks(m_audioChannel, "audio");

        qDebug() << "Data channels created";
    } catch (const std::exception &e) {
        qDebug() << "创建数据通道失败:" << e.what();
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
        //切换到主线程中执行
        QMetaObject::invokeMethod(this, [this, labelStr]() {
            qDebug() << "数据通道已打开:" << labelStr;

            bool videoReady = m_videoChannel && m_videoChannel->isOpen();
            bool audioReady = m_audioChannel && m_audioChannel->isOpen();

            qDebug() << "视频通道:" << videoReady << "音频通道：" << audioReady;

            if (videoReady && audioReady) {
                m_dataChannelsReady = true;
                qDebug() << "所有数据通道已打开";
                emit statusChanged("视频通话已建立");
                emit remoteStreamReady();
                startLocalMedia();
            }
        }, Qt::QueuedConnection);
    });

    // 通道关闭回调
    dc->onClosed([this, labelStr]() {
        QMetaObject::invokeMethod(this, [this, labelStr]() {
            qDebug() << "数据通道已关闭:" << labelStr;
            m_dataChannelsReady = false;
            stopLocalMedia();
            m_connected = false;
            emit connectedChanged();
            emit statusChanged("连接已断开");
        }, Qt::QueuedConnection);
    });

    // 消息接收回调
    dc->onMessage([this, label](auto data) {
        {
            if (std::holds_alternative<std::vector<std::byte>>(data)) {
                auto bytes = std::get<std::vector<std::byte>>(data);
                // 复制数据，避免生命周期问题
                QByteArray qdata(reinterpret_cast<const char *>(bytes.data()),
                                 static_cast<int>(bytes.size()));

                QMetaObject::invokeMethod(this, [this, label, qdata]() {
                    qDebug() << "DataChannel 收到消息，通道:" << QString::fromStdString(label);
                    qDebug() << "消息大小:" << qdata.size() << "字节";

                    if (label == "video") {
                        qDebug() << "这是视频数据";
                        qDebug() << "mediaController正在处理收到的视频";
                        m_mediaController->videoRecived(qdata);
                        qDebug() << "处理完成";
                    } else if (label == "audio") {
                        //todo
                    }
                }, Qt::QueuedConnection);
            } else if (std::holds_alternative<std::string>(data)) {
                auto str = std::get<std::string>(data);
                QString qstr = QString::fromStdString(str);

                // ✅ 切换到主线程执行
                QMetaObject::invokeMethod(this, [qstr]() {
                    qDebug() << "消息类型: string:" << qstr;
                }, Qt::QueuedConnection);
            }
        }
    });

    // 错误回调
    dc->onError([this, labelStr](const std::string &error) {
        qDebug() << "数据通道错误:" << labelStr << QString::fromStdString(error);
    });
}

//关闭pc
void WebRTCManager::closePeerConnection()
{
    stopLocalMedia();

    if (m_pc) {
        m_pc->close();
        m_pc.reset();
    }

    m_videoChannel.reset();
    m_audioChannel.reset();

    m_connected = false;
    m_dataChannelsReady = false;
    emit connectedChanged();

    qDebug() << "pc连接已关闭";
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
        qDebug() << "offer已设置到本地";
        emit statusChanged("已接收Offer，正在创建Answer");
    } catch (const std::exception &e) {
        qDebug() << "设置远程描述失败:" << e.what();
        emit errorOccurred(QString("处理Offer失败: %1").arg(e.what()));
    }
}

//处理answer

void WebRTCManager::handleAnswer(const QString &fromId, const QString &sdp)
{
    qDebug() << "Received answer from:" << fromId;
    if (!m_pc) {
        qDebug() << "No peer connection found";
        return;
    }

    try {

        rtc::Description answer(sdp.toStdString(), rtc::Description::Type::Answer);
        m_pc->setRemoteDescription(answer);

        emit statusChanged("已接收Answer");

    } catch (const std::exception &e) {
       qDebug()<< "设置远程描述失败:" << e.what();
        emit errorOccurred(QString("处理Answer失败: %1").arg(e.what()));

    }
}

void WebRTCManager::handleIceCandidate(const QString &fromId, const QString &candidate)
{
    qDebug() << "Received ICE candidate from:" << fromId;


    if (!m_pc) {
        qDebug()<< "No peer connection found";
        return;
    }

    try {
        rtc::Candidate rtcCandidate(candidate.toStdString());
        m_pc->addRemoteCandidate(rtcCandidate);

    } catch (const std::exception &e) {
       qDebug() << "添加ICE候选失败:" << e.what();
    }
}

void WebRTCManager::onvideoFrameReady(const QByteArray &data)
{
    sendVideo(data);
}






void WebRTCManager::sendVideo(const QByteArray &data)
{
    if (!m_videoEnabled || !m_connected || !m_dataChannelsReady || !m_videoChannel || !m_videoChannel->isOpen()) {
        return;
    }

    try {
        std::vector<std::byte> bytes(data.size());
        std::memcpy(bytes.data(), data.data(), data.size());
        m_videoChannel->send(bytes);
    } catch (const std::exception &e) {
        qWarning() << "发送视频异常:" << e.what();
    }
}

void WebRTCManager::sendAudio(const QByteArray &data)
{
   //toto
}


void WebRTCManager::onVideoFrameReady(const QByteArray &data)
{
    qDebug() << "捕获到视频帧，大小为" << data.size() << "字节";
    sendVideo(data);
}

void WebRTCManager::onVideoReceived(const QByteArray &data)
{
    qDebug() << "收到远程视频帧，正在处理";
    if (data.isEmpty()) {
        qDebug() << "空视频数据";
        return;
    }

    qDebug() << "收到远程视频，大小为:" << data.size() << "字节";
    m_mediaController->videoRecived(data);
}

void WebRTCManager::onPeerJoined(const QString &peerId)
{
    qDebug() << "收到 peerJoined 信号";
    m_peerId = peerId;
    qDebug() << "m_peerId 已设置为:" << m_peerId;
    qDebug() << "m_isOfferer =" << m_isOfferer << "(应该是 true)";

    if (m_isOfferer && !m_pc) {
        qDebug() << "房主创建pc并发送 Offer";
        setupPeerConnection(true);
    } else if (m_pc) {
        qDebug() << "pc已存在，无需重复创建";
    }
}

void WebRTCManager::onRoomJoined(const QString &roomId, const QJsonObject &roomInfo)
{
    qDebug() << "Room joined, roomId:" << roomId << ", I am ANSWERER";
}

void WebRTCManager::onRoomCreated(const QString &roomId, const QJsonObject &roomInfo)
{
    m_isOfferer = true;
    qDebug() << "Room created, roomId:" << roomId << ", I am OFFERER";
}

