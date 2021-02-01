/****************************************************************************
** Meta object code from reading C++ file 'arduino.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../arduino.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arduino.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_arduino_t {
    QByteArrayData data[19];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_arduino_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_arduino_t qt_meta_stringdata_arduino = {
    {
QT_MOC_LITERAL(0, 0, 7), // "arduino"
QT_MOC_LITERAL(1, 8, 11), // "chipUpdated"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "uint32_t"
QT_MOC_LITERAL(4, 30, 4), // "size"
QT_MOC_LITERAL(5, 35, 13), // "blockComplete"
QT_MOC_LITERAL(6, 49, 7), // "address"
QT_MOC_LITERAL(7, 57, 12), // "readComplete"
QT_MOC_LITERAL(8, 70, 4), // "data"
QT_MOC_LITERAL(9, 75, 9), // "readError"
QT_MOC_LITERAL(10, 85, 8), // "uint16_t"
QT_MOC_LITERAL(11, 94, 7), // "uint8_t"
QT_MOC_LITERAL(12, 102, 5), // "value"
QT_MOC_LITERAL(13, 108, 13), // "writeComplete"
QT_MOC_LITERAL(14, 122, 10), // "writeError"
QT_MOC_LITERAL(15, 133, 7), // "voltage"
QT_MOC_LITERAL(16, 141, 1), // "v"
QT_MOC_LITERAL(17, 143, 7), // "recieve"
QT_MOC_LITERAL(18, 151, 13) // "write_recieve"

    },
    "arduino\0chipUpdated\0\0uint32_t\0size\0"
    "blockComplete\0address\0readComplete\0"
    "data\0readError\0uint16_t\0uint8_t\0value\0"
    "writeComplete\0writeError\0voltage\0v\0"
    "recieve\0write_recieve"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_arduino[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    1,   65,    2, 0x06 /* Public */,
       9,    2,   68,    2, 0x06 /* Public */,
      13,    0,   73,    2, 0x06 /* Public */,
      14,    2,   74,    2, 0x06 /* Public */,
      15,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,   82,    2, 0x08 /* Private */,
      18,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 11,    6,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 11,    6,   12,
    QMetaType::Void, QMetaType::Float,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void arduino::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<arduino *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chipUpdated((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 1: _t->blockComplete((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 2: _t->readComplete((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->readError((*reinterpret_cast< uint16_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 4: _t->writeComplete(); break;
        case 5: _t->writeError((*reinterpret_cast< uint16_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 6: _t->voltage((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->recieve(); break;
        case 8: _t->write_recieve(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (arduino::*)(uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::chipUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (arduino::*)(uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::blockComplete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (arduino::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::readComplete)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (arduino::*)(uint16_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::readError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (arduino::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::writeComplete)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (arduino::*)(uint16_t , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::writeError)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (arduino::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&arduino::voltage)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject arduino::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_arduino.data,
    qt_meta_data_arduino,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *arduino::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *arduino::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_arduino.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int arduino::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void arduino::chipUpdated(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void arduino::blockComplete(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void arduino::readComplete(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void arduino::readError(uint16_t _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void arduino::writeComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void arduino::writeError(uint16_t _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void arduino::voltage(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
