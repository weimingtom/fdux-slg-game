/****************************************************************************
** Meta object code from reading C++ file 'scripteditor.h'
**
** Created: Fri Feb 25 10:29:52 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Scr/scripteditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scripteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptEditor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      32,   13,   13,   13, 0x0a,
      53,   13,   13,   13, 0x0a,
      71,   13,   13,   13, 0x0a,
      88,   13,   13,   13, 0x0a,
     109,   13,   13,   13, 0x0a,
     134,   13,   13,   13, 0x0a,
     152,   13,   13,   13, 0x0a,
     167,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptEditor[] = {
    "ScriptEditor\0\0showImageButton()\0"
    "SetTextColorButton()\0SetDialogButton()\0"
    "ShowTextButton()\0ShowRoleNameButton()\0"
    "SetRoleNameColorButton()\0ClearTextButton()\0"
    "RunLuaScript()\0ParseScript()\0"
};

const QMetaObject ScriptEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ScriptEditor,
      qt_meta_data_ScriptEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptEditor))
        return static_cast<void*>(const_cast< ScriptEditor*>(this));
    if (!strcmp(_clname, "Ogre::WindowEventListener"))
        return static_cast< Ogre::WindowEventListener*>(const_cast< ScriptEditor*>(this));
    if (!strcmp(_clname, "LuaSystemListener"))
        return static_cast< LuaSystemListener*>(const_cast< ScriptEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ScriptEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showImageButton(); break;
        case 1: SetTextColorButton(); break;
        case 2: SetDialogButton(); break;
        case 3: ShowTextButton(); break;
        case 4: ShowRoleNameButton(); break;
        case 5: SetRoleNameColorButton(); break;
        case 6: ClearTextButton(); break;
        case 7: RunLuaScript(); break;
        case 8: ParseScript(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
