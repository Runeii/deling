/****************************************************************************
** Meta object code from reading C++ file 'MsdWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widgets/MsdWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MsdWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMsdWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMsdWidgetENDCLASS = QtMocHelpers::stringData(
    "MsdWidget",
    "textIdChanged",
    "",
    "fromChanged",
    "gotoText",
    "textID",
    "from",
    "size",
    "specialCharactersDialog",
    "fillTextEdit",
    "QListWidgetItem*",
    "updateCurrentText",
    "emitFromChanged",
    "prevTextPreviewPage",
    "nextTextPreviewPage",
    "changeTextPreviewPage",
    "prevTextPreviewWin",
    "nextTextPreviewWin",
    "changeTextPreviewWin",
    "changeCoord",
    "point",
    "changeXCoord",
    "changeYCoord",
    "insertTag",
    "QAction*",
    "insertTextAbove",
    "insertText",
    "removeText"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMsdWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x06,    1 /* Public */,
       3,    1,  137,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    3,  140,    2, 0x0a,    5 /* Public */,
       8,    0,  147,    2, 0x08,    9 /* Private */,
       9,    1,  148,    2, 0x08,   10 /* Private */,
      11,    0,  151,    2, 0x08,   12 /* Private */,
      12,    0,  152,    2, 0x08,   13 /* Private */,
      13,    0,  153,    2, 0x08,   14 /* Private */,
      14,    0,  154,    2, 0x08,   15 /* Private */,
      15,    0,  155,    2, 0x08,   16 /* Private */,
      16,    0,  156,    2, 0x08,   17 /* Private */,
      17,    0,  157,    2, 0x08,   18 /* Private */,
      18,    0,  158,    2, 0x08,   19 /* Private */,
      19,    1,  159,    2, 0x08,   20 /* Private */,
      21,    1,  162,    2, 0x08,   22 /* Private */,
      22,    1,  165,    2, 0x08,   24 /* Private */,
      23,    1,  168,    2, 0x08,   26 /* Private */,
      25,    0,  171,    2, 0x08,   28 /* Private */,
      26,    0,  172,    2, 0x08,   29 /* Private */,
      27,    0,  173,    2, 0x08,   30 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   20,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MsdWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PageWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMsdWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMsdWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMsdWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MsdWidget, std::true_type>,
        // method 'textIdChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fromChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'gotoText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'specialCharactersDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fillTextEdit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'updateCurrentText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'emitFromChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prevTextPreviewPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextTextPreviewPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeTextPreviewPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prevTextPreviewWin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextTextPreviewWin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeTextPreviewWin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeCoord'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'changeXCoord'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'changeYCoord'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'insertTag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAction *, std::false_type>,
        // method 'insertTextAbove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MsdWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsdWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->textIdChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->fromChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->gotoText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 3: _t->specialCharactersDialog(); break;
        case 4: _t->fillTextEdit((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 5: _t->updateCurrentText(); break;
        case 6: _t->emitFromChanged(); break;
        case 7: _t->prevTextPreviewPage(); break;
        case 8: _t->nextTextPreviewPage(); break;
        case 9: _t->changeTextPreviewPage(); break;
        case 10: _t->prevTextPreviewWin(); break;
        case 11: _t->nextTextPreviewWin(); break;
        case 12: _t->changeTextPreviewWin(); break;
        case 13: _t->changeCoord((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 14: _t->changeXCoord((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->changeYCoord((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->insertTag((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 17: _t->insertTextAbove(); break;
        case 18: _t->insertText(); break;
        case 19: _t->removeText(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MsdWidget::*)(int );
            if (_t _q_method = &MsdWidget::textIdChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MsdWidget::*)(int );
            if (_t _q_method = &MsdWidget::fromChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MsdWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MsdWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMsdWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return PageWidget::qt_metacast(_clname);
}

int MsdWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MsdWidget::textIdChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MsdWidget::fromChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
