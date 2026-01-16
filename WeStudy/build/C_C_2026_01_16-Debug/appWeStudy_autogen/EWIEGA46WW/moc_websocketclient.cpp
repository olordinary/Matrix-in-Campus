/****************************************************************************
** Meta object code from reading C++ file 'websocketclient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../websocketclient.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'websocketclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15WebSocketClientE_t {};
} // unnamed namespace

template <> constexpr inline auto WebSocketClient::qt_create_metaobjectdata<qt_meta_tag_ZN15WebSocketClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WebSocketClient",
        "connectedChanged",
        "",
        "userIdChanged",
        "messageReceived",
        "message",
        "errorOccurred",
        "error",
        "participantLeft",
        "participantId",
        "roomCreated",
        "roomId",
        "roomInfo",
        "roomJoined",
        "peerJoined",
        "peerId",
        "roomLeft",
        "roomClosed",
        "roomListReceived",
        "rooms",
        "searchResultReceived",
        "participantJoined",
        "participant",
        "offerReceived",
        "fromId",
        "sdp",
        "answerReceived",
        "iceCandidateReceived",
        "candidate",
        "onConnected",
        "onDisconnected",
        "onTextMessageReceived",
        "onError",
        "QAbstractSocket::SocketError",
        "connectToServer",
        "url",
        "disconnect",
        "sendMessage",
        "sendOffer",
        "targetId",
        "sendAnswer",
        "sendIceCandidate",
        "createRoom",
        "roomName",
        "maxParticipants",
        "isPrivate",
        "videoStatus",
        "audioStatus",
        "password",
        "joinRoom",
        "searchRoom",
        "connected",
        "userId"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connectedChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'userIdChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'messageReceived'
        QtMocHelpers::SignalData<void(const QJsonObject &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonObject, 5 },
        }}),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'participantLeft'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'roomCreated'
        QtMocHelpers::SignalData<void(const QString &, const QJsonObject &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QJsonObject, 12 },
        }}),
        // Signal 'roomJoined'
        QtMocHelpers::SignalData<void(const QString &, const QJsonObject &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QJsonObject, 12 },
        }}),
        // Signal 'peerJoined'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'roomLeft'
        QtMocHelpers::SignalData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'roomClosed'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'roomListReceived'
        QtMocHelpers::SignalData<void(const QJsonArray &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonArray, 19 },
        }}),
        // Signal 'searchResultReceived'
        QtMocHelpers::SignalData<void(const QJsonArray &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonArray, 19 },
        }}),
        // Signal 'participantJoined'
        QtMocHelpers::SignalData<void(const QJsonObject &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonObject, 22 },
        }}),
        // Signal 'offerReceived'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 25 },
        }}),
        // Signal 'answerReceived'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 25 },
        }}),
        // Signal 'iceCandidateReceived'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 28 },
        }}),
        // Slot 'onConnected'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTextMessageReceived'
        QtMocHelpers::SlotData<void(const QString &)>(31, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'onError'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 33, 7 },
        }}),
        // Method 'connectToServer'
        QtMocHelpers::MethodData<void(const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 35 },
        }}),
        // Method 'disconnect'
        QtMocHelpers::MethodData<void()>(36, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'sendMessage'
        QtMocHelpers::MethodData<void(const QJsonObject &)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonObject, 5 },
        }}),
        // Method 'sendOffer'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(38, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 39 }, { QMetaType::QString, 25 },
        }}),
        // Method 'sendAnswer'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 39 }, { QMetaType::QString, 25 },
        }}),
        // Method 'sendIceCandidate'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 39 }, { QMetaType::QString, 28 },
        }}),
        // Method 'createRoom'
        QtMocHelpers::MethodData<void(const QString &, int, bool, bool, bool, const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 43 }, { QMetaType::Int, 44 }, { QMetaType::Bool, 45 }, { QMetaType::Bool, 46 },
            { QMetaType::Bool, 47 }, { QMetaType::QString, 48 },
        }}),
        // Method 'createRoom'
        QtMocHelpers::MethodData<void(const QString &, int, bool, bool, bool)>(42, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 43 }, { QMetaType::Int, 44 }, { QMetaType::Bool, 45 }, { QMetaType::Bool, 46 },
            { QMetaType::Bool, 47 },
        }}),
        // Method 'joinRoom'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(49, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 48 },
        }}),
        // Method 'joinRoom'
        QtMocHelpers::MethodData<void(const QString &)>(49, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Method 'searchRoom'
        QtMocHelpers::MethodData<void(const QString &)>(50, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 43 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'connected'
        QtMocHelpers::PropertyData<bool>(51, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'userId'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WebSocketClient, qt_meta_tag_ZN15WebSocketClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WebSocketClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WebSocketClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WebSocketClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15WebSocketClientE_t>.metaTypes,
    nullptr
} };

void WebSocketClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WebSocketClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connectedChanged(); break;
        case 1: _t->userIdChanged(); break;
        case 2: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->participantLeft((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->roomCreated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 6: _t->roomJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 7: _t->peerJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->roomLeft(); break;
        case 9: _t->roomClosed(); break;
        case 10: _t->roomListReceived((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 11: _t->searchResultReceived((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 12: _t->participantJoined((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 13: _t->offerReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 14: _t->answerReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->iceCandidateReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 16: _t->onConnected(); break;
        case 17: _t->onDisconnected(); break;
        case 18: _t->onTextMessageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->onError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 20: _t->connectToServer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->disconnect(); break;
        case 22: _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 23: _t->sendOffer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 24: _t->sendAnswer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 25: _t->sendIceCandidate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 26: _t->createRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 27: _t->createRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 28: _t->joinRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 29: _t->joinRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 30: _t->searchRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)()>(_a, &WebSocketClient::connectedChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)()>(_a, &WebSocketClient::userIdChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QJsonObject & )>(_a, &WebSocketClient::messageReceived, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & )>(_a, &WebSocketClient::errorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & )>(_a, &WebSocketClient::participantLeft, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & , const QJsonObject & )>(_a, &WebSocketClient::roomCreated, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & , const QJsonObject & )>(_a, &WebSocketClient::roomJoined, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & )>(_a, &WebSocketClient::peerJoined, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)()>(_a, &WebSocketClient::roomLeft, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)()>(_a, &WebSocketClient::roomClosed, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QJsonArray & )>(_a, &WebSocketClient::roomListReceived, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QJsonArray & )>(_a, &WebSocketClient::searchResultReceived, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QJsonObject & )>(_a, &WebSocketClient::participantJoined, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & , const QString & )>(_a, &WebSocketClient::offerReceived, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & , const QString & )>(_a, &WebSocketClient::answerReceived, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebSocketClient::*)(const QString & , const QString & )>(_a, &WebSocketClient::iceCandidateReceived, 15))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isConnected(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->userId(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setUserId(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *WebSocketClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebSocketClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15WebSocketClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebSocketClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WebSocketClient::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebSocketClient::userIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebSocketClient::messageReceived(const QJsonObject & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void WebSocketClient::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void WebSocketClient::participantLeft(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void WebSocketClient::roomCreated(const QString & _t1, const QJsonObject & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void WebSocketClient::roomJoined(const QString & _t1, const QJsonObject & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void WebSocketClient::peerJoined(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void WebSocketClient::roomLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void WebSocketClient::roomClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void WebSocketClient::roomListReceived(const QJsonArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void WebSocketClient::searchResultReceived(const QJsonArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void WebSocketClient::participantJoined(const QJsonObject & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void WebSocketClient::offerReceived(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1, _t2);
}

// SIGNAL 14
void WebSocketClient::answerReceived(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1, _t2);
}

// SIGNAL 15
void WebSocketClient::iceCandidateReceived(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1, _t2);
}
QT_WARNING_POP
