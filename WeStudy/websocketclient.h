#pragma once
#include <QObject>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>

class WebSocketClient:public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)//自动变化
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)

public:
    explicit WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();

    void setUserId(const QString &userId);
    bool isConnected() const { return m_connected; }
    QString userId() const { return m_userId; }
    //连接信令服务器
    Q_INVOKABLE void connectToServer(const QString &url);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendMessage(const QJsonObject &message);
    // WebRTC信令
    Q_INVOKABLE void sendOffer(const QString &targetId, const QString &sdp);
    Q_INVOKABLE void sendAnswer(const QString &targetId, const QString &sdp);
    Q_INVOKABLE void sendIceCandidate(const QString &targetId, const QString &candidate);


    Q_INVOKABLE void createRoom(const QString &roomName, int maxParticipants,

                                bool isPrivate,bool videoStatus,bool audioStatus,const QString &password=" ");
    Q_INVOKABLE void getRoomList();//请求得到房间列表，展示到大厅，里面有很多房间信息，有对应的响应的操作
    Q_INVOKABLE void joinRoom(const QString &roomId, const QString &password = "");


signals:
    void connectedChanged();
    void userIdChanged();
    void messageReceived(const QJsonObject &message);
    void errorOccurred(const QString &error);
    void participantLeft(const QString &participantId);


    //自习室信号
    void roomCreated(const QString &roomId, const QJsonObject &roomInfo);
    void roomJoined(const QString &roomId, const QJsonObject &roomInfo);

    void roomLeft();
    void roomClosed();

    void roomListReceived(const QJsonArray &rooms);//得到房间列表，直接到MlistView里面处理
    void participantJoined(const QJsonObject &participant);
    //void participantLeft(const QString &participantId);

    // WebRTC信令信号
    void offerReceived(const QString &fromId, const QString &sdp);
    void answerReceived(const QString &fromId, const QString &sdp);
    void iceCandidateReceived(const QString &fromId, const QString &candidate);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);

private:
    void handleMessage(const QJsonObject &message);
    QJsonObject createMessage(const QString &type) const;
    QWebSocket *m_webSocket;
    bool m_connected;
    QString m_userId;//存储该服务器的用户ID，当前用户的唯一标识
    QString m_currentRoomId;//记录当前用户进入的房间号
};
