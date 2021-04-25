/****************************************************************************
** Meta object code from reading C++ file 'matchinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CSAnalize/matchinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'matchinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MatchInfo_t {
    QByteArrayData data[16];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MatchInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MatchInfo_t qt_meta_stringdata_MatchInfo = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MatchInfo"
QT_MOC_LITERAL(1, 10, 7), // "loading"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "closed"
QT_MOC_LITERAL(4, 26, 17), // "timeFilterChanged"
QT_MOC_LITERAL(5, 44, 1), // "i"
QT_MOC_LITERAL(6, 46, 12), // "entFromMonth"
QT_MOC_LITERAL(7, 59, 10), // "entToMonth"
QT_MOC_LITERAL(8, 70, 4), // "load"
QT_MOC_LITERAL(9, 75, 5), // "reMap"
QT_MOC_LITERAL(10, 81, 8), // "reFilter"
QT_MOC_LITERAL(11, 90, 8), // "isLoaded"
QT_MOC_LITERAL(12, 99, 11), // "infoLoaded1"
QT_MOC_LITERAL(13, 111, 12), // "lineupFilter"
QT_MOC_LITERAL(14, 124, 11), // "infoLoaded2"
QT_MOC_LITERAL(15, 136, 7) // "closing"

    },
    "MatchInfo\0loading\0\0closed\0timeFilterChanged\0"
    "i\0entFromMonth\0entToMonth\0load\0reMap\0"
    "reFilter\0isLoaded\0infoLoaded1\0"
    "lineupFilter\0infoLoaded2\0closing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MatchInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   76,    2, 0x0a /* Public */,
       6,    1,   79,    2, 0x0a /* Public */,
       7,    1,   82,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    1,   86,    2, 0x0a /* Public */,
      10,    0,   89,    2, 0x0a /* Public */,
      11,    0,   90,    2, 0x0a /* Public */,
      12,    1,   91,    2, 0x0a /* Public */,
      14,    1,   94,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,

       0        // eod
};

void MatchInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MatchInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loading(); break;
        case 1: _t->closed(); break;
        case 2: _t->timeFilterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->entFromMonth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->entToMonth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->load(); break;
        case 6: _t->reMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->reFilter(); break;
        case 8: _t->isLoaded(); break;
        case 9: _t->infoLoaded1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->infoLoaded2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->closing(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MatchInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MatchInfo::loading)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MatchInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MatchInfo::closed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MatchInfo::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MatchInfo.data,
    qt_meta_data_MatchInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MatchInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MatchInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MatchInfo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MatchInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MatchInfo::loading()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MatchInfo::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
