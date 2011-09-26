/****************************************************************************
** Meta object code from reading C++ file 'DataEditorControl.h'
**
** Created: Sun Aug 21 13:36:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scr/dataeditor/DataEditorControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataEditorControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataEditorControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   19,   18,   18, 0x0a,
      47,   19,   18,   18, 0x0a,
      71,   18,   18,   18, 0x0a,
      80,   18,   18,   18, 0x0a,
      90,   18,   18,   18, 0x0a,
     103,   18,   18,   18, 0x0a,
     116,   18,   18,   18, 0x0a,
     127,   18,   18,   18, 0x0a,
     138,   18,   18,   18, 0x0a,
     151,   18,   18,   18, 0x0a,
     164,   18,   18,   18, 0x0a,
     177,   18,   18,   18, 0x0a,
     190,   18,   18,   18, 0x0a,
     201,   18,   18,   18, 0x0a,
     212,   18,   18,   18, 0x0a,
     224,   18,   18,   18, 0x0a,
     236,   18,   18,   18, 0x0a,
     247,   18,   18,   18, 0x0a,
     258,   18,   18,   18, 0x0a,
     270,   18,   18,   18, 0x0a,
     282,   18,   18,   18, 0x0a,
     293,   18,   18,   18, 0x0a,
     304,   18,   18,   18, 0x0a,
     320,   18,   18,   18, 0x0a,
     336,   18,   18,   18, 0x0a,
     348,   18,   18,   18, 0x0a,
     367,  360,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DataEditorControl[] = {
    "DataEditorControl\0\0text\0ModBoxChanged(QString)\0"
    "LangBoxChanged(QString)\0AddMod()\0"
    "AddLang()\0AddSoldier()\0DelSoldier()\0"
    "AddHorse()\0DelHorse()\0AddPWeapon()\0"
    "DelPWeapon()\0AddSWeapon()\0DelSWeapon()\0"
    "AddArmor()\0DelArmor()\0AddShield()\0"
    "DelShield()\0AddSkill()\0DelSkill()\0"
    "AddEffect()\0DelEffect()\0AddSquad()\0"
    "DelSquad()\0AddSquadSkill()\0DelSquadSkill()\0"
    "AddString()\0DelString()\0_index\0"
    "SelectSquad(QModelIndex)\0"
};

const QMetaObject DataEditorControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataEditorControl,
      qt_meta_data_DataEditorControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataEditorControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataEditorControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataEditorControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataEditorControl))
        return static_cast<void*>(const_cast< DataEditorControl*>(this));
    return QObject::qt_metacast(_clname);
}

int DataEditorControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ModBoxChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: LangBoxChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: AddMod(); break;
        case 3: AddLang(); break;
        case 4: AddSoldier(); break;
        case 5: DelSoldier(); break;
        case 6: AddHorse(); break;
        case 7: DelHorse(); break;
        case 8: AddPWeapon(); break;
        case 9: DelPWeapon(); break;
        case 10: AddSWeapon(); break;
        case 11: DelSWeapon(); break;
        case 12: AddArmor(); break;
        case 13: DelArmor(); break;
        case 14: AddShield(); break;
        case 15: DelShield(); break;
        case 16: AddSkill(); break;
        case 17: DelSkill(); break;
        case 18: AddEffect(); break;
        case 19: DelEffect(); break;
        case 20: AddSquad(); break;
        case 21: DelSquad(); break;
        case 22: AddSquadSkill(); break;
        case 23: DelSquadSkill(); break;
        case 24: AddString(); break;
        case 25: DelString(); break;
        case 26: SelectSquad((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
