/****************************************************************************
** Meta object code from reading C++ file 'delphinosyncro.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CSAnalize/delphinosyncro.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'delphinosyncro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KeyWidget_t {
    QByteArrayData data[15];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyWidget_t qt_meta_stringdata_KeyWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "KeyWidget"
QT_MOC_LITERAL(1, 10, 13), // "destroyedThis"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "product"
QT_MOC_LITERAL(4, 33, 11), // "destroyProg"
QT_MOC_LITERAL(5, 45, 11), // "destroyThis"
QT_MOC_LITERAL(6, 57, 3), // "key"
QT_MOC_LITERAL(7, 61, 6), // "turnOn"
QT_MOC_LITERAL(8, 68, 7), // "turnOff"
QT_MOC_LITERAL(9, 76, 16), // "productDestroyed"
QT_MOC_LITERAL(10, 93, 14), // "destroyClicked"
QT_MOC_LITERAL(11, 108, 15), // "activityClicked"
QT_MOC_LITERAL(12, 124, 6), // "active"
QT_MOC_LITERAL(13, 131, 2), // "is"
QT_MOC_LITERAL(14, 134, 7) // "license"

    },
    "KeyWidget\0destroyedThis\0\0product\0"
    "destroyProg\0destroyThis\0key\0turnOn\0"
    "turnOff\0productDestroyed\0destroyClicked\0"
    "activityClicked\0active\0is\0license"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    1,   68,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,
       8,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      14,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void KeyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KeyWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->destroyedThis((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->destroyProg(); break;
        case 2: _t->destroyThis((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->turnOn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->turnOff((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->productDestroyed(); break;
        case 6: _t->destroyClicked(); break;
        case 7: _t->activityClicked(); break;
        case 8: _t->active((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->license((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KeyWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyWidget::destroyedThis)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KeyWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyWidget::destroyProg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (KeyWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyWidget::destroyThis)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (KeyWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyWidget::turnOn)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (KeyWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KeyWidget::turnOff)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KeyWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_KeyWidget.data,
    qt_meta_data_KeyWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KeyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KeyWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KeyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void KeyWidget::destroyedThis(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyWidget::destroyProg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void KeyWidget::destroyThis(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void KeyWidget::turnOn(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void KeyWidget::turnOff(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_Delphinosyncro_t {
    QByteArrayData data[36];
    char stringdata0[456];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Delphinosyncro_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Delphinosyncro_t qt_meta_stringdata_Delphinosyncro = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Delphinosyncro"
QT_MOC_LITERAL(1, 15, 12), // "startLoading"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "mess"
QT_MOC_LITERAL(4, 34, 13), // "finishLoading"
QT_MOC_LITERAL(5, 48, 13), // "openMainSpace"
QT_MOC_LITERAL(6, 62, 12), // "openKeySpace"
QT_MOC_LITERAL(7, 75, 14), // "openLoginSpace"
QT_MOC_LITERAL(8, 90, 21), // "openRegistrationSpace"
QT_MOC_LITERAL(9, 112, 9), // "isAutorun"
QT_MOC_LITERAL(10, 122, 2), // "ar"
QT_MOC_LITERAL(11, 125, 15), // "exitFromAccount"
QT_MOC_LITERAL(12, 141, 9), // "deleteKey"
QT_MOC_LITERAL(13, 151, 4), // "_key"
QT_MOC_LITERAL(14, 156, 9), // "connected"
QT_MOC_LITERAL(15, 166, 11), // "hostFounded"
QT_MOC_LITERAL(16, 178, 15), // "connectingError"
QT_MOC_LITERAL(17, 194, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(18, 223, 16), // "reconnectTimeout"
QT_MOC_LITERAL(19, 240, 15), // "checkConnection"
QT_MOC_LITERAL(20, 256, 7), // "reading"
QT_MOC_LITERAL(21, 264, 7), // "writing"
QT_MOC_LITERAL(22, 272, 7), // "command"
QT_MOC_LITERAL(23, 280, 10), // "activating"
QT_MOC_LITERAL(24, 291, 13), // "activatingAll"
QT_MOC_LITERAL(25, 305, 6), // "runAll"
QT_MOC_LITERAL(26, 312, 8), // "logining"
QT_MOC_LITERAL(27, 321, 12), // "registration"
QT_MOC_LITERAL(28, 334, 13), // "turnOnProduct"
QT_MOC_LITERAL(29, 348, 4), // "name"
QT_MOC_LITERAL(30, 353, 14), // "turnOffProduct"
QT_MOC_LITERAL(31, 368, 15), // "trayIconClicked"
QT_MOC_LITERAL(32, 384, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(33, 418, 6), // "reason"
QT_MOC_LITERAL(34, 425, 16), // "launcherShowHide"
QT_MOC_LITERAL(35, 442, 13) // "closeLauncher"

    },
    "Delphinosyncro\0startLoading\0\0mess\0"
    "finishLoading\0openMainSpace\0openKeySpace\0"
    "openLoginSpace\0openRegistrationSpace\0"
    "isAutorun\0ar\0exitFromAccount\0deleteKey\0"
    "_key\0connected\0hostFounded\0connectingError\0"
    "QAbstractSocket::SocketError\0"
    "reconnectTimeout\0checkConnection\0"
    "reading\0writing\0command\0activating\0"
    "activatingAll\0runAll\0logining\0"
    "registration\0turnOnProduct\0name\0"
    "turnOffProduct\0trayIconClicked\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0launcherShowHide\0closeLauncher"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Delphinosyncro[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x0a /* Public */,
       4,    0,  147,    2, 0x0a /* Public */,
       5,    0,  148,    2, 0x0a /* Public */,
       6,    0,  149,    2, 0x0a /* Public */,
       7,    0,  150,    2, 0x0a /* Public */,
       8,    0,  151,    2, 0x0a /* Public */,
       9,    1,  152,    2, 0x0a /* Public */,
      11,    0,  155,    2, 0x0a /* Public */,
      12,    1,  156,    2, 0x0a /* Public */,
      14,    0,  159,    2, 0x0a /* Public */,
      15,    0,  160,    2, 0x0a /* Public */,
      16,    1,  161,    2, 0x0a /* Public */,
      18,    0,  164,    2, 0x0a /* Public */,
      19,    0,  165,    2, 0x0a /* Public */,
      20,    0,  166,    2, 0x0a /* Public */,
      21,    1,  167,    2, 0x0a /* Public */,
      23,    0,  170,    2, 0x0a /* Public */,
      24,    0,  171,    2, 0x0a /* Public */,
      25,    0,  172,    2, 0x0a /* Public */,
      26,    0,  173,    2, 0x0a /* Public */,
      27,    0,  174,    2, 0x0a /* Public */,
      28,    1,  175,    2, 0x0a /* Public */,
      30,    1,  178,    2, 0x0a /* Public */,
      31,    1,  181,    2, 0x0a /* Public */,
      34,    0,  184,    2, 0x0a /* Public */,
      35,    0,  185,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Delphinosyncro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Delphinosyncro *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startLoading((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->finishLoading(); break;
        case 2: _t->openMainSpace(); break;
        case 3: _t->openKeySpace(); break;
        case 4: _t->openLoginSpace(); break;
        case 5: _t->openRegistrationSpace(); break;
        case 6: _t->isAutorun((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->exitFromAccount(); break;
        case 8: _t->deleteKey((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->connected(); break;
        case 10: _t->hostFounded(); break;
        case 11: _t->connectingError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->reconnectTimeout(); break;
        case 13: _t->checkConnection(); break;
        case 14: _t->reading(); break;
        case 15: _t->writing((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->activating(); break;
        case 17: _t->activatingAll(); break;
        case 18: _t->runAll(); break;
        case 19: _t->logining(); break;
        case 20: _t->registration(); break;
        case 21: _t->turnOnProduct((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->turnOffProduct((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->trayIconClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 24: _t->launcherShowHide(); break;
        case 25: _t->closeLauncher(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Delphinosyncro::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Delphinosyncro.data,
    qt_meta_data_Delphinosyncro,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Delphinosyncro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Delphinosyncro::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Delphinosyncro.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Delphinosyncro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
