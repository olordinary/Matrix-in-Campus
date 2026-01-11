#include "controller.h"
#include "websocketclient.h"
#include "webrtcManager.h"
#include <QJsonArray>
#include <QJsonObject>
#include<QDebug>


Controller::Controller(WebSocketClient *client, WebRTCManager *webrtc, QObject *parent):QObject(parent)
    , m_client(client)
    , m_webrtc(webrtc)
    , m_currentRoom(nullptr) {
    connect(m_client, &WebSocketClient::roomCreated,
            this, &Controller::handleRoomCreated);
    connect(m_client, &WebSocketClient::roomJoined,
            this, &Controller::handleRoomJoined);
    connect(m_client, &WebSocketClient::participantJoined,
            this, &Controller::handleParticipantJoined);

}

QQmlListProperty<Participant> Controller::participants() {
    return QQmlListProperty<Participant>(this, &m_participants);

}

bool Controller::isOwner() const {
    if (!m_currentRoom || m_client->userId().isEmpty()) {
        return false;
    }
    return m_currentRoom->ownerId() == m_client->userId();
}

void Controller::createRoom(const QString &roomName,
                            int maxParticipants,
                            bool isPrivate,
                            bool videoStatus,
                            bool audioStatus,
                            const QString &password)
{
    if (isInRoom()) {
        return;
    }

    m_client->createRoom(roomName, maxParticipants, isPrivate,videoStatus, audioStatus,password);
}

void Controller::joinRoom(const QString &roomId, const QString &password) {

    m_client->joinRoom(roomId, password);
}

<<<<<<< HEAD
=======
void Controller::startStudying() {
    if (!isInRoom()) {
        emit errorOccurred("请先加入自习室");
        return;
    }

    m_isStudying = true;
    m_webrtc->startLocalMedia();
    emit isStudyingChanged();
}

void Controller::stopStudying() {
    if (!m_isStudying) {
        return;
    }

    m_isStudying = false;
    emit isStudyingChanged();
}

>>>>>>> bca9fd1 (without mediacapture)
Controller::~Controller() {
    // clearCurrentRoom();
}

void Controller::handleRoomCreated(const QString &roomId, const QJsonObject &roomInfo) {
    clearCurrentRoom();

    QString roomName = roomInfo["roomName"].toString();
    QString ownerId = roomInfo["ownerId"].toString();
    int maxParticipants = roomInfo["maxParticipants"].toInt();
    bool isPrivate = roomInfo["isPrivate"].toBool();
    bool defaultvideostatus = roomInfo["defaultvideostatus"].toBool();
    bool defaultaudiostatus = roomInfo["defaultaudiostatus"].toBool();
    m_currentRoom = new StudyRoom(roomId, roomName, ownerId, maxParticipants, isPrivate,defaultvideostatus,defaultaudiostatus, this);
    m_currentRoom->setIsActive(true);

    // 更新参与者列表
    QJsonArray participantsArray = roomInfo["participants"].toArray();
    updateParticipantsFromJson(participantsArray);

    emit currentRoomChanged();
    emit isInRoomChanged();
    emit isOwnerChanged();
//这里可能少了收集本地的webRtcIDE SDP、
    qDebug() << "Room created:" << roomId;
}

void Controller::handleRoomJoined(const QString &roomId, const QJsonObject &roomInfo) {
    clearCurrentRoom();//清空现有的房间

    QString roomName = roomInfo["roomName"].toString();
    QString ownerId = roomInfo["ownerId"].toString();
    int maxParticipants = roomInfo["maxParticipants"].toInt();
    int currentParticipants = roomInfo["currentParticipants"].toInt();
    bool isPrivate = roomInfo["isPrivate"].toBool();
    bool defaultvideostatus = roomInfo["videoStatus"].toBool();
    bool defaultaudioStatus = roomInfo["audioStatus"].toBool();

    //在加入房间后B端也要显示UI房间信息，所以就创建一个本地的来收集信息，展示信息而已
    m_currentRoom = new StudyRoom(roomId, roomName, ownerId, maxParticipants, isPrivate, defaultvideostatus,defaultaudioStatus,this);
    m_currentRoom->setCurrentParticipants(currentParticipants);
    m_currentRoom->setIsActive(true);

    // 更新参与者列表
    QJsonArray participantsArray = roomInfo["participants"].toArray();
    updateParticipantsFromJson(participantsArray);//更新我房间管理器的成员列表

    // 为每个已存在的参与者创建WebRTC连接
    for (Participant *p : m_participants) {
        if (p->participantId() != m_client->userId()) {
<<<<<<< HEAD
            m_webrtc->createPeerConnection(p->participantId());
=======
            m_webrtc->setupPeerConnection(true);
>>>>>>> bca9fd1 (without mediacapture)
        }
    }

    emit currentRoomChanged();
    emit isInRoomChanged();
    emit isOwnerChanged();

    qDebug() << "Room joined:" << roomId;
}

void Controller::handleParticipantJoined(const QJsonObject &participant) {
    QString participantId = participant["participantId"].toString();
    QString nickname = participant["nickname"].toString();

    if (findParticipant(participantId)) {
        qWarning() << "Participant already exists:" << participantId;
        return;
    }

    Participant *p = new Participant(participantId, nickname, this);
    m_participants.append(p);

    if (m_currentRoom) {
        m_currentRoom->setCurrentParticipants(m_participants.count());
    }

    // 为新加入的参与者创建WebRTC连接
    if (participantId != m_client->userId()) {
<<<<<<< HEAD
        m_webrtc->createPeerConnection(participantId);
=======
        m_webrtc->setupPeerConnection(true);
>>>>>>> bca9fd1 (without mediacapture)
    }

    emit participantsChanged();

    qDebug() << "Participant joined:" << participantId;
}

void Controller::clearCurrentRoom() {
    if (m_currentRoom) {
        m_currentRoom->deleteLater();
        m_currentRoom = nullptr;
    }

    qDeleteAll(m_participants);
    m_participants.clear();
    emit participantsChanged();

<<<<<<< HEAD
    m_webrtc->closeAllConnections();
=======
    m_webrtc->closePeerConnection();
>>>>>>> bca9fd1 (without mediacapture)

}

void Controller::updateParticipantsFromJson(const QJsonArray &participantsArray) {
    qDeleteAll(m_participants);
    m_participants.clear();

    for (const QJsonValue &value : participantsArray) {
        QJsonObject obj = value.toObject();
        QString participantId = obj["participantId"].toString();
        QString nickname = obj["nickname"].toString();
        bool isOwner = obj["isOwner"].toBool();

        Participant *p = new Participant(participantId, nickname, this);
        p->setIsOwner(isOwner);
        m_participants.append(p);
    }

    emit participantsChanged();


}

Participant *Controller::findParticipant(const QString &participantId) {
    for (Participant *p : m_participants) {
        if (p->participantId() == participantId) {
            return p;
        }
    }
    return nullptr;
}
