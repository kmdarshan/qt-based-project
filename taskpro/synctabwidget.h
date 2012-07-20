#ifndef SYNCTABWIDGET_H
#define SYNCTABWIDGET_H

#include <QTabWidget>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QUrl>
#include <QDebug>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFileInfo>

#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFile;
class QLabel;
class QLineEdit;
class QProgressDialog;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;


QT_END_NAMESPACE

namespace Ui {
    class SyncTabWidget;
}

class SyncTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit SyncTabWidget(QWidget *parent = 0);
    ~SyncTabWidget();
    QString getEmail();
    QString getPin();
    QString m_syncPost;
    QString m_syncPassword;
    QString m_syncEmail;

    //For httprequest for SYNC
    QUrl url;
    QNetworkAccessManager qnam;
    //QNetworkConfigurationManager qconfnet;
    QNetworkReply *reply;
    int httpGetId;
    bool httpRequestAborted;
    int retryCount;
    void startRequest(QUrl url);
    QFile *file;


private:
    Ui::SyncTabWidget *ui;
private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    //Slots for httprequest
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
    void error(QNetworkReply::NetworkError ne);
/*#ifndef QT_NO_OPENSSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif*/

};

#endif // SYNCTABWIDGET_H
