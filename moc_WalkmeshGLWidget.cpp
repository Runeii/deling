/****************************************************************************
** Meta object code from reading C++ file 'WalkmeshGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "WalkmeshGLWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WalkmeshGLWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWalkmeshGLWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSWalkmeshGLWidgetENDCLASS = QtMocHelpers::stringData(
    "WalkmeshGLWidget",
    "setXRotation",
    "",
    "setYRotation",
    "setZRotation",
    "setZoom",
    "resetCamera",
    "setCurrentFieldCamera",
    "camID",
    "setSelectedTriangle",
    "triangle",
    "setSelectedDoor",
    "door",
    "setSelectedGate",
    "gate",
    "setLineToDraw",
    "const Vertex_s[2]",
    "vertex",
    "clearLineToDraw"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWalkmeshGLWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x0a,    1 /* Public */,
       3,    1,   83,    2, 0x0a,    3 /* Public */,
       4,    1,   86,    2, 0x0a,    5 /* Public */,
       5,    1,   89,    2, 0x0a,    7 /* Public */,
       6,    0,   92,    2, 0x0a,    9 /* Public */,
       7,    1,   93,    2, 0x0a,   10 /* Public */,
       9,    1,   96,    2, 0x0a,   12 /* Public */,
      11,    1,   99,    2, 0x0a,   14 /* Public */,
      13,    1,  102,    2, 0x0a,   16 /* Public */,
      15,    1,  105,    2, 0x0a,   18 /* Public */,
      18,    0,  108,    2, 0x0a,   20 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject WalkmeshGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWalkmeshGLWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWalkmeshGLWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWalkmeshGLWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WalkmeshGLWidget, std::true_type>,
        // method 'setXRotation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setYRotation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setZRotation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setZoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'resetCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setCurrentFieldCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setSelectedTriangle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setSelectedDoor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setSelectedGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setLineToDraw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Vertex_s, std::false_type>,
        // method 'clearLineToDraw'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void WalkmeshGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WalkmeshGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setXRotation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->setYRotation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->setZRotation((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setZoom((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->resetCamera(); break;
        case 5: _t->setCurrentFieldCamera((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->setSelectedTriangle((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->setSelectedDoor((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->setSelectedGate((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->setLineToDraw((*reinterpret_cast< std::add_pointer_t<const Vertex_s[2]>>(_a[1]))); break;
        case 10: _t->clearLineToDraw(); break;
        default: ;
        }
    }
}

const QMetaObject *WalkmeshGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WalkmeshGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWalkmeshGLWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int WalkmeshGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
