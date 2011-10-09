/****************************************************************************
** Meta object code from reading C++ file 'ToolBarControl.h'
**
** Created: Sun Oct 9 10:44:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Src/ToolBarControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolBarControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolBarControl[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ToolBarControl[] = {
    "ToolBarControl\0\0checked\0addAction(bool)\0"
};

const QMetaObject ToolBarControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ToolBarControl,
      qt_meta_data_ToolBarControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ToolBarControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ToolBarControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ToolBarControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBarControl))
        return static_cast<void*>(const_cast< ToolBarControl*>(this));
    return QObject::qt_metacast(_clname);
}

int ToolBarControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addAction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
