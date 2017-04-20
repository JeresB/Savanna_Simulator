/****************************************************************************
** Meta object code from reading C++ file 'simulation.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "simulation.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulation.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Simulation_t {
    QByteArrayData data[13];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Simulation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Simulation_t qt_meta_stringdata_Simulation = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Simulation"
QT_MOC_LITERAL(1, 11, 14), // "signal_valeurs"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "slot_setTailleX"
QT_MOC_LITERAL(4, 43, 15), // "slot_setTailleY"
QT_MOC_LITERAL(5, 59, 15), // "slot_nb_animaux"
QT_MOC_LITERAL(6, 75, 18), // "slot_setProportion"
QT_MOC_LITERAL(7, 94, 12), // "slot_vitesse"
QT_MOC_LITERAL(8, 107, 15), // "slot_setEnergie"
QT_MOC_LITERAL(9, 123, 22), // "slot_simulation_animal"
QT_MOC_LITERAL(10, 146, 14), // "Statistiques*&"
QT_MOC_LITERAL(11, 161, 11), // "statsWindow"
QT_MOC_LITERAL(12, 173, 6) // "update"

    },
    "Simulation\0signal_valeurs\0\0slot_setTailleX\0"
    "slot_setTailleY\0slot_nb_animaux\0"
    "slot_setProportion\0slot_vitesse\0"
    "slot_setEnergie\0slot_simulation_animal\0"
    "Statistiques*&\0statsWindow\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Simulation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   68,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x0a /* Public */,
       5,    1,   74,    2, 0x0a /* Public */,
       6,    1,   77,    2, 0x0a /* Public */,
       7,    1,   80,    2, 0x0a /* Public */,
       8,    1,   83,    2, 0x0a /* Public */,
       9,    1,   86,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void Simulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Simulation *_t = static_cast<Simulation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_valeurs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->slot_setTailleX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_setTailleY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_nb_animaux((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_setProportion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_vitesse((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_setEnergie((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_simulation_animal((*reinterpret_cast< Statistiques*(*)>(_a[1]))); break;
        case 8: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Simulation::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Simulation::signal_valeurs)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Simulation::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_Simulation.data,
      qt_meta_data_Simulation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Simulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Simulation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Simulation.stringdata0))
        return static_cast<void*>(const_cast< Simulation*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int Simulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void Simulation::signal_valeurs(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
