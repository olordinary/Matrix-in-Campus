#include "studyroom.h"

StudyRoom::StudyRoom(QObject *parent)
    : QObject(parent)
    , m_maxParticipants(2)
    , m_currentParticipants(0)
    , m_isPrivate(false)
    , m_isActive(false)
{
}

StudyRoom::StudyRoom(const QString &roomId, const QString &roomName,
                     const QString &ownerId, int maxParticipants,
                     bool isPrivate,bool defaultvideostatus,
                     bool defaultaudiostatus ,QObject *parent)
    : QObject(parent)
    , m_roomId(roomId)
    , m_roomName(roomName)
    , m_ownerId(ownerId)
    , m_maxParticipants(maxParticipants)
    , m_currentParticipants(0)
    , m_isPrivate(isPrivate)
    , m_isActive(false)
    , m_defaultvideostatus(defaultvideostatus)
    , m_defaultaudiostatus(defaultaudiostatus)
{
}
void StudyRoom::setRoomName(const QString &name)
{
    if (m_roomName != name) {
        m_roomName = name;
        emit roomNameChanged();
    }
}

void StudyRoom::setOwnerId(const QString &ownerId)
{
     if (m_ownerId != ownerId) {
         m_ownerId = ownerId;
         emit ownerIdChanged();
     }
}

void StudyRoom::setMaxParticipants(int max)
{
    if (m_maxParticipants != max) {
        m_maxParticipants = max;
        emit maxParticipantsChanged();
    }
}

void StudyRoom::setCurrentParticipants(int current)
{
    if (m_currentParticipants != current) {
        m_currentParticipants = current;
        emit currentParticipantsChanged();
    }
}

void StudyRoom::setIsPrivate(bool isPrivate)
{
    if (m_isPrivate != isPrivate) {
        m_isPrivate = isPrivate;
        emit isPrivateChanged();
    }
}

void StudyRoom::setIsActive(bool isActive)
{
    if (m_isActive != isActive) {
        m_isActive = isActive;
        emit isActiveChanged();
    }
}

