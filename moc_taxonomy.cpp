/****************************************************************************
** Meta object code from reading C++ file 'taxonomy.h'
**
** Created: Tue Dec 4 08:09:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/taxonomy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taxonomy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Taxonomy[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      47,   45,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Taxonomy[] = {
    "Taxonomy\0\0Taxonomy_get_taxonomy_ok(QVariant)\0"
    ",\0Taxonomy_get_taxonomy_failed(int,QString)\0"
};

const QMetaObject Taxonomy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Taxonomy,
      qt_meta_data_Taxonomy, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Taxonomy::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Taxonomy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Taxonomy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Taxonomy))
        return static_cast<void*>(const_cast< Taxonomy*>(this));
    return QObject::qt_metacast(_clname);
}

int Taxonomy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Taxonomy_get_taxonomy_ok((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 1: Taxonomy_get_taxonomy_failed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
