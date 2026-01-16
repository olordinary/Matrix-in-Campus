/****************************************************************************
** Meta object code from reading C++ file 'webrtcmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../webrtcmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webrtcmanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13WebRTCManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto WebRTCManager::qt_create_metaobjectdata<qt_meta_tag_ZN13WebRTCManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WebRTCManager",
        "connectedChanged",
        "",
        "audioStateChanged",
        "videoStateChanged",
        "localStreamReady",
        "remoteStreamReady",
        "videoReceived",
        "data",
        "audioReceived",
        "errorOccurred",
        "error",
        "statusChanged",
        "status",
        "peerConnectionStateChanged",
        "state",
        "handleOffer",
        "fromId",
        "sdp",
        "handleAnswer",
        "handleIceCandidate",
        "candidate",
        "onVideoFrameReady",
        "onVideoReceived",
        "onPeerJoined",
        "peerId",
        "startLocalMedia",
        "stopLocalMedia",
        "setupPeerConnection",
        "isOfferer",
        "closePeerConnection",
        "sendVideo",
        "sendAudio",
        "connected",
        "audioEnabled",
        "videoEnabled"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connectedChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'audioStateChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'videoStateChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'localStreamReady'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'remoteStreamReady'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'videoReceived'
        QtMocHelpers::SignalData<void(const QByteArray &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
        // Signal 'audioReceived'
        QtMocHelpers::SignalData<void(const QByteArray &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Signal 'peerConnectionStateChanged'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'handleOffer'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 17 }, { QMetaType::QString, 18 },
        }}),
        // Slot 'handleAnswer'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 17 }, { QMetaType::QString, 18 },
        }}),
        // Slot 'handleIceCandidate'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 17 }, { QMetaType::QString, 21 },
        }}),
        // Slot 'onVideoFrameReady'
        QtMocHelpers::SlotData<void(const QByteArray &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
        // Slot 'onVideoReceived'
        QtMocHelpers::SlotData<void(const QByteArray &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
        // Slot 'onPeerJoined'
        QtMocHelpers::SlotData<void(const QString &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 25 },
        }}),
        // Method 'startLocalMedia'
        QtMocHelpers::MethodData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopLocalMedia'
        QtMocHelpers::MethodData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setupPeerConnection'
        QtMocHelpers::MethodData<void(bool)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 29 },
        }}),
        // Method 'closePeerConnection'
        QtMocHelpers::MethodData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'sendVideo'
        QtMocHelpers::MethodData<void(const QByteArray &)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
        // Method 'sendAudio'
        QtMocHelpers::MethodData<void(const QByteArray &)>(32, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 8 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'connected'
        QtMocHelpers::PropertyData<bool>(33, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'audioEnabled'
        QtMocHelpers::PropertyData<bool>(34, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'videoEnabled'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WebRTCManager, qt_meta_tag_ZN13WebRTCManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WebRTCManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13WebRTCManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13WebRTCManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13WebRTCManagerE_t>.metaTypes,
    nullptr
} };

void WebRTCManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WebRTCManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connectedChanged(); break;
        case 1: _t->audioStateChanged(); break;
        case 2: _t->videoStateChanged(); break;
        case 3: _t->localStreamReady(); break;
        case 4: _t->remoteStreamReady(); break;
        case 5: _t->videoReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 6: _t->audioReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 7: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->peerConnectionStateChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->handleOffer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->handleAnswer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 12: _t->handleIceCandidate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->onVideoFrameReady((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 14: _t->onVideoReceived((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 15: _t->onPeerJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->startLocalMedia(); break;
        case 17: _t->stopLocalMedia(); break;
        case 18: _t->setupPeerConnection((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->closePeerConnection(); break;
        case 20: _t->sendVideo((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 21: _t->sendAudio((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)()>(_a, &WebRTCManager::connectedChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)()>(_a, &WebRTCManager::audioStateChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)()>(_a, &WebRTCManager::videoStateChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)()>(_a, &WebRTCManager::localStreamReady, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)()>(_a, &WebRTCManager::remoteStreamReady, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)(const QByteArray & )>(_a, &WebRTCManager::videoReceived, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)(const QByteArray & )>(_a, &WebRTCManager::audioReceived, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)(const QString & )>(_a, &WebRTCManager::errorOccurred, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)(const QString & )>(_a, &WebRTCManager::statusChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (WebRTCManager::*)(const QString & )>(_a, &WebRTCManager::peerConnectionStateChanged, 9))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isConnected(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isAudioEnabled(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isVideoEnabled(); break;
        default: break;
        }
    }
}

const QMetaObject *WebRTCManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebRTCManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13WebRTCManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebRTCManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WebRTCManager::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebRTCManager::audioStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebRTCManager::videoStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WebRTCManager::localStreamReady()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WebRTCManager::remoteStreamReady()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WebRTCManager::videoReceived(const QByteArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void WebRTCManager::audioReceived(const QByteArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void WebRTCManager::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void WebRTCManager::statusChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void WebRTCManager::peerConnectionStateChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}
QT_WARNING_POP
