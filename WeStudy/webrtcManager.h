<<<<<<< HEAD
#ifndef WEBRTCMANAGER_H
#define WEBRTCMANAGER_H

#include <QObject>
#include <QMap>
#include <memory>
#include "rtc/rtc.hpp"
=======
#pragma once
#include <QObject>
#include <QByteArray>
#include <rtc/rtc.hpp>
#include <memory>
>>>>>>> bca9fd1 (without mediacapture)

class WebSocketClient;

class WebRTCManager : public QObject
{
    Q_OBJECT
<<<<<<< HEAD
=======
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(bool audioEnabled READ isAudioEnabled NOTIFY audioStateChanged)
    Q_PROPERTY(bool videoEnabled READ isVideoEnabled NOTIFY videoStateChanged)
>>>>>>> bca9fd1 (without mediacapture)

public:
    explicit WebRTCManager(WebSocketClient *signaling, QObject *parent = nullptr);
    ~WebRTCManager();

<<<<<<< HEAD
    Q_INVOKABLE void createPeerConnection(const QString &participantId);
    Q_INVOKABLE void closePeerConnection(const QString &participantId);
    Q_INVOKABLE void closeAllConnections();

=======
    bool isConnected() const { return m_connected; }
    bool isAudioEnabled() const { return m_audioEnabled; }
    bool isVideoEnabled() const { return m_videoEnabled; }

    // 媒体控制
>>>>>>> bca9fd1 (without mediacapture)
    Q_INVOKABLE void startLocalMedia();
    Q_INVOKABLE void stopLocalMedia();
    Q_INVOKABLE bool toggleAudio();
    Q_INVOKABLE bool toggleVideo();

<<<<<<< HEAD
signals:
    void localStreamReady();
    void remoteStreamReady(const QString &participantId);
    void peerConnectionStateChanged(const QString &participantId, const QString &state);
    void errorOccurred(const QString &error);
=======
    // 连接管理
    Q_INVOKABLE void setupPeerConnection(bool isOfferer);
    Q_INVOKABLE void closePeerConnection();

    // 数据发送
    Q_INVOKABLE void sendVideo(const QByteArray &data);
    Q_INVOKABLE void sendAudio(const QByteArray &data);

signals:
    void connectedChanged();
    void audioStateChanged();
    void videoStateChanged();

    void localStreamReady();
    void remoteStreamReady();

    void videoReceived(const QByteArray &data);
    void audioReceived(const QByteArray &data);

    void errorOccurred(const QString &error);
    void statusChanged(const QString &status);
    void peerConnectionStateChanged(const QString &state);
>>>>>>> bca9fd1 (without mediacapture)

private slots:
    void handleOffer(const QString &fromId, const QString &sdp);
    void handleAnswer(const QString &fromId, const QString &sdp);
    void handleIceCandidate(const QString &fromId, const QString &candidate);
<<<<<<< HEAD

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
=======
    void onvideoFrameReady(const QByteArray &data);
private:
    void setupCallbacks();
    void createDataChannels();
    void setupDataChannelCallbacks(std::shared_ptr<rtc::DataChannel> dc, const std::string &label);

    WebSocketClient *m_signaling;
    std::shared_ptr<rtc::PeerConnection> m_pc;
    std::shared_ptr<rtc::DataChannel> m_videoChannel;
    std::shared_ptr<rtc::DataChannel> m_audioChannel;

    rtc::Configuration m_config;

    bool m_connected;
    bool m_audioEnabled;
    bool m_videoEnabled;
    bool m_mediaStarted;
    bool m_isOfferer;

    QString m_peerId;  // 对方的ID
};
>>>>>>> bca9fd1 (without mediacapture)
