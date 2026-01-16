/****************************************************************************
** Meta object code from reading C++ file 'studyroom.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../studyroom.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studyroom.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9StudyRoomE_t {};
} // unnamed namespace

template <> constexpr inline auto StudyRoom::qt_create_metaobjectdata<qt_meta_tag_ZN9StudyRoomE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "StudyRoom",
        "roomNameChanged",
        "",
        "ownerIdChanged",
        "maxParticipantsChanged",
        "currentParticipantsChanged",
        "isPrivateChanged",
        "isActiveChanged",
        "roomId",
        "roomName",
        "ownerId",
        "maxParticipants",
        "currentParticipants",
        "isPrivate",
        "isActive",
        "defaultvideostatus",
        "defaultaudiostatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'roomNameChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ownerIdChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxParticipantsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentParticipantsChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isPrivateChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'isActiveChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'roomId'
        QtMocHelpers::PropertyData<QString>(8, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'roomName'
        QtMocHelpers::PropertyData<QString>(9, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'ownerId'
        QtMocHelpers::PropertyData<QString>(10, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'maxParticipants'
        QtMocHelpers::PropertyData<int>(11, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'currentParticipants'
        QtMocHelpers::PropertyData<int>(12, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'isPrivate'
        QtMocHelpers::PropertyData<bool>(13, QMetaType::Bool, QMC::DefaultPropertyFlags, 4),
        // property 'isActive'
        QtMocHelpers::PropertyData<bool>(14, QMetaType::Bool, QMC::DefaultPropertyFlags, 5),
        // property 'defaultvideostatus'
        QtMocHelpers::PropertyData<bool>(15, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'defaultaudiostatus'
        QtMocHelpers::PropertyData<bool>(16, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<StudyRoom, qt_meta_tag_ZN9StudyRoomE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject StudyRoom::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StudyRoomE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StudyRoomE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9StudyRoomE_t>.metaTypes,
    nullptr
} };

void StudyRoom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<StudyRoom *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->roomNameChanged(); break;
        case 1: _t->ownerIdChanged(); break;
        case 2: _t->maxParticipantsChanged(); break;
        case 3: _t->currentParticipantsChanged(); break;
        case 4: _t->isPrivateChanged(); break;
        case 5: _t->isActiveChanged(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::roomNameChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::ownerIdChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::maxParticipantsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::currentParticipantsChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::isPrivateChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (StudyRoom::*)()>(_a, &StudyRoom::isActiveChanged, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->roomId(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->roomName(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->ownerId(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->maxParticipants(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->currentParticipants(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->isPrivate(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->isActive(); break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->defaultvideostatus(); break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->defaultaudiostatus(); break;
        default: break;
        }
    }
}

const QMetaObject *StudyRoom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudyRoom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StudyRoomE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StudyRoom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void StudyRoom::roomNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StudyRoom::ownerIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StudyRoom::maxParticipantsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StudyRoom::currentParticipantsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void StudyRoom::isPrivateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void StudyRoom::isActiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
