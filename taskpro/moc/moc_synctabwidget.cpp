/****************************************************************************
** Meta object code from reading C++ file 'synctabwidget.h'
**
** Created: Mon Jun 6 20:47:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../synctabwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'synctabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SyncTabWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      41,   14,   14,   14, 0x08,
      67,   14,   14,   14, 0x08,
      93,   14,   14,   14, 0x08,
     117,   14,   14,   14, 0x08,
     132,   14,   14,   14, 0x08,
     149,   14,   14,   14, 0x08,
     164,   14,   14,   14, 0x08,
     201,  180,   14,   14, 0x08,
     239,   14,   14,   14, 0x08,
     264,  262,   14,   14, 0x08,
     326,  323,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SyncTabWidget[] = {
    "SyncTabWidget\0\0on_pushButton_4_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_clicked()\0downloadFile()\0"
    "cancelDownload()\0httpFinished()\0"
    "httpReadyRead()\0bytesRead,totalBytes\0"
    "updateDataReadProgress(qint64,qint64)\0"
    "enableDownloadButton()\0,\0"
    "slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)\0"
    "ne\0error(QNetworkReply::NetworkError)\0"
};

const QMetaObject SyncTabWidget::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_SyncTabWidget,
      qt_meta_data_SyncTabWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SyncTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SyncTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SyncTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SyncTabWidget))
        return static_cast<void*>(const_cast< SyncTabWidget*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int SyncTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_4_clicked(); break;
        case 1: on_pushButton_3_clicked(); break;
        case 2: on_pushButton_2_clicked(); break;
        case 3: on_pushButton_clicked(); break;
        case 4: downloadFile(); break;
        case 5: cancelDownload(); break;
        case 6: httpFinished(); break;
        case 7: httpReadyRead(); break;
        case 8: updateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 9: enableDownloadButton(); break;
        case 10: slotAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 11: error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
