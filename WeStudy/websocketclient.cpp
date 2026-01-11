#include "websocketclient.h"
#include <QJsonArray>

WebSocketClient::WebSocketClient(QObject *parent)
    : QObject(parent)
    , m_webSocket(new QWebSocket())
    , m_connected(false)
{
    connect(m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    connect(m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &WebSocketClient::onError);
}

void WebSocketClient::setUserId(const QString &userId)
{
    if (m_userId != userId) {
        m_userId = userId;
        emit userIdChanged();
    }
}

void WebSocketClient::connectToServer(const QString &url) {
    qDebug() << "Connecting to:" << url;
    m_webSocket->open(QUrl(url));
}

void WebSocketClient::disconnect() {
    m_webSocket->close();
}

QJsonObject WebSocketClient::createMessage(const QString &type) const
{
    QJsonObject message;
    message["type"] = type;
    message["userId"] = m_userId;
    message["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    return message;
}


void WebSocketClient::sendMessage(const QJsonObject &message)
{
    if (!m_connected) {
        qWarning() << "Not connected to server";
        return;
    }

    QJsonDocument doc(message);
    QString jsonString = doc.toJson(QJsonDocument::Compact);
    m_webSocket->sendTextMessage(jsonString);
}


void WebSocketClient::createRoom(const QString &roomName,
                                 int maxParticipants,
                                 bool isPrivate,
                                 bool videoStatus,
                                 bool audioStatus,
                                 const QString &password)
{
    QJsonObject message = createMessage("createRoom");
    message["roomName"] = roomName;
    message["maxParticipants"] = maxParticipants;
    message["isPrivate"] = isPrivate;
    message["videoStatus"] = videoStatus;
    message["audioStatus"] = audioStatus;
    if (isPrivate && !password.isEmpty()) {
        message["password"] = password;
    }
    sendMessage(message);
}

void WebSocketClient::getRoomList()
{
    QJsonObject message = createMessage("getRoomList");
    sendMessage(message);
}

void WebSocketClient::joinRoom(const QString &roomId, const QString &password)
{
    QJsonObject message = createMessage("joinRoom");
    message["roomId"] = roomId;
    if (!password.isEmpty()) {
        message["password"] = password;
    }
    m_currentRoomId = roomId;
    sendMessage(message);
}

void WebSocketClient::sendOffer(const QString &targetId, const QString &sdp)
{
    QJsonObject message = createMessage("webrtcOffer");
    message["targetId"] = targetId;
    message["sdp"] = sdp;
    sendMessage(message);
}

void WebSocketClient::sendAnswer(const QString &targetId, const QString &sdp)
{
    QJsonObject message = createMessage("webrtcAnswer");
    message["targetId"] = targetId;
    message["sdp"] = sdp;
    sendMessage(message);
}

void WebSocketClient::sendIceCandidate(const QString &targetId, const QString &candidate)
{
    QJsonObject message = createMessage("iceCandidate");
    message["targetId"] = targetId;
    message["candidate"] = candidate;
    sendMessage(message);
}

void WebSocketClient::onConnected()
{
    qDebug() << "Connected to server";
    m_connected = true;
    emit connectedChanged();

    // 注册用户
    QJsonObject message = createMessage("register");
    sendMessage(message);
}

void WebSocketClient::onDisconnected()
{
    qDebug() << "Disconnected from server";
    m_connected = false;
    emit connectedChanged();
}

void WebSocketClient::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) {
        qWarning() << "Invalid JSON message";
        return;
    }

    QJsonObject jsonMessage = doc.object();
    handleMessage(jsonMessage);
}

void WebSocketClient::onError(QAbstractSocket::SocketError error)
{
    QString errorString = m_webSocket->errorString();
    qWarning() << "WebSocket error:" << error << errorString;
    emit errorOccurred(errorString);
}

void WebSocketClient::handleMessage(const QJsonObject &message)
{
    QString type = message["type"].toString();

    emit messageReceived(message);

    if (type == "registered") {
        QString userId = message["userId"].toString();//分配唯一标识当前用户的ID
        setUserId(userId);//用户ID暴露出去
        qDebug() << "Registered with userId:" << userId;
    }
    else if (type == "roomCreated") {
        QString roomId = message["roomId"].toString();
        QJsonObject roomInfo = message["roomInfo"].toObject();
        m_currentRoomId = roomId;
        emit roomCreated(roomId, roomInfo);
    }
    else if (type == "roomJoined") {
        QString roomId = message["roomId"].toString();
        QJsonObject roomInfo = message["roomInfo"].toObject();
        m_currentRoomId = roomId;
        emit roomJoined(roomId, roomInfo);
    }
    else if (type == "roomLeft") {
        m_currentRoomId.clear();
        emit roomLeft();
    }
    else if (type == "roomClosed") {
        m_currentRoomId.clear();
        emit roomClosed();
    }
    else if (type == "roomList") {
        QJsonArray rooms = message["rooms"].toArray();
        emit roomListReceived(rooms);
    }
    else if (type == "participantJoined") {
        QJsonObject participant = message["participant"].toObject();
        emit participantJoined(participant);
    }
    else if (type == "participantLeft") {
        QString participantId = message["participantId"].toString();
        emit participantLeft(participantId);
    }
    else if (type == "webrtcOffer") {
        QString fromId = message["fromId"].toString();
        QString sdp = message["sdp"].toString();
        emit offerReceived(fromId, sdp);
    }
    else if (type == "webrtcAnswer") {
        QString fromId = message["fromId"].toString();
        QString sdp = message["sdp"].toString();
        emit answerReceived(fromId, sdp);
    }
    else if (type == "iceCandidate") {
        QString fromId = message["fromId"].toString();
        QString candidate = message["candidate"].toString();
        emit iceCandidateReceived(fromId, candidate);
    }
    else if (type == "error") {
        QString error = message["message"].toString();
        emit errorOccurred(error);
    }
}

WebSocketClient::~WebSocketClient() {}
