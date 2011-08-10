/****************************************************************************
** Meta object code from reading C++ file 'renderwindow.h'
**
** Created: Fri Mar 25 17:11:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scr/FrameWork/renderwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IIRenderWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x05,
      46,   16,   15,   15, 0x05,
      71,   16,   15,   15, 0x05,
     104,   98,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_IIRenderWindow[] = {
    "IIRenderWindow\0\0event\0mouseMove(QMouseEvent*)\0"
    "mousePress(QMouseEvent*)\0"
    "mouseRelease(QMouseEvent*)\0x,y,z\0"
    "cameraMove(float,float,float)\0"
};

const QMetaObject IIRenderWindow::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_IIRenderWindow,
      qt_meta_data_IIRenderWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IIRenderWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IIRenderWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IIRenderWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IIRenderWindow))
        return static_cast<void*>(const_cast< IIRenderWindow*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int IIRenderWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: mousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: mouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: cameraMove((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IIRenderWindow::mouseMove(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IIRenderWindow::mousePress(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IIRenderWindow::mouseRelease(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IIRenderWindow::cameraMove(float _t1, float _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
