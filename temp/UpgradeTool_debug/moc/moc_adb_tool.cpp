/****************************************************************************
** Meta object code from reading C++ file 'adb_tool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/upgrade_tool/adb_tool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adb_tool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_adb_tool_t {
    QByteArrayData data[11];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_adb_tool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_adb_tool_t qt_meta_stringdata_adb_tool = {
    {
QT_MOC_LITERAL(0, 0, 8), // "adb_tool"
QT_MOC_LITERAL(1, 9, 22), // "on_choseButton_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 22), // "on_startButton_clicked"
QT_MOC_LITERAL(4, 56, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(5, 80, 22), // "on_checkButton_clicked"
QT_MOC_LITERAL(6, 103, 20), // "on_rebootBtn_clicked"
QT_MOC_LITERAL(7, 124, 23), // "on_uninstallBtn_clicked"
QT_MOC_LITERAL(8, 148, 21), // "on_setbootBtn_clicked"
QT_MOC_LITERAL(9, 170, 17), // "slot_SoftConfigAc"
QT_MOC_LITERAL(10, 188, 11) // "slot_ExitAc"

    },
    "adb_tool\0on_choseButton_clicked\0\0"
    "on_startButton_clicked\0on_cancelButton_clicked\0"
    "on_checkButton_clicked\0on_rebootBtn_clicked\0"
    "on_uninstallBtn_clicked\0on_setbootBtn_clicked\0"
    "slot_SoftConfigAc\0slot_ExitAc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_adb_tool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void adb_tool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        adb_tool *_t = static_cast<adb_tool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_choseButton_clicked(); break;
        case 1: _t->on_startButton_clicked(); break;
        case 2: _t->on_cancelButton_clicked(); break;
        case 3: _t->on_checkButton_clicked(); break;
        case 4: _t->on_rebootBtn_clicked(); break;
        case 5: _t->on_uninstallBtn_clicked(); break;
        case 6: _t->on_setbootBtn_clicked(); break;
        case 7: _t->slot_SoftConfigAc(); break;
        case 8: _t->slot_ExitAc(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject adb_tool::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_adb_tool.data,
      qt_meta_data_adb_tool,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *adb_tool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *adb_tool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_adb_tool.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int adb_tool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
