#ifndef WEBRTCMANAGER_H
#define WEBRTCMANAGER_H

#include <QObject>
#include <QMap>
#include <memory>
#include "rtc/rtc.hpp"

class WebSocketClient;

class WebRTCManager : public QObject
{
    Q_OBJECT

public:
    explicit WebRTCManager(WebSocketClient *signaling, QObject *parent = nullptr);
    ~WebRTCManager();

    Q_INVOKABLE void createPeerConnection(const QString &participantId);
    Q_INVOKABLE void closePeerConnection(const QString &participantId);
    Q_INVOKABLE void closeAllConnections();

    Q_INVOKABLE void startLocalMedia();
    Q_INVOKABLE void stopLocalMedia();
    Q_INVOKABLE bool toggleAudio();
    Q_INVOKABLE bool toggleVideo();

signals:
    void localStreamReady();
    void remoteStreamReady(const QString &participantId);
    void peerConnectionStateChanged(const QString &participantId, const QString &state);
    void errorOccurred(const QString &error);

private slots:
    void handleOffer(const QString &fromId, const QString &sdp);
    void handleAnswer(const QString &fromId, const QString &sdp);
    void handleIceCandidate(const QString &fromId, const QString &candidate);

private:
    struct PeerConnectionData {
        std::shared_ptr<rtc::PeerConnection> pc;
        std::shared_ptr<rtc::Track> videoTrack;
        std::shared_ptr<rtc::Track> audioTrack;
    };

    void setupPeerConnection(const QString &participantId,
                             std::shared_ptr<rtc::PeerConnection> pc);
    void addLocalTracksToConnection(std::shared_ptr<rtc::PeerConnection> pc);

    WebSocketClient *m_signaling;
    QMap<QString, PeerConnectionData> m_peerConnections;

    // 本地媒体流
    std::shared_ptr<rtc::Track> m_localVideoTrack;
    std::shared_ptr<rtc::Track> m_localAudioTrack;
    bool m_audioEnabled;
    bool m_videoEnabled;
    bool m_mediaStarted;

    rtc::Configuration m_config;
};

#endif // WEBRTCMANAGER_H
