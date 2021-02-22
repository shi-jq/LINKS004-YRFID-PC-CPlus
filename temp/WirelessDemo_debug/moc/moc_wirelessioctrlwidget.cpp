/****************************************************************************
** Meta object code from reading C++ file 'wirelessioctrlwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WIRELESS/wireless/wirelessioctrlwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wirelessioctrlwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WirelessIOCtrlWidget_t {
    QByteArrayData data[12];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WirelessIOCtrlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WirelessIOCtrlWidget_t qt_meta_stringdata_WirelessIOCtrlWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WirelessIOCtrlWidget"
QT_MOC_LITERAL(1, 21, 22), // "slot_StartPort1Clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 22), // "slot_StartPort2Clicked"
QT_MOC_LITERAL(4, 68, 22), // "slot_StartPort3Clicked"
QT_MOC_LITERAL(5, 91, 22), // "slot_StartPort4Clicked"
QT_MOC_LITERAL(6, 114, 25), // "slot_CtrlOutSetBtnClicked"
QT_MOC_LITERAL(7, 140, 23), // "slot_CtrlOutSet1Clicked"
QT_MOC_LITERAL(8, 164, 23), // "slot_CtrlOutSet2Clicked"
QT_MOC_LITERAL(9, 188, 23), // "slot_CtrlOutSet3Clicked"
QT_MOC_LITERAL(10, 212, 23), // "slot_CtrlOutSet4Clicked"
QT_MOC_LITERAL(11, 236, 23) // "slot_CtrlOutSet5Clicked"

    },
    "WirelessIOCtrlWidget\0slot_StartPort1Clicked\0"
    "\0slot_StartPort2Clicked\0slot_StartPort3Clicked\0"
    "slot_StartPort4Clicked\0slot_CtrlOutSetBtnClicked\0"
    "slot_CtrlOutSet1Clicked\0slot_CtrlOutSet2Clicked\0"
    "slot_CtrlOutSet3Clicked\0slot_CtrlOutSet4Clicked\0"
    "slot_CtrlOutSet5Clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WirelessIOCtrlWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

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
    QMetaType::Void,

       0        // eod
};

void WirelessIOCtrlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WirelessIOCtrlWidget *_t = static_cast<WirelessIOCtrlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_StartPort1Clicked(); break;
        case 1: _t->slot_StartPort2Clicked(); break;
        case 2: _t->slot_StartPort3Clicked(); break;
        case 3: _t->slot_StartPort4Clicked(); break;
        case 4: _t->slot_CtrlOutSetBtnClicked(); break;
        case 5: _t->slot_CtrlOutSet1Clicked(); break;
        case 6: _t->slot_CtrlOutSet2Clicked(); break;
        case 7: _t->slot_CtrlOutSet3Clicked(); break;
        case 8: _t->slot_CtrlOutSet4Clicked(); break;
        case 9: _t->slot_CtrlOutSet5Clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WirelessIOCtrlWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WirelessIOCtrlWidget.data,
      qt_meta_data_WirelessIOCtrlWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WirelessIOCtrlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WirelessIOCtrlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WirelessIOCtrlWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WirelessIOCtrlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
