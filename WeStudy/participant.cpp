#include "participant.h"


Participant::Participant(QObject *parent):QObject(parent)
    , m_isOwner(false) {}

Participant::Participant(const QString &participantId, const QString &nickname,
                         QObject *parent)
    : QObject(parent)
    , m_participantId(participantId)
    , m_nickname(nickname)
    , m_isOwner(false)
{
}

void Participant::setIsOwner(bool isOwner) {
    if (m_isOwner != isOwner) {
        m_isOwner = isOwner;
        emit isOwnerChanged();
    }
}
