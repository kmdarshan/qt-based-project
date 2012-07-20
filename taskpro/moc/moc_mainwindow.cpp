/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Jun 6 20:47:15 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   11,   11,   11, 0x08,
      56,   11,   11,   11, 0x08,
      82,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     191,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     269,   11,   11,   11, 0x08,
     293,   11,   11,   11, 0x08,
     310,   11,   11,   11, 0x08,
     326,   11,   11,   11, 0x08,
     338,   11,   11,   11, 0x08,
     358,  352,   11,   11, 0x08,
     387,   11,   11,   11, 0x08,
     403,  352,   11,   11, 0x08,
     454,  429,   11,   11, 0x08,
     486,   11,   11,   11, 0x08,
     504,   11,   11,   11, 0x08,
     524,   11,   11,   11, 0x08,
     542,   11,   11,   11, 0x08,
     557,   11,   11,   11, 0x08,
     574,   11,   11,   11, 0x08,
     589,   11,   11,   11, 0x08,
     626,  605,   11,   11, 0x08,
     664,   11,   11,   11, 0x08,
     689,  687,   11,   11, 0x08,
     751,  748,   11,   11, 0x08,
     786,   11,   11,   11, 0x08,
     822,   11,   11,   11, 0x08,
     866,   11,   11,   11, 0x08,
     894,   11,   11,   11, 0x08,
     932,   11,   11,   11, 0x08,
     966,   11,   11,   11, 0x08,
     996,   11,   11,   11, 0x08,
    1024,   11,   11,   11, 0x08,
    1084, 1077,   11,   11, 0x08,
    1121, 1107,   11,   11, 0x08,
    1149, 1140,   11,   11, 0x08,
    1180, 1174,   11,   11, 0x08,
    1220, 1207,   11,   11, 0x08,
    1269, 1263,   11,   11, 0x08,
    1296,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0finishedRequest()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_5_clicked()\0setupSyncPosts()\0"
    "on_actionBackup_All_Posts_2_triggered()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_clicked()\0clearDoneTasks()\0"
    "clearAllTasks()\0WriteToUI()\0backupPosts()\0"
    "reply\0finishedSlot(QNetworkReply*)\0"
    "slotReadyRead()\0slotError(QNetworkReply*)\0"
    "bytesReceived,bytesTotal\0"
    "downloadProgress(qint64,qint64)\0"
    "processResponse()\0downloadReadyRead()\0"
    "slotBackupposts()\0downloadFile()\0"
    "cancelDownload()\0httpFinished()\0"
    "httpReadyRead()\0bytesRead,totalBytes\0"
    "updateDataReadProgress(qint64,qint64)\0"
    "enableDownloadButton()\0,\0"
    "slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)\0"
    "ne\0error(QNetworkReply::NetworkError)\0"
    "on_wakeupCheckBox_stateChanged(int)\0"
    "on_notificationUiCheckBox_stateChanged(int)\0"
    "on_settingsButton_clicked()\0"
    "on_sendNotificationIdButton_clicked()\0"
    "on_notificationIdButton_clicked()\0"
    "on_unregisterButton_clicked()\0"
    "on_registerButton_clicked()\0"
    "on_notificationIconSelectionBox_highlighted(QString)\0"
    "aState\0stateChanged(QObject*)\0"
    "aNotification\0received(QObject*)\0"
    "aVersion\0versionResponse(QString)\0"
    "aData\0notificationInfo(QObject*)\0"
    "reply,errors\0sslErrors(QNetworkReply*,QList<QSslError>)\0"
    "event\0resizeEvent(QResizeEvent*)\0"
    "on_pushButton_9_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finishedRequest(); break;
        case 1: on_pushButton_8_clicked(); break;
        case 2: on_pushButton_6_clicked(); break;
        case 3: on_pushButton_7_clicked(); break;
        case 4: on_pushButton_5_clicked(); break;
        case 5: setupSyncPosts(); break;
        case 6: on_actionBackup_All_Posts_2_triggered(); break;
        case 7: on_pushButton_4_clicked(); break;
        case 8: on_pushButton_3_clicked(); break;
        case 9: on_pushButton_2_clicked(); break;
        case 10: on_pushButton_clicked(); break;
        case 11: clearDoneTasks(); break;
        case 12: clearAllTasks(); break;
        case 13: WriteToUI(); break;
        case 14: backupPosts(); break;
        case 15: finishedSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: slotReadyRead(); break;
        case 17: slotError((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 18: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 19: processResponse(); break;
        case 20: downloadReadyRead(); break;
        case 21: slotBackupposts(); break;
        case 22: downloadFile(); break;
        case 23: cancelDownload(); break;
        case 24: httpFinished(); break;
        case 25: httpReadyRead(); break;
        case 26: updateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 27: enableDownloadButton(); break;
        case 28: slotAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 29: error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 30: on_wakeupCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: on_notificationUiCheckBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: on_settingsButton_clicked(); break;
        case 33: on_sendNotificationIdButton_clicked(); break;
        case 34: on_notificationIdButton_clicked(); break;
        case 35: on_unregisterButton_clicked(); break;
        case 36: on_registerButton_clicked(); break;
        case 37: on_notificationIconSelectionBox_highlighted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: stateChanged((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 39: received((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 40: versionResponse((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: notificationInfo((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 42: sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        case 43: resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 44: on_pushButton_9_clicked(); break;
        default: ;
        }
        _id -= 45;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::finishedRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
