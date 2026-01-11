#pragma once
#include <QObject>

class StudyRoom:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomId READ roomId CONSTANT)
    Q_PROPERTY(QString roomName READ roomName NOTIFY roomNameChanged)
    Q_PROPERTY(QString ownerId READ ownerId NOTIFY ownerIdChanged)
    Q_PROPERTY(int maxParticipants READ maxParticipants NOTIFY maxParticipantsChanged)
    Q_PROPERTY(int currentParticipants READ currentParticipants NOTIFY currentParticipantsChanged)
    Q_PROPERTY(bool isPrivate READ isPrivate NOTIFY isPrivateChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool defaultvideostatus READ defaultvideostatus CONSTANT )
    Q_PROPERTY(bool defaultaudiostatus READ  defaultaudiostatus CONSTANT)

public:
    explicit StudyRoom(QObject *parent = nullptr);
    StudyRoom(const QString &roomId, const QString &roomName,
              const QString &ownerId, int maxParticipants,
              bool isPrivate,bool defaultvideostatus,
              bool defaultaudiostatus ,QObject *parent = nullptr);

    QString roomId() const { return m_roomId; }
    QString roomName() const { return m_roomName; }
    QString ownerId() const { return m_ownerId; }
    int maxParticipants() const { return m_maxParticipants; }
    int currentParticipants() const { return m_currentParticipants; }
    bool isPrivate() const { return m_isPrivate; }
    bool isActive() const { return m_isActive; }
    bool defaultvideostatus() const{return m_defaultvideostatus;}
    bool defaultaudiostatus() const{return m_defaultaudiostatus;}
    void setRoomName(const QString &name);
    void setOwnerId(const QString &ownerId);
    void setMaxParticipants(int max);
    void setCurrentParticipants(int current);
    void setIsPrivate(bool isPrivate);
    void setIsActive(bool isActive);
signals:
    void roomNameChanged();
    void ownerIdChanged();
    void maxParticipantsChanged();
    void currentParticipantsChanged();
    void isPrivateChanged();
    void isActiveChanged();
private:
    QString m_roomId;
    QString m_roomName;
    QString m_ownerId;
    int m_maxParticipants;
    int m_currentParticipants;
    bool m_isPrivate;
    bool m_isActive;
    bool m_defaultvideostatus;
    bool m_defaultaudiostatus;
};
