#pragma once
#include<QObject>
#include<QWebSocket>
#include<QJsonObject>
#include<rtc/rtc.hpp>
#include<memory>
#include<string>
#include<QPointer>

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

signals:
    void errorOccurred(const QString &error);
    void peerConnectionStateChanged(const QString &participantId, const QString &state);

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
    //上层调用此函数去创建P2P，并初始化上层的participantId
    void addLocalTracksToConnection(std::shared_ptr<rtc::PeerConnection> pc);

    WebSocketClient *m_signaling;
    QMap<QString, PeerConnectionData> m_peerConnections;

    rtc::Configuration m_config;
};
