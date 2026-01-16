/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../controller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10ControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto Controller::qt_create_metaobjectdata<qt_meta_tag_ZN10ControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Controller",
        "currentRoomChanged",
        "",
        "errorOccurred",
        "error",
        "isInRoomChanged",
        "isOwnerChanged",
        "participantsChanged",
        "isStudyingChanged",
        "handleRoomCreated",
        "roomId",
        "roomInfo",
        "handleRoomJoined",
        "handleParticipantJoined",
        "participant",
        "handleRoomLeft",
        "handleRoomClosed",
        "handleParticipantLeft",
        "particpantId",
        "createRoom",
        "roomName",
        "maxParticipants",
        "isPrivate",
        "videoStatus",
        "audioStatus",
        "password",
        "joinRoom",
        "startStudying",
        "stopStudying",
        "leaveRoom",
        "closeRoom",
        "currentRoom",
        "StudyRoom*",
        "participants",
        "QQmlListProperty<Participant>",
        "isInRoom",
        "isOwner",
        "isStudying"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'currentRoomChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 },
        }}),
        // Signal 'isInRoomChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isOwnerChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'participantsChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isStudyingChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleRoomCreated'
        QtMocHelpers::SlotData<void(const QString &, const QJsonObject &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QJsonObject, 11 },
        }}),
        // Slot 'handleRoomJoined'
        QtMocHelpers::SlotData<void(const QString &, const QJsonObject &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QJsonObject, 11 },
        }}),
        // Slot 'handleParticipantJoined'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QJsonObject, 14 },
        }}),
        // Slot 'handleRoomLeft'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleRoomClosed'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleParticipantLeft'
        QtMocHelpers::SlotData<void(const QString &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 18 },
        }}),
        // Method 'createRoom'
        QtMocHelpers::MethodData<void(const QString &, int, bool, bool, bool, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::Int, 21 }, { QMetaType::Bool, 22 }, { QMetaType::Bool, 23 },
            { QMetaType::Bool, 24 }, { QMetaType::QString, 25 },
        }}),
        // Method 'createRoom'
        QtMocHelpers::MethodData<void(const QString &, int, bool, bool, bool)>(19, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 20 }, { QMetaType::Int, 21 }, { QMetaType::Bool, 22 }, { QMetaType::Bool, 23 },
            { QMetaType::Bool, 24 },
        }}),
        // Method 'joinRoom'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QString, 25 },
        }}),
        // Method 'joinRoom'
        QtMocHelpers::MethodData<void(const QString &)>(26, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'startStudying'
        QtMocHelpers::MethodData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopStudying'
        QtMocHelpers::MethodData<void()>(28, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'leaveRoom'
        QtMocHelpers::MethodData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'closeRoom'
        QtMocHelpers::MethodData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'currentRoom'
        QtMocHelpers::PropertyData<StudyRoom*>(31, 0x80000000 | 32, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'participants'
        QtMocHelpers::PropertyData<QQmlListProperty<Participant>>(33, 0x80000000 | 34, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'isInRoom'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags, 2),
        // property 'isOwner'
        QtMocHelpers::PropertyData<bool>(36, QMetaType::Bool, QMC::DefaultPropertyFlags, 3),
        // property 'isStudying'
        QtMocHelpers::PropertyData<bool>(37, QMetaType::Bool, QMC::DefaultPropertyFlags, 5),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Controller, qt_meta_tag_ZN10ControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ControllerE_t>.metaTypes,
    nullptr
} };

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Controller *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->currentRoomChanged(); break;
        case 1: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->isInRoomChanged(); break;
        case 3: _t->isOwnerChanged(); break;
        case 4: _t->participantsChanged(); break;
        case 5: _t->isStudyingChanged(); break;
        case 6: _t->handleRoomCreated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 7: _t->handleRoomJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[2]))); break;
        case 8: _t->handleParticipantJoined((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 9: _t->handleRoomLeft(); break;
        case 10: _t->handleRoomClosed(); break;
        case 11: _t->handleParticipantLeft((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->createRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 13: _t->createRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 14: _t->joinRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->joinRoom((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->startStudying(); break;
        case 17: _t->stopStudying(); break;
        case 18: _t->leaveRoom(); break;
        case 19: _t->closeRoom(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Controller::*)()>(_a, &Controller::currentRoomChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)(const QString & )>(_a, &Controller::errorOccurred, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)()>(_a, &Controller::isInRoomChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)()>(_a, &Controller::isOwnerChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)()>(_a, &Controller::participantsChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Controller::*)()>(_a, &Controller::isStudyingChanged, 5))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StudyRoom* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<StudyRoom**>(_v) = _t->currentRoom(); break;
        case 1: *reinterpret_cast<QQmlListProperty<Participant>*>(_v) = _t->participants(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isInRoom(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isOwner(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->isStudying(); break;
        default: break;
        }
    }
}

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Controller::currentRoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Controller::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Controller::isInRoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Controller::isOwnerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Controller::participantsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Controller::isStudyingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
