#pragma once
#include <QObject>
#include <QByteArray>
#include <rtc/rtc.hpp>
#include <memory>

class WebSocketClient;
class MediaController;

class WebRTCManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(bool audioEnabled READ isAudioEnabled NOTIFY audioStateChanged)
    Q_PROPERTY(bool videoEnabled READ isVideoEnabled NOTIFY videoStateChanged)

public:
    explicit WebRTCManager(WebSocketClient *signaling,MediaController* mediaController, QObject *parent = nullptr);
    ~WebRTCManager();

    bool isConnected() const { return m_connected; }
    bool isAudioEnabled() const { return m_audioEnabled; }
    bool isVideoEnabled() const { return m_videoEnabled; }
    void onRoomCreated(const QString &roomId, const QJsonObject &roomInfo);
    void onRoomJoined(const QString &roomId, const QJsonObject &roomInfo);

    // 媒体控制
    Q_INVOKABLE void startLocalMedia();
    Q_INVOKABLE void stopLocalMedia();
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

private slots:
    void handleOffer(const QString &fromId, const QString &sdp);
    void handleAnswer(const QString &fromId, const QString &sdp);
    void handleIceCandidate(const QString &fromId, const QString &candidate);
    void onvideoFrameReady(const QByteArray &data);
    void onVideoFrameReady(const QByteArray &data);
    void onVideoReceived(const QByteArray &data);
    void onPeerJoined(const QString &peerId);
private:
    void setupCallbacks();
    void createDataChannels();
    void setupDataChannelCallbacks(std::shared_ptr<rtc::DataChannel> dc, const std::string &label);

    WebSocketClient *m_signaling;
    MediaController *m_mediaController;

    //数据传输
    std::shared_ptr<rtc::PeerConnection> m_pc;
    std::shared_ptr<rtc::DataChannel> m_videoChannel;
    std::shared_ptr<rtc::DataChannel> m_audioChannel;

    rtc::Configuration m_config;

    bool m_connected;
    bool m_audioEnabled;
    bool m_videoEnabled;
    bool m_mediaStarted=false;
    bool m_isOfferer=false;
    bool m_peerJoined;
    bool m_dataChannelsReady;

    QString m_peerId;  // 对方的ID
};

