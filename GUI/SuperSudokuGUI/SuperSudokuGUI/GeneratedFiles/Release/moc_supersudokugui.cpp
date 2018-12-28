/****************************************************************************
** Meta object code from reading C++ file 'supersudokugui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../supersudokugui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'supersudokugui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SuperSudokuGUI_t {
    QByteArrayData data[11];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SuperSudokuGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SuperSudokuGUI_t qt_meta_stringdata_SuperSudokuGUI = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SuperSudokuGUI"
QT_MOC_LITERAL(1, 15, 12), // "SelectSudoku"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "tmp"
QT_MOC_LITERAL(4, 33, 9), // "SetSudoku"
QT_MOC_LITERAL(5, 43, 5), // "Reset"
QT_MOC_LITERAL(6, 49, 7), // "NewGame"
QT_MOC_LITERAL(7, 57, 7), // "level_1"
QT_MOC_LITERAL(8, 65, 7), // "level_2"
QT_MOC_LITERAL(9, 73, 7), // "level_3"
QT_MOC_LITERAL(10, 81, 10) // "timeUpdate"

    },
    "SuperSudokuGUI\0SelectSudoku\0\0tmp\0"
    "SetSudoku\0Reset\0NewGame\0level_1\0level_2\0"
    "level_3\0timeUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SuperSudokuGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    0,   60,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    0,   62,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SuperSudokuGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SuperSudokuGUI *_t = static_cast<SuperSudokuGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SelectSudoku((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SetSudoku((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->Reset(); break;
        case 3: _t->NewGame(); break;
        case 4: _t->level_1(); break;
        case 5: _t->level_2(); break;
        case 6: _t->level_3(); break;
        case 7: _t->timeUpdate(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SuperSudokuGUI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_SuperSudokuGUI.data,
    qt_meta_data_SuperSudokuGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SuperSudokuGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SuperSudokuGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SuperSudokuGUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SuperSudokuGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
