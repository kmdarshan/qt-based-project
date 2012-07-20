#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFileInfo>
#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
class HttpCommunicator;
class QNetworkReply;
class QNetworkRequest;
class QIODevice;
class QFile;
#include <QNetworkConfigurationManager>
class OviNotificationSession;
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString getNokiaUserID();
    void setUpNotifications();
    QString getSyncEmail();
    QString getSyncPin();
    void setInfo();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkEmail();
    //QString getEmail();
    //QString getPin();
    void checkPin();
    void createFiles();
    void displayErrorbox(QString qError);
    //QNetworkAccessManager m_manager2;
    QNetworkAccessManager m_manager;
    QNetworkRequest* m_networkRequest;
    QNetworkReply* m_networkReply;
    void sendHttpRequests(QString url);
    static void encodeQueryItems(QUrl& url);
    QString m_networkReplyBody;
    int m_downloadProgress;
    int m_uploadProgress;
    QUrl m_url;
    void appendHeaders();
    HttpCommunicator* m_httpCommunicator;

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
    void displayAllSyncPosts();
    //void setEmail();
    //void setPin();
    bool writeFiles(QString filename,
                                QString qstr,
                                bool qbool,
                                QString qmessage);
    QString readFiles(QString fileName);
private:
    Ui::MainWindow *ui;

signals:
  void finishedRequest();
private slots:
  void on_pushButton_8_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_5_clicked();
  void setupSyncPosts();
    void on_actionBackup_All_Posts_2_triggered();
    //void on_actionBackup_All_Posts_triggered();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void clearDoneTasks();
    void clearAllTasks();
    void WriteToUI();
    //void setReminder();
    //void setEmail();
    void backupPosts();
    //void setPin();
    //void displayHelp();
    void finishedSlot(QNetworkReply* reply);
    void slotReadyRead();
    void slotError(QNetworkReply* reply);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void processResponse();
    virtual void downloadReadyRead();
    void slotBackupposts();
    //Slots for httprequest
    void downloadFile();
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
    void error(QNetworkReply::NetworkError ne);

private slots:
    void on_wakeupCheckBox_stateChanged(int );
    void on_notificationUiCheckBox_stateChanged(int );
    void on_settingsButton_clicked();
    void on_sendNotificationIdButton_clicked();
    void on_notificationIdButton_clicked();
    void on_unregisterButton_clicked();
    void on_registerButton_clicked();
    void on_notificationIconSelectionBox_highlighted(QString );

private slots:


    /*!
     * State of the Notifications application session has been changed. Check the new state
     * and possible error.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aMessage OviNotificationMessage from OviNotificationInterface.
     */
    void stateChanged(QObject* aState);

    /*!
     * Received notification from the Notifications service.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aNotification OviNotificationMessage from OviNotificationInterface.
     */
    void received(QObject* aNotification);

    /*!
     * Callback for version request
     *
     */
    void versionResponse(QString aVersion);

    /*!
     * Address for the service to identify Notifications application.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aData OviNotificationMessage from OviNotificationInterface.
     */
    void notificationInfo(QObject* aData);

    /*!
     * Callback for handling possible SSL errors
     *
     */
    void sslErrors(QNetworkReply * reply, const QList<QSslError> & errors);

    /*!
     * Handles orientation change
     *
     */
    void resizeEvent (QResizeEvent* event);

    void on_pushButton_9_clicked();

private:

    /*!
     * Loads Notifications Enabler interface and connects the signals to example application.
     */
    bool initialize();

private:
    OviNotificationSession*   iNotificationSession;
    QString                     iIconData;
    QNetworkAccessManager*      iHttpManager;
    QString                     iNotificationId;


};

#endif // MAINWINDOW_H
