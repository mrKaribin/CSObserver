/****************************************************************************
** Meta object code from reading C++ file 'teaminfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CSAnalize/teaminfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teaminfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapStat_t {
    QByteArrayData data[19];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapStat_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapStat_t qt_meta_stringdata_mapStat = {
    {
QT_MOC_LITERAL(0, 0, 7), // "mapStat"
QT_MOC_LITERAL(1, 8, 9), // "roundEdit"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "team"
QT_MOC_LITERAL(4, 24, 3), // "pos"
QT_MOC_LITERAL(5, 28, 3), // "res"
QT_MOC_LITERAL(6, 32, 4), // "icon"
QT_MOC_LITERAL(7, 37, 10), // "roundParse"
QT_MOC_LITERAL(8, 48, 4), // "html"
QT_MOC_LITERAL(9, 53, 4), // "half"
QT_MOC_LITERAL(10, 58, 5), // "parse"
QT_MOC_LITERAL(11, 64, 4), // "load"
QT_MOC_LITERAL(12, 69, 8), // "reFilter"
QT_MOC_LITERAL(13, 78, 6), // "filter"
QT_MOC_LITERAL(14, 85, 8), // "isLoaded"
QT_MOC_LITERAL(15, 94, 10), // "createFull"
QT_MOC_LITERAL(16, 105, 10), // "createDemo"
QT_MOC_LITERAL(17, 116, 8), // "openFull"
QT_MOC_LITERAL(18, 125, 8) // "openDemo"

    },
    "mapStat\0roundEdit\0\0team\0pos\0res\0icon\0"
    "roundParse\0html\0half\0parse\0load\0"
    "reFilter\0filter\0isLoaded\0createFull\0"
    "createDemo\0openFull\0openDemo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapStat[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   64,    2, 0x0a /* Public */,
       7,    3,   73,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    1,   84,    2, 0x0a /* Public */,
      14,    0,   87,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x0a /* Public */,
      16,    0,   89,    2, 0x0a /* Public */,
      17,    0,   90,    2, 0x0a /* Public */,
      18,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    8,    3,    9,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mapStat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mapStat *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->roundEdit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->roundParse((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->parse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->load(); break;
        case 4: _t->reFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->isLoaded(); break;
        case 6: _t->createFull(); break;
        case 7: _t->createDemo(); break;
        case 8: _t->openFull(); break;
        case 9: _t->openDemo(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mapStat::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_mapStat.data,
    qt_meta_data_mapStat,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapStat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapStat::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapStat.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int mapStat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_TeamMapInfo_t {
    QByteArrayData data[6];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TeamMapInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TeamMapInfo_t qt_meta_stringdata_TeamMapInfo = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TeamMapInfo"
QT_MOC_LITERAL(1, 12, 4), // "load"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "isLoaded"
QT_MOC_LITERAL(4, 27, 8), // "reFilter"
QT_MOC_LITERAL(5, 36, 6) // "filter"

    },
    "TeamMapInfo\0load\0\0isLoaded\0reFilter\0"
    "filter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TeamMapInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    1,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void TeamMapInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TeamMapInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->load(); break;
        case 1: _t->isLoaded(); break;
        case 2: _t->reFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TeamMapInfo::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TeamMapInfo.data,
    qt_meta_data_TeamMapInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TeamMapInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TeamMapInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TeamMapInfo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TeamMapInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_TeamInfo_t {
    QByteArrayData data[9];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TeamInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TeamInfo_t qt_meta_stringdata_TeamInfo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TeamInfo"
QT_MOC_LITERAL(1, 9, 7), // "loading"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "lineupFilter"
QT_MOC_LITERAL(4, 31, 3), // "str"
QT_MOC_LITERAL(5, 35, 4), // "load"
QT_MOC_LITERAL(6, 40, 8), // "isLoaded"
QT_MOC_LITERAL(7, 49, 8), // "reFilter"
QT_MOC_LITERAL(8, 58, 6) // "filter"

    },
    "TeamInfo\0loading\0\0lineupFilter\0str\0"
    "load\0isLoaded\0reFilter\0filter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TeamInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void TeamInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TeamInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loading(); break;
        case 1: _t->lineupFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->load(); break;
        case 3: _t->isLoaded(); break;
        case 4: _t->reFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TeamInfo::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TeamInfo::loading)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TeamInfo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TeamInfo::lineupFilter)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TeamInfo::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TeamInfo.data,
    qt_meta_data_TeamInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TeamInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TeamInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TeamInfo.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TeamInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TeamInfo::loading()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TeamInfo::lineupFilter(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
