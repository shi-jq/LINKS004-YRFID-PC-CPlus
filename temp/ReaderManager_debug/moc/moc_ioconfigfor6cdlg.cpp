/****************************************************************************
** Meta object code from reading C++ file 'ioconfigfor6cdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/HTDEMO/ioconfigfor6cdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ioconfigfor6cdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IoConfigFor6CDlg_t {
    QByteArrayData data[9];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IoConfigFor6CDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IoConfigFor6CDlg_t qt_meta_stringdata_IoConfigFor6CDlg = {
    {
QT_MOC_LITERAL(0, 0, 16), // "IoConfigFor6CDlg"
QT_MOC_LITERAL(1, 17, 22), // "slot_QueryInBtnClicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "slot_Putout1BtnClicked"
QT_MOC_LITERAL(4, 64, 22), // "slot_Putout2BtnClicked"
QT_MOC_LITERAL(5, 87, 22), // "slot_Putout3BtnClicked"
QT_MOC_LITERAL(6, 110, 22), // "slot_Putout4BtnClicked"
QT_MOC_LITERAL(7, 133, 27), // "slot_CtrlOutQueryBtnClicked"
QT_MOC_LITERAL(8, 161, 25) // "slot_CtrlOutSetBtnClicked"

    },
    "IoConfigFor6CDlg\0slot_QueryInBtnClicked\0"
    "\0slot_Putout1BtnClicked\0slot_Putout2BtnClicked\0"
    "slot_Putout3BtnClicked\0slot_Putout4BtnClicked\0"
    "slot_CtrlOutQueryBtnClicked\0"
    "slot_CtrlOutSetBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IoConfigFor6CDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IoConfigFor6CDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IoConfigFor6CDlg *_t = static_cast<IoConfigFor6CDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_QueryInBtnClicked(); break;
        case 1: _t->slot_Putout1BtnClicked(); break;
        case 2: _t->slot_Putout2BtnClicked(); break;
        case 3: _t->slot_Putout3BtnClicked(); break;
        case 4: _t->slot_Putout4BtnClicked(); break;
        case 5: _t->slot_CtrlOutQueryBtnClicked(); break;
        case 6: _t->slot_CtrlOutSetBtnClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject IoConfigFor6CDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IoConfigFor6CDlg.data,
      qt_meta_data_IoConfigFor6CDlg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IoConfigFor6CDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IoConfigFor6CDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IoConfigFor6CDlg.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int IoConfigFor6CDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
