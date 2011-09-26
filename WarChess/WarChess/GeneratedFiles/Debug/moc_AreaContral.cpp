/****************************************************************************
** Meta object code from reading C++ file 'AreaContral.h'
**
** Created: Sun Aug 21 13:36:14 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scr/AreaContral.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AreaContral.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AreaControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      54,   12,   12,   12, 0x0a,
      64,   12,   12,   12, 0x0a,
      77,   12,   12,   12, 0x0a,
      88,   12,   12,   12, 0x0a,
     105,   99,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AreaControl[] = {
    "AreaControl\0\0event\0mousePress(QMouseEvent*)\0"
    "AddArea()\0DelArea()\0CancelArea()\0"
    "AddCoord()\0DelCoord()\0index\0"
    "ChooseArea(QModelIndex)\0"
};

const QMetaObject AreaControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AreaControl,
      qt_meta_data_AreaControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AreaControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AreaControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AreaControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AreaControl))
        return static_cast<void*>(const_cast< AreaControl*>(this));
    return QObject::qt_metacast(_clname);
}

int AreaControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: AddArea(); break;
        case 2: DelArea(); break;
        case 3: CancelArea(); break;
        case 4: AddCoord(); break;
        case 5: DelCoord(); break;
        case 6: ChooseArea((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
