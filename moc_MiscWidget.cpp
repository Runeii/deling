/****************************************************************************
** Meta object code from reading C++ file 'MiscWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widgets/MiscWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MiscWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMiscWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMiscWidgetENDCLASS = QtMocHelpers::stringData(
    "MiscWidget",
    "editName",
    "",
    "editPmp",
    "editPmd",
    "editPvp",
    "editPvp2",
    "updatePmpView"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMiscWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x08,    1 /* Private */,
       3,    1,   53,    2, 0x08,    3 /* Private */,
       4,    1,   56,    2, 0x08,    5 /* Private */,
       5,    1,   59,    2, 0x08,    7 /* Private */,
       6,    1,   62,    2, 0x08,    9 /* Private */,
       7,    0,   65,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MiscWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<PageWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMiscWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMiscWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMiscWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MiscWidget, std::true_type>,
        // method 'editName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'editPmp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'editPmd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'editPvp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'editPvp2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updatePmpView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MiscWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MiscWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->editName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->editPmp((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->editPmd((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->editPvp((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->editPvp2((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->updatePmpView(); break;
        default: ;
        }
    }
}

const QMetaObject *MiscWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MiscWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMiscWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return PageWidget::qt_metacast(_clname);
}

int MiscWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
