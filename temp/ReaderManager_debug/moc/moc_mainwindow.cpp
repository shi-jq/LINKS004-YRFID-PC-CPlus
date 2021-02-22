/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/HTDEMO/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "slot_leftBtnClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "slot_downBtnClicked"
QT_MOC_LITERAL(4, 52, 14), // "slot_CutConnet"
QT_MOC_LITERAL(5, 67, 11), // "slot_ExitAc"
QT_MOC_LITERAL(6, 79, 22), // "slot_updateReaderState"
QT_MOC_LITERAL(7, 102, 11), // "nConnetType"
QT_MOC_LITERAL(8, 114, 11), // "slot_HelpAc"
QT_MOC_LITERAL(9, 126, 22), // "slot_WIFIConfigFor6CAc"
QT_MOC_LITERAL(10, 149, 17), // "slot_SoftConfigAc"
QT_MOC_LITERAL(11, 167, 20), // "slot_VersionCommonAc"
QT_MOC_LITERAL(12, 188, 20), // "slot_UpdateReadCount"
QT_MOC_LITERAL(13, 209, 5), // "count"
QT_MOC_LITERAL(14, 215, 5), // "speed"
QT_MOC_LITERAL(15, 221, 6) // "nReset"

    },
    "MainWindow\0slot_leftBtnClicked\0\0"
    "slot_downBtnClicked\0slot_CutConnet\0"
    "slot_ExitAc\0slot_updateReaderState\0"
    "nConnetType\0slot_HelpAc\0slot_WIFIConfigFor6CAc\0"
    "slot_SoftConfigAc\0slot_VersionCommonAc\0"
    "slot_UpdateReadCount\0count\0speed\0"
    "nReset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       6,    1,   68,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    3,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_leftBtnClicked(); break;
        case 1: _t->slot_downBtnClicked(); break;
        case 2: _t->slot_CutConnet(); break;
        case 3: _t->slot_ExitAc(); break;
        case 4: _t->slot_updateReaderState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_HelpAc(); break;
        case 6: _t->slot_WIFIConfigFor6CAc(); break;
        case 7: _t->slot_SoftConfigAc(); break;
        case 8: _t->slot_VersionCommonAc(); break;
        case 9: _t->slot_UpdateReadCount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
