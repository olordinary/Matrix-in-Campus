#pragma once
#include<QObject>

class WebSocketClient:public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient();

    // WebRTC信令
    Q_INVOKABLE void sendOffer(const QString &targetId, const QString &sdp);
    Q_INVOKABLE void sendAnswer(const QString &targetId, const QString &sdp);
    Q_INVOKABLE void sendIceCandidate(const QString &targetId, const QString &candidate);


signals:    // WebRTC信令信号
    void offerReceived(const QString &fromId, const QString &sdp);
    void answerReceived(const QString &fromId, const QString &sdp);
    void iceCandidateReceived(const QString &fromId, const QString &candidate);
};
