#include "webrtcManager.h"
#include "websocketclient.h"
#include <QDebug>

WebRTCManager::WebRTCManager(WebSocketClient *signaling, QObject *parent)
    : QObject(parent)
    , m_signaling(signaling)
    , m_audioEnabled(true)
    , m_videoEnabled(true)
    , m_mediaStarted(false)
{
    // 配置STUN服务器
    m_config.iceServers.emplace_back("stun:stun.l.google.com:19302");

    // 连接信令
    connect(m_signaling, &WebSocketClient::offerReceived,
            this, &WebRTCManager::handleOffer);
    connect(m_signaling, &WebSocketClient::answerReceived,
            this, &WebRTCManager::handleAnswer);
    connect(m_signaling, &WebSocketClient::iceCandidateReceived,
            this, &WebRTCManager::handleIceCandidate);
}

WebRTCManager::~WebRTCManager()
{
    closeAllConnections();
    stopLocalMedia();
}

void WebRTCManager::startLocalMedia()
{
    if (m_mediaStarted) {
        return;
    }

    try {
        // 注意：libdatachannel本身不处理媒体捕获
        // 这里需要配合其他库（如FFmpeg、GStreamer等）来捕获音视频
        // 这里只是创建占位符，实际实现需要根据具体需求

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

    m_localVideoTrack.reset();
    m_localAudioTrack.reset();
    m_mediaStarted = false;
    qDebug() << "Local media stopped";
}

bool WebRTCManager::toggleAudio()
{
    m_audioEnabled = !m_audioEnabled;
    // TODO: 实际控制音频track的启用/禁用
    qDebug() << "Audio toggled:" << m_audioEnabled;
    return m_audioEnabled;
}

bool WebRTCManager::toggleVideo()
{
    m_videoEnabled = !m_videoEnabled;
    // TODO: 实际控制视频track的启用/禁用
    qDebug() << "Video toggled:" << m_videoEnabled;
    return m_videoEnabled;
}

void WebRTCManager::createPeerConnection(const QString &participantId)
{
    if (m_peerConnections.contains(participantId)) {
        qDebug() << "Peer connection already exists for:" << participantId;
        return;
    }

    try {
        auto pc = std::make_shared<rtc::PeerConnection>(m_config);
        setupPeerConnection(participantId, pc);

        PeerConnectionData data;
        data.pc = pc;
        m_peerConnections[participantId] = data;

        // 添加本地媒体流
        addLocalTracksToConnection(pc);

        qDebug() << "Creating offer for:" << participantId;

        // 创建offer
        pc->setLocalDescription();

    } catch (const std::exception &e) {
        qWarning() << "Failed to create peer connection:" << e.what();
        emit errorOccurred(QString("Failed to create peer connection: %1").arg(e.what()));
    }
}

void WebRTCManager::setupPeerConnection(const QString &participantId,
                                        std::shared_ptr<rtc::PeerConnection> pc)
{
    // 设置本地描述回调
    pc->onLocalDescription([this, participantId](rtc::Description description) {
        QString sdp = QString::fromStdString(std::string(description));

        if (description.type() == rtc::Description::Type::Offer) {
            qDebug() << "Sending offer to:" << participantId;
            m_signaling->sendOffer(participantId, sdp);
        } else if (description.type() == rtc::Description::Type::Answer) {
            qDebug() << "Sending answer to:" << participantId;
            m_signaling->sendAnswer(participantId, sdp);
        }
    });

    // 设置本地ICE候选回调
    pc->onLocalCandidate([this, participantId](rtc::Candidate candidate) {
        QString candidateStr = QString::fromStdString(std::string(candidate));
        qDebug() << "Sending ICE candidate to:" << participantId;
        m_signaling->sendIceCandidate(participantId, candidateStr);
    });

    // 设置连接状态回调
    pc->onStateChange([this, participantId](rtc::PeerConnection::State state) {
        QString stateStr;
        switch (state) {
        case rtc::PeerConnection::State::New:
            stateStr = "New";
            break;
        case rtc::PeerConnection::State::Connecting:
            stateStr = "Connecting";
            break;
        case rtc::PeerConnection::State::Connected:
            stateStr = "Connected";
            break;
        case rtc::PeerConnection::State::Disconnected:
            stateStr = "Disconnected";
            break;
        case rtc::PeerConnection::State::Failed:
            stateStr = "Failed";
            break;
        case rtc::PeerConnection::State::Closed:
            stateStr = "Closed";
            break;
        }
        qDebug() << "Peer connection state changed:" << participantId << stateStr;
        emit peerConnectionStateChanged(participantId, stateStr);
    });

    // 设置Track回调
    pc->onTrack([this, participantId](std::shared_ptr<rtc::Track> track) {
        qDebug() << "Received track from:" << participantId;

        track->onMessage([participantId](rtc::message_variant message) {
            // 处理接收到的媒体数据
            if (std::holds_alternative<rtc::binary>(message)) {
                auto data = std::get<rtc::binary>(message);
                qDebug() << "Received binary media data from:" << participantId << "size:" << data.size();
            }

        });

        emit remoteStreamReady(participantId);
    });
}

void WebRTCManager::addLocalTracksToConnection(std::shared_ptr<rtc::PeerConnection> pc)
{
    if (!m_mediaStarted) {
        return;
    }

    // TODO: 添加实际的音视频track
    // 这里需要配合实际的媒体捕获实现
}

void WebRTCManager::closePeerConnection(const QString &participantId)
{
    if (!m_peerConnections.contains(participantId)) {
        return;
    }

    auto &data = m_peerConnections[participantId];
    if (data.pc) {
        data.pc->close();
    }

    m_peerConnections.remove(participantId);
    qDebug() << "Closed peer connection for:" << participantId;
}

void WebRTCManager::closeAllConnections()
{
    for (auto it = m_peerConnections.begin(); it != m_peerConnections.end(); ++it) {
        if (it->pc) {
            it->pc->close();
        }
    }
    m_peerConnections.clear();
    qDebug() << "Closed all peer connections";
}

void WebRTCManager::handleOffer(const QString &fromId, const QString &sdp)
{
    qDebug() << "Received offer from:" << fromId;

    try {
        if (!m_peerConnections.contains(fromId)) {
            auto pc = std::make_shared<rtc::PeerConnection>(m_config);
            setupPeerConnection(fromId, pc);

            PeerConnectionData data;
            data.pc = pc;
            m_peerConnections[fromId] = data;

            addLocalTracksToConnection(pc);
        }

        auto &data = m_peerConnections[fromId];
        rtc::Description description(sdp.toStdString(), rtc::Description::Type::Offer);
        data.pc->setRemoteDescription(description);

        // 创建answer会通过onLocalDescription回调自动发送
        data.pc->setLocalDescription();

    } catch (const std::exception &e) {
        qWarning() << "Failed to handle offer:" << e.what();
        emit errorOccurred(QString("Failed to handle offer: %1").arg(e.what()));
    }
}

void WebRTCManager::handleAnswer(const QString &fromId, const QString &sdp)
{
    qDebug() << "Received answer from:" << fromId;

    if (!m_peerConnections.contains(fromId)) {
        qWarning() << "No peer connection found for:" << fromId;
        return;
    }

    try {
        auto &data = m_peerConnections[fromId];
        rtc::Description description(sdp.toStdString(), rtc::Description::Type::Answer);
        data.pc->setRemoteDescription(description);
    } catch (const std::exception &e) {
        qWarning() << "Failed to handle answer:" << e.what();
        emit errorOccurred(QString("Failed to handle answer: %1").arg(e.what()));
    }
}

void WebRTCManager::handleIceCandidate(const QString &fromId, const QString &candidate)
{
    qDebug() << "Received ICE candidate from:" << fromId;

    if (!m_peerConnections.contains(fromId)) {
        qWarning() << "No peer connection found for:" << fromId;
        return;
    }

    try {
        auto &data = m_peerConnections[fromId];
        rtc::Candidate rtcCandidate(candidate.toStdString());
        data.pc->addRemoteCandidate(rtcCandidate);
    } catch (const std::exception &e) {
        qWarning() << "Failed to add ICE candidate:" << e.what();
        emit errorOccurred(QString("Failed to add ICE candidate: %1").arg(e.what()));
    }
}
