#pragma once

#include <QObject>
#include <QString>
class Participant : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString participantId READ participantId CONSTANT)
    Q_PROPERTY(QString nickname READ nickname NOTIFY nicknameChanged)
    Q_PROPERTY(bool isOwner READ isOwner NOTIFY isOwnerChanged)

public:
    explicit Participant(QObject *parent = nullptr);
    Participant(const QString &participantId, const QString &nickname,
                QObject *parent = nullptr);
    QString participantId() const { return m_participantId; }
    QString nickname() const { return m_nickname; }
    bool isOwner() const { return m_isOwner; }
    void setIsOwner(bool isOwner);
signals:
    void nicknameChanged();
    void isOwnerChanged();

private:
    QString m_participantId;
    QString m_nickname;
    bool m_isOwner;
};
