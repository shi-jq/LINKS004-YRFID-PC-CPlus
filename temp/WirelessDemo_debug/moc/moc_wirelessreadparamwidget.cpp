/****************************************************************************
** Meta object code from reading C++ file 'wirelessreadparamwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WIRELESS/wireless/wirelessreadparamwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wirelessreadparamwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WirelessReadParamWidget_t {
    QByteArrayData data[10];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WirelessReadParamWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WirelessReadParamWidget_t qt_meta_stringdata_WirelessReadParamWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "WirelessReadParamWidget"
QT_MOC_LITERAL(1, 24, 26), // "slot_FlashEnableBtnClicked"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 28), // "slot_FlashTagCountBtnClicked"
QT_MOC_LITERAL(4, 81, 28), // "slot_FlashTagClearBtnClicked"
QT_MOC_LITERAL(5, 110, 27), // "slot_FilterEnableBtnClicked"
QT_MOC_LITERAL(6, 138, 25), // "slot_FilterTimeBtnClicked"
QT_MOC_LITERAL(7, 164, 30), // "slot_QueryFilterTimeBtnClicked"
QT_MOC_LITERAL(8, 195, 21), // "slot_QueryFlashEnable"
QT_MOC_LITERAL(9, 217, 16) // "slot_QueryFilter"

    },
    "WirelessReadParamWidget\0"
    "slot_FlashEnableBtnClicked\0\0"
    "slot_FlashTagCountBtnClicked\0"
    "slot_FlashTagClearBtnClicked\0"
    "slot_FilterEnableBtnClicked\0"
    "slot_FilterTimeBtnClicked\0"
    "slot_QueryFilterTimeBtnClicked\0"
    "slot_QueryFlashEnable\0slot_QueryFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WirelessReadParamWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void WirelessReadParamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WirelessReadParamWidget *_t = static_cast<WirelessReadParamWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_FlashEnableBtnClicked(); break;
        case 1: _t->slot_FlashTagCountBtnClicked(); break;
        case 2: _t->slot_FlashTagClearBtnClicked(); break;
        case 3: _t->slot_FilterEnableBtnClicked(); break;
        case 4: _t->slot_FilterTimeBtnClicked(); break;
        case 5: _t->slot_QueryFilterTimeBtnClicked(); break;
        case 6: _t->slot_QueryFlashEnable(); break;
        case 7: _t->slot_QueryFilter(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WirelessReadParamWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WirelessReadParamWidget.data,
      qt_meta_data_WirelessReadParamWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WirelessReadParamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WirelessReadParamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WirelessReadParamWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WirelessReadParamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
