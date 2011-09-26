/****************************************************************************
** Meta object code from reading C++ file 'ObjcetControl.h'
**
** Created: Thu Aug 25 17:14:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scr/ObjcetControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ObjcetControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ObjcetControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      30,   14,   14,   14, 0x0a,
      47,   14,   14,   14, 0x0a,
      73,   67,   14,   14, 0x0a,
      97,   67,   14,   14, 0x0a,
     122,   67,   14,   14, 0x0a,
     155,  149,   14,   14, 0x0a,
     193,  185,   14,   14, 0x0a,
     210,  185,   14,   14, 0x0a,
     229,  185,   14,   14, 0x0a,
     247,  185,   14,   14, 0x0a,
     268,  185,   14,   14, 0x0a,
     301,  290,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ObjcetControl[] = {
    "ObjcetControl\0\0removeObject()\0"
    "addObjectGroup()\0removeObjectGroup()\0"
    "event\0mouseMove(QMouseEvent*)\0"
    "mousePress(QMouseEvent*)\0"
    "mouseRelease(QMouseEvent*)\0x,y,z\0"
    "cameraMove(float,float,float)\0checked\0"
    "moveAction(bool)\0rotateAction(bool)\0"
    "scaleAction(bool)\0moveLockAction(bool)\0"
    "scaleLockAction(bool)\0name,value\0"
    "attributeChangle(QString,QString)\0"
};

const QMetaObject ObjcetControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ObjcetControl,
      qt_meta_data_ObjcetControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ObjcetControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ObjcetControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ObjcetControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjcetControl))
        return static_cast<void*>(const_cast< ObjcetControl*>(this));
    return QObject::qt_metacast(_clname);
}

int ObjcetControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: removeObject(); break;
        case 1: addObjectGroup(); break;
        case 2: removeObjectGroup(); break;
        case 3: mouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: mouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: cameraMove((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 7: moveAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: rotateAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: scaleAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: moveLockAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: scaleLockAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: attributeChangle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
