#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QList"
#include "QListWidgetItem"
#include "QFile"
#include "QString"
#include "QTextStream"
#include "QMessageBox"
#include "QPalette"
#include "QDebug"
#include "QLabel"
#include "QCompleter"
#include "QNetworkAccessManager"
#include "QMessageBox"
#include "QDateTime"
#include "QDebug"
#include <sstream>
#include <QString>
#include "finddialog.h"
#include "dialog.h"
#include <QGridLayout>

#include <QtGui>
#include <QPluginLoader>
#include <QHttpRequestHeader>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>

// Notifications
#include <ovinotificationinterface.h>
#include <ovinotificationsession.h>
#include <ovinotificationinfo.h>
#include <ovinotificationmessage.h>
#include <ovinotificationstate.h>
#include <ovinotificationpayload.h>

/*
* You can request your own application and service id from:
* https://projects.forum.nokia.com/notificationsapi/wiki/registerservice
*
* Public "example.com" service can be used for testing.
* Sending Notification Id to "example.com" service is not supported.
*/

const QString application_id = "com.taskpro";
const QString service_id = "taskpro.com";

/* HTTP Proxy definition, if needed for sending notifications.
   If left empty, system wide proxy configuration will be used
 */
const QString http_proxy = "";
const int proxy_port = 8080;

#include "httpcommunicator.h"
#define NOTIFY_FILE "notify.txt"
#define TASK_DB_NAME "taskproDB.txt"
#define NOKIA_USER_ID "nokia_user_id.txt"
#define EMAIL "email.txt"
#define PIN "pin.txt"
#define WEB_ADDRESS "http://www.kmdarshan.com/qt/"
#define SYNC_EMAIL_FILE "syncEmail.txt"
#define SYNC_PASSWORD_FILE "syncPassword.txt"
#define SYNC_POSTS_FILE "syncPosts.txt"
#define SYNC_URL "http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?"
#define SYNC_URL_DISPLAY "http://www.kmdarshan.com/qt/displaySyncPosts.php?"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        m_httpCommunicator(NULL)
{
    ui->setupUi(this);
    this->setWindowTitle("TASK PRO");
    ui->scrollArea->ensureWidgetVisible(ui->pushButton_7,50,50);

    //Create all the files needed
    createFiles();

    //this->showMaximized();
    /*ui->plainTextEdit->setPlainText("How to sync: \n"\
                                    "Enter handle and pin in this phone. "\
                                    "Give this handle and pin to any other "\
                                    "person you want to sync your posts with."\
                                    "\nExample: set handle as tom"\
                                    "set pin as 12345"\
                                    "Now give the same pin to your wife or friend."\
                                    "When they enter the same handle and pin, you both "\
                                    "would receive the same posts."\
                                    "\n\nBackup posts:"\
                                    "Enter email and password."\
                                    "Goto File->Backup posts\n"\
                                    "\n\n Reminders:"\
                                    "Click on remind."\
                                    "Set the date and time."\
                                    "Reminders will be send to your email."\
                                    "\n\n Issues: \nkmdarshan@gmail.com");*/

    setInfo();
    /*QString qEmail=getEmail();
    QString qPwd=getPin();
    QString qSEmail=getSyncEmail();
    QString qSPin=getSyncPin();
    QString finalStr = "<b>Email: </b> "+qEmail+"<br><br> <b>Password: </b> "+
                       qPwd+"<br><br> <b>Sync Handle: </b>"+
                       qSEmail+"<br><br> <b>Sync Pin: </b>"+qSPin;
    ui->textBrowser->setText(finalStr);*/
    connect(ui->actionRemove_Done_Tasks, SIGNAL(triggered()), this, SLOT(clearDoneTasks()));
    connect(ui->actionRemove_All_Tasks, SIGNAL(triggered()), this, SLOT(clearAllTasks()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_pushButton_4_clicked()));
    connect(ui->actionSync_Posts, SIGNAL(triggered()),this, SLOT(setupSyncPosts()));

    QString fileName =TASK_DB_NAME;
    displayAllSyncPosts();
    //checkEmail();
    //checkPin();
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: Opening the DB for writing.\n contact admin@kmdarshan.com");
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            if(line.startsWith("DELETE ", Qt::CaseInsensitive) == true)
            {
                line.remove(0,7);
                QListWidgetItem *item=new QListWidgetItem;
                QFont f("Helvetica");
                f.setStrikeOut(true);
                item->setFont(f);
                item->setIcon(QIcon(":/images/Done.png"));
                item->setText(line);
                ui->listWidget->addItem(item);
            }else{
                QListWidgetItem *item=new QListWidgetItem;
                QFont f("Helvetica");
                //f.setStrikeOut(false);
                item->setFont(f);
                item->setIcon(QIcon(":/images/red.png"));
                item->setText(line);
                //item=new QListWidgetItem(QIcon(":/images/red.png"),line,ui->listWidget);
                ui->listWidget->addItem(item);
            }

            line = in.readLine();
        }
        file.close();
    }

}

bool MainWindow::writeFiles(QString fileName,
                            QString qstr,
                            bool qbool,
                            QString qmessage)
{

            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly)) {
                    displayErrorbox("Error: Could not open file.\n Contact admin@kmdarshan.com");
                    return false;
                }
                QTextStream stream(&file);
                stream<<qstr;
                if(qbool)
                    displayErrorbox(qmessage);
                file.close();
                return true;
            }
            return false;
}
QString MainWindow::readFiles(QString fileName)
{
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: Could not open file. Contact kmdarshan@gmail.com");
            return "error";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "error";
}
#include "MainWindow.h"
void MainWindow::setupSyncPosts()
{
   this->hide();
   //this->close();
   //MainWindow *sf=new MainWindow;
   //qDebug()<<"in sync";
   //sf->show();
   //sf->showFullScreen();
   //sf->showMaximized();
}

//#include "helpdialog.h"
/*void MainWindow::displayHelp()
{
    //HelpDialog hd;
    //hd.exec();
}*/

void MainWindow::displayErrorbox(QString qError)
{
    QMessageBox::information(this, tr("Error"),
                             qError);
}
QString gbackupurl="";
QTimer* backupTimer;
long gBackupEpochtime;
long gBackupEpochStartime;
void MainWindow::slotBackupposts()
{
    //qDebug()<<"inside b slot "<<gbackupurl;
    //qDebug()<<"current epochtime backup"<<gBackupEpochtime;
    QString strCurrenttime=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    QDateTime qdTemptime = QDateTime::fromString(strCurrenttime, "yyyy.MM.dd hh:mm:ss");
    gBackupEpochtime=qdTemptime.toTime_t();
    //qDebug()<<"end epoch time"<<gBackupEpochtime;

    if((gBackupEpochtime - gBackupEpochStartime)>2)
    {

        backupTimer->stop();
        //qDebug()<<"timer stopped";
        sendHttpRequests(gbackupurl);
    }else
    {
        //qDebug()<<"Time difference is "<<(gBackupEpochtime - gBackupEpochStartime);
    }
}

void MainWindow::backupPosts()
{
    //displayErrorbox("Coming soon!!!!");
    //qDebug()<<"Inside bac pu posts";
    checkEmail();
    checkPin();

    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() <1)
        return;
    int iCRow = ui->listWidget->currentRow();
    QListWidgetItem *qlwItem = ui->listWidget->takeItem(iCRow);
    QString qStr=qlwItem->text();
    if(qStr.length()<2)
    {
        displayErrorbox("No post to backup");
    }else
    {
        if(qStr.startsWith('.')==true)
        {
            qStr = qStr;
            displayErrorbox("cannot backup finished tasks");
        }
        else
        {
            QString sEmail=getNokiaUserID();
            QString sFinalPath=WEB_ADDRESS;
            sFinalPath+="insertpost.php?post=";
            QString sPost;
            QString sPin="";
            //Add it to the database
            sPost=qStr;
            QString sDate=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
            sDate.replace(" ","+");
            sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date="+sDate+"&pin="+sPin;
            sendHttpRequests(sFinalPath);
            QListWidgetItem *item=new QListWidgetItem;
            QFont f("Helvetica");
            //f.setStrikeOut(true);
            item->setFont(f);
            item->setIcon(QIcon(":/images/red.png"));
            item->setText(qStr);
            /*QListWidgetItem *item;
                item=new QListWidgetItem(QIcon(":/images/red.png"),qStr,ui->listWidget);*/
            ui->listWidget->addItem(item);
            ui->listWidget->setCurrentItem(item);
        }
    }



    /*QList<QListWidgetItem*>::iterator i;
    QList<QListWidgetItem*> items;

    items = ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    for (i = items.begin(); i != items.end(); ++i)
    {
        gbackupurl="";
        QString strCurrenttime=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        QDateTime qdTemptime = QDateTime::fromString(strCurrenttime, "yyyy.MM.dd hh:mm:ss");
        gBackupEpochStartime=qdTemptime.toTime_t();
        qDebug()<<"start epoch time"<<gBackupEpochStartime;
        //Sample URL
        //WEB_ADDRESSinsertpost.php?post=darshan+sucks&email=divyadarshankm%40yahoo.com
        QListWidgetItem *qlwItem;
        qlwItem=*i;
        QString qsTxt=qlwItem->text();
        //QNetworkAccessManager* m_manager = new QNetworkAccessManager(this);
        QString sDate=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        sDate.replace(" ","+");
        ////qDebug()()<<sDate;
        QString sEmail=getEmail();
        QString sFinalPath=WEB_ADDRESS;
        sFinalPath+="insertpost.php?post=";
        QString sPost;
        QString sPin=getPin();
        if(qsTxt.startsWith("."))
        {
            sPost="DELETE ";
            sPost+=qsTxt;
        }
        //Add it to the database
        sPost=qsTxt;
        sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date="+sDate+"&pin="+sPin;
        QString strCurrenttime1=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
        QDateTime qdTemptime1 = QDateTime::fromString(strCurrenttime1, "yyyy.MM.dd hh:mm:ss");
        qDebug()<<"URL "<<sFinalPath;
        sendHttpRequests(sFinalPath);
        long epochStartime=qdTemptime1.toTime_t();
        long diff=0;
        while(diff < 5)
        {
            QString strCurrenttime2=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
            QDateTime qdTemptime2 = QDateTime::fromString(strCurrenttime2, "yyyy.MM.dd hh:mm:ss");
            long epochendime=qdTemptime2.toTime_t();
            //qDebug()<<"End time"<<epochendime;
            diff=epochendime-epochStartime;
            //qDebug()<<"Diff = >"<<diff;
            if(m_httpCommunicator->getBackupvariable()=="true")
            {
                qDebug()<<"Its true";
                break;
            }
        }

        backupTimer = new QTimer;
        gbackupurl = sFinalPath;
        connect(backupTimer, SIGNAL(timeout()), this, SLOT(slotBackupposts()));
        backupTimer->start(3000);

        qDebug()<<"finished "<<diff;

    }*/
}

void MainWindow::checkEmail()
{
    QString fileName =EMAIL;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: No email has been set. Please set the email. File-> Set EMail.");
            //QMessageBox::critical(this, tr("Error: No email has been set. Please set the email. File-> Set EMail."));
        }else
        {
            QTextStream in(&file);
            QString line = in.readLine();
            if(line.length()<4)
            {
                displayErrorbox("Please set your email. \n Click on the SETUP tab.");
            }
        }
    }
}
void MainWindow::checkPin()
{
    QString fileName =PIN;

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: Checkpin. Opening DB for pin.");
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        if(line.length()<4)
        {
            displayErrorbox("Please set your PIN. \n Click on the SETUP tab.");
        }
    }
}

QString MainWindow::getNokiaUserID()
{
    QString fileName =NOKIA_USER_ID;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            //displayErrorbox("Error: Could not open file. Contact kmdarshan@gmail.com");
            return "";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "";
}
/*
QString MainWindow::getEmail()
{
    QString fileName =EMAIL;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: Could not open file. Contact kmdarshan@gmail.com");
            return "error";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "admin@kmdarshan.com";
}
QString MainWindow::getPin()
{
    QString fileName =PIN;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Error: Could not open file. Contact kmdarshan@gmail.com");
            return "error";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "1234";
}
//#include "emaildialog.h"
void MainWindow::setPin()
{

        QString sEmail=ui->lineEdit_4->text();
        if(sEmail.length()<3)
        {
            displayErrorbox("Please enter correct PIN.\n Length is less than 3.\n");
            return;
        }else{
            QString fileName = PIN;
            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly)) {
                    displayErrorbox("Error: Could not open file.\n Contact admin@kmdarshan.com");
                    return;
                }
                QTextStream stream(&file);
                stream<<sEmail;
                displayErrorbox("Finished saving PIN. thanks!");
                /*QMessageBox msgBox;
                msgBox.setText("Finished saving PIN. thanks!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
                file.close();
                setInfo();
            }
        }

}
void MainWindow::setEmail()
{

        QString sEmail=ui->lineEdit_3->text();
        if(sEmail.length()<4)
        {
            displayErrorbox("Please enter correct email.\n Length is less than 4.\n");
            return;
        }
        else{
            QString fileName = EMAIL;
            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly)) {
                    displayErrorbox("Error: Could not open file. Contact admin@kmdarshan.com");
                    return;
                }
                QTextStream stream(&file);
                stream<<sEmail;
                displayErrorbox("finished saving email. thanks!");
                /*QMessageBox msgBox;
                msgBox.setText("finished saving email. thanks!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
                file.close();
                setInfo();
            }
        }

}*/

MainWindow::~MainWindow()
{
    //delete m_manager;
    //Enter into file
    QString fileName = TASK_DB_NAME;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
            displayErrorbox("Error: Could not open DB for saving posts. \nContact kmdarshan@gmail.com");
            //QMessageBox::critical(this, tr("Error: Opening DB for saving posts."));
            return;
        } else {
            QList<QListWidgetItem*> items = ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
            QList<QListWidgetItem*>::iterator i;
            QTextStream stream(&file);
            for (i = items.begin(); i != items.end(); ++i)
            {
                //Sample URL
                //WEB_ADDRESSinsertpost.php?post=darshan+sucks&email=divyadarshankm%40yahoo.com


                QListWidgetItem *qlwItem;
                qlwItem=*i;
                //QIcon qIcn=qlwItem->icon();
                QString qsTxt=qlwItem->text();
                QString qsBeginChar=qsTxt;
                qsBeginChar.truncate(1);
                if(qsBeginChar==".")
                {
                    stream << "DELETE ";
                }
                stream << qsTxt;
                stream << "\n";
                stream.flush();
            }
            file.close();
        }
    }
    if(readFiles(NOTIFY_FILE)!="ONLINE")
    {

    }else{
        on_unregisterButton_clicked();
        QFile::remove(NOTIFY_FILE);
        if ( iHttpManager )
        {
            delete iHttpManager;
            iHttpManager = NULL;
        }

        if (iNotificationSession)
        {
            delete iNotificationSession;
            iNotificationSession = NULL;
        }
    }

    delete ui;
}

void MainWindow::clearDoneTasks()
{
    QList<QListWidgetItem*> items = ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    QList<QListWidgetItem*> newListItem;
    QList<QListWidgetItem*>::iterator itr;

    for (itr=items.begin(); itr!=items.end(); itr++)
    {
        QListWidgetItem *qlwItem = *itr;
        QString qsTxt=qlwItem->text();
        QString qsBeginChar=qsTxt;
        qsBeginChar.truncate(1);
        if(qsBeginChar!=".")
        {
            newListItem.push_back(qlwItem);
        }
    }

    QString fileName =TASK_DB_NAME;

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            displayErrorbox("Could not open db for clearing tasks.\n");
            return;
        }

        //QTextStream in(&file);
        QTextStream stream(&file);
        for (itr=newListItem.begin(); itr!=newListItem.end(); itr++)
        {
            QListWidgetItem *qlwItem;
            qlwItem=*itr;
            //QIcon qIcn=qlwItem->icon();
            QString qsTxt=qlwItem->text();
            stream << qsTxt;
            stream << "\n";
            stream.flush();
        }

        file.close();
    }

    ui->listWidget->clear();
    WriteToUI();
}

void MainWindow::WriteToUI()
{
    //Write to the UI again
    QString fileName =TASK_DB_NAME;

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            displayErrorbox("Could not open file");
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            if(line.startsWith("DELETE ", Qt::CaseInsensitive) == true)
            {
                line.remove(0,7);
                QListWidgetItem *item;
                item=new QListWidgetItem(QIcon(":/images/Done.png"),line,ui->listWidget);
                ui->listWidget->addItem(item);
            }else{
                QListWidgetItem *item;
                item=new QListWidgetItem(QIcon(":/images/red.png"),line,ui->listWidget);
                ui->listWidget->addItem(item);
            }
            line = in.readLine();
        }
        file.close();
    }
}

void MainWindow::clearAllTasks()
{
    ui->listWidget->clear();   
}

//Method to add posts
void MainWindow::on_pushButton_clicked()
{
    QString qStr=ui->lineEdit->text();
    if(qStr.size() == 0)
        return;

    QListWidgetItem *item;
    item=new QListWidgetItem(QIcon(":/images/red.png"),qStr,ui->listWidget);
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

//Method to set the posts as done
void MainWindow::on_pushButton_2_clicked()
{
    //ui->listWidget->takeItem(iCRow);
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() <1)
        return;
    int iCRow = ui->listWidget->currentRow();
    QListWidgetItem *qlwItem = ui->listWidget->takeItem(iCRow);
    QString qStr=qlwItem->text();
    QString sPost=qStr;
    if(qStr.startsWith('.')==true)
        qStr = qStr;
    else
        qStr = "."+qStr;
    //Delete the posts
    //WEB_ADDRESSdelete.php?post=divyadsasasda&email=kmdarshan%40gmail.com&date=
    //QNetworkAccessManager* m_manager = new QNetworkAccessManager(this);
    QString sEmail=getNokiaUserID();
    QString sFinalPath=WEB_ADDRESS;
    sFinalPath+="delete.php?post=";
    sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date=";
    sendHttpRequests(sFinalPath);
    ////qDebug()()<<sFinalPath;
    //m_manager->get(QNetworkRequest(QUrl(sFinalPath)));

    QListWidgetItem *item=new QListWidgetItem;
    QFont f("Helvetica");
    f.setStrikeOut(true);
    item->setFont(f);
    item->setIcon(QIcon(":/images/Done.png"));
    item->setText(qStr);
    /*QListWidgetItem *item;
        item=new QListWidgetItem(QIcon(":/images/Done.png"),qStr,ui->listWidget);*/
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void MainWindow::encodeQueryItems(QUrl& url) {
    QList<QPair<QString, QString> > queryList = url.queryItems();
    for (int i = 0; i  < queryList.count(); i++) {
        QPair<QString, QString> pair = queryList[i];
        QByteArray leftEncoded = QUrl::toPercentEncoding(pair.first);
        QByteArray rightEncoded = QUrl::toPercentEncoding(pair.second);
        url.removeQueryItem(pair.first);
        url.addEncodedQueryItem(leftEncoded, rightEncoded);
    }
}
void MainWindow::appendHeaders() {
    //  m_networkRequest->setRawHeader("Accept-Encoding", "application/x-www-form-urlencoded");
    //  m_networkRequest->setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    /*for (int i = 0; i < m_customHeaders.count(); i++) {
    const QPair<QByteArray, QByteArray> headerPair = m_customHeaders[i];
    request->setRawHeader(headerPair.first, headerPair.second);
  }*/
}
void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        //qDebug()()<<"In download progress > 0";
    }
    else {
        //qDebug()()<<"In download progress = 0";
    }
}
void MainWindow::processResponse()
{


    const QNetworkReply* networkReply = m_networkReply;
    if (networkReply != NULL) {
        qDebug()<<"Inside process response";
        //m_httpCommunicator->setBackupvariable("true");
        /*const QList<QByteArray> headerListByetArray = networkReply->rawHeaderList();
        QString headerListString;
        for (int i = 0; i < headerListByetArray.length(); i++) {
            headerListString.append(headerListByetArray[i]);
            headerListString.append(":");
            headerListString.append(networkReply->rawHeader(headerListByetArray[i]));
            headerListString.append("\n");
        }*/
        //qDebug()()<<"inside process response";
        /*if (networkReply->error() == QNetworkReply::NoError) {
            QString boby = m_networkReplyBody;
            if (boby.length() == 0) {
                boby = tr("Request Succeeded.");
                //qDebug()()<<boby;
            }

        }
        // Some http error received
        else {
            // handle errors here
            //ui->m_textBrowserResp->append(networkReply->errorString());
            //qDebug()()<<"networkReply->errorString() ->"<<networkReply->errorString();
        }*/
    }

}
void MainWindow::downloadReadyRead()
{
    QByteArray bytes = m_networkReply->readAll();  // bytes
    m_networkReplyBody = m_networkReplyBody + bytes; // string
    //qDebug()()<<"In download ready read";
}


void MainWindow::sendHttpRequests(QString url)
{
    //qDebug()()<<"inside send";

    // Pick the headers
    QList<QPair<QByteArray, QByteArray> > headers;
    if (!HttpCommunicator::splitIntoHeaders("",
                                            headers)) {
        //qDebug()()<<"Error in sploit";
        return;
    }

    // Pick request body if needed
    QByteArray postData("");
    //QFile* file = NULL;


    bool saveToFile = false;

    if (m_httpCommunicator) {
        delete m_httpCommunicator;
        m_httpCommunicator = NULL;
    }

    //qDebug()()<<"inside send 2";
    QString strGet="GET";
    // Proceed with request if header parsing is through
    HttpCommunicator::HttpRequestType requestType =
            HttpCommunicator::httpRequestTypeForText(strGet);

    //qDebug()()<<"post data"<<postData;
    //qDebug()()<<"headers "<<headers;
    //qDebug()()<<"request type"<<requestType;
    m_httpCommunicator = new HttpCommunicator(requestType,
                                              url,
                                              postData, headers, saveToFile);

    connect(m_httpCommunicator, SIGNAL(finishedRequest()), this,
            SLOT(processResponse()));
    m_httpCommunicator->makeRequest();

}
void MainWindow::slotReadyRead()
{

    //QByteArray bytes = m_networkReply->readAll();
    ////qDebug()()<<"ready read"<<bytes;
    //displayErrorbox("finished ready read");
}
void MainWindow::slotError(QNetworkReply *reply)
{
    //qDebug()()<<"slotError";
    //displayErrorbox("network error");
}

/*
void MainWindow::on_lineEdit_textEdited(QString)
{
    QList<QListWidgetItem*> items = ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    QList<QListWidgetItem*>::iterator itr;
    if(items.size()<1)
        printf("Error: Size is 0 \n");
    else
    {
        QStringList taskList;
        for (itr=items.begin(); itr!=items.end(); itr++)
        {
            QListWidgetItem *qlwItem=new QListWidgetItem;
            qlwItem=*itr;
            QString qsTxt=(QString)qlwItem->text();
            ////qDebug()()<<qsTxt;
            taskList.append(qsTxt);
        }
        QCompleter *completer = new QCompleter(taskList, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit->setCompleter(completer);
    }
}*/

//search items
//sync window open
void MainWindow::on_pushButton_3_clicked()
{
    /*this->hide();
    //this->close();
    MainWindow *sf=new MainWindow;
    qDebug()<<"in sync";
    sf->showMaximized();*/
    QList<QListWidgetItem*> items;
    QString qSearchstring=ui->lineEdit->text();
    items = ui->listWidget->findItems(qSearchstring+"*", Qt::MatchWrap | Qt::MatchWildcard);
    FindDialog fd;
    fd.displayPosts(items);
    fd.exec();
}

//Adding reminders from the push button
void MainWindow::on_pushButton_4_clicked()
{
    QString sError ="";
    if(getNokiaUserID().size()<4)
    {
       sError = "Please enter nokia user id, then only we can send the notifications.";
    }
    if(readFiles(NOTIFY_FILE)!="ONLINE")
    {
        sError += "Please goto the NOTIFY tab, \n and click on the setup reminder notifications. \n It takes only 10 seconds to do it.";
    }

    if(sError.size()>20)
    {
        displayErrorbox(sError);
        //ui->tabNotify->show();
        return;
    }
    //first check if the line edit is empty
    //if not, then proceed to the tab
    QString qStr=ui->lineEdit->text();
    if(qStr.size() == 0)
    {
        //check if this is a finished task
        //if its a finished task, we cannot set reminders on them
        //send a message
         QListWidgetItem *qlwItem = ui->listWidget->currentItem();
        if(qlwItem==NULL)
            return;
        QString sPost=qlwItem->text();
        if(sPost.startsWith("."))
        {
            QMessageBox msgBox;
            msgBox.setText("You cannot set reminder's on finished tasks!!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return;
        }
    }
    Dialog dlg;
    dlg.adjustSize();
    if(dlg.exec() == QDialog::Accepted)
    {
        QString fileName = NOKIA_USER_ID;
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadWrite)) {
                displayErrorbox("Reminder:Could not open file");
                return;
            }
            QTextStream in(&file);
            QString line = in.readLine();
            if (line.length()<4) {
                displayErrorbox("Please enter the email address in the text box.and then try");
                return;
            }

        }

        QString strDateTime = dlg.getDate()+" "+dlg.getTime();

        //qDebug()()<<"setReminder";
        QDateTime qdTemptime = QDateTime::fromString(strDateTime, "MM/dd/yyyy h:m:s AP");
        //qDebug()()<<qdTemptime;
        long iEpochtime=qdTemptime.toTime_t();
        //qDebug()()<<iEpochtime;
        QString sEpochtime;
        std::stringstream ss;
        ss << iEpochtime;
        sEpochtime= QString::fromStdString(ss.str());

        QString sDate=qdTemptime.toString("yyyy.MM.dd h:m:s");
        sDate.replace(" ","+");
        sDate.replace(".","/");
        //qDebug()()<<"Date ="<<sDate;
        QListWidgetItem *qlwItem = ui->listWidget->currentItem();
        if(qlwItem==NULL)
            return;

        QString sPost=qlwItem->text();
        QString sEmail=getNokiaUserID();
        QString sFinalPath=WEB_ADDRESS;
        sFinalPath+="insert.php?post=";
        sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date="+sDate+"&epochtime="+sEpochtime;
        sendHttpRequests(sFinalPath);
        qDebug()<<"Inside SetReminder"<<sFinalPath;
        //QNetworkReply *qreply=m_manager->get(QNetworkRequest(QUrl(sFinalPath)));

    }
}

void MainWindow::finishedSlot(QNetworkReply* reply)
{
    //qDebug()()<<"Inside finished slot";
    Q_ASSERT(m_networkReply == reply);
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    //QNetworkReply::NetworkError error = reply->error();
    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        //qDebug()()<<"Inside signal reply";
        // Example 2: Reading bytes form the reply
        // QByteArray bytes = reply.readAll();  // bytes
        // QString string(bytes); // string
    }else if (reply->error() == QNetworkReply::HostNotFoundError)
    {
        //qDebug()()<<"host Errors here";
    }
    // Some http error received
    else
    {
        // handle errors here
        //qDebug()()<<reply->error()<<"Errors here";
    }
    emit finishedRequest();
    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    //delete reply;
}

void MainWindow::on_actionBackup_All_Posts_2_triggered()
{
    //displayErrorbox("Coming soon!!!!");
    //qDebug()<<"Inside bac pu posts 2 trigger";
    checkEmail();
    checkPin();

    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() <1)
        return;
    int iCRow = ui->listWidget->currentRow();
    QListWidgetItem *qlwItem = ui->listWidget->takeItem(iCRow);
    QString qStr=qlwItem->text();
    if(qStr.length()<1)
    {
        displayErrorbox("No post to backup");
    }else
    {
        if(qStr.startsWith('.')==true)
        {
            qStr = qStr;
            displayErrorbox("cannot backup finished tasks");
        }
        else
        {
            QString sEmail=getNokiaUserID();
            QString sFinalPath=WEB_ADDRESS;
            sFinalPath+="insertpost.php?post=";
            QString sPost;
            QString sPin="";
            //Add it to the database
            sPost=qStr;
            QString sDate=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
            sDate.replace(" ","+");
            sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date="+sDate+"&pin="+sPin;
            sendHttpRequests(sFinalPath);
            QListWidgetItem *item=new QListWidgetItem;
            QFont f("Helvetica");
            //f.setStrikeOut(true);
            item->setFont(f);
            item->setIcon(QIcon(":/images/red.png"));
            item->setText(qStr);
            /*QListWidgetItem *item;
                item=new QListWidgetItem(QIcon(":/images/red.png"),qStr,ui->listWidget);*/
            ui->listWidget->addItem(item);
            ui->listWidget->setCurrentItem(item);
        }
    }
}

//Adding iterms to the sync list widget
void MainWindow::on_pushButton_5_clicked()
{
    QString qStr=ui->lineEdit_2->text();
    if(qStr.size() == 0)
    {
        displayAllSyncPosts();
        return;
    }

    QString email=getSyncEmail();
    QString pwd=getSyncPin();
    if(email.endsWith("error") || email.size()==0
       || pwd.endsWith("error") || pwd.size()==0)
    {
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to sync post, set HANDLE and PIN.\nClick on the SETUP tab."));


    }else
    {
        m_syncEmail=email;
        m_syncPassword=pwd;
        m_syncPost=qStr;

        downloadFile();
    }
}

void MainWindow::displayAllSyncPosts()
{
    QString email=getSyncEmail();
    QString pwd=getSyncPin();
    if(email.endsWith("error") || email.size()==0
       || pwd.endsWith("error") || pwd.size()==0)
    {
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to sync post, set email and password."));

    }else
    {
        m_syncEmail=email;
        m_syncPassword=pwd;



    url = SYNC_URL_DISPLAY;
    //url = "http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=from post rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan";
    //http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan
    QString tmpUrl=SYNC_URL_DISPLAY;
    tmpUrl.append("email="+m_syncEmail+"&pin="+m_syncPassword);
    //QFileInfo fileInfo(url.path());
    url = tmpUrl;
    //qDebug()<<url;
    QFileInfo fileInfo(SYNC_POSTS_FILE);
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    /*if (QFile::exists(fileName)) {
        if (QMessageBox::question(this, tr("HTTP"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        QFile::remove(fileName);
    }*/

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

//#ifndef Q_WS_MAEMO_5
    //ui->progressDialog->
   // ui->progressDialog->setWindowTitle(tr("HTTP"));
   // ui->progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
//#endif
    ui->pushButton_5->setEnabled(false);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}
}

void MainWindow::downloadFile()
{

    url = SYNC_URL;
    //url = "http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=from post rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan";
    //http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan
    QString tmpUrl=SYNC_URL;
    tmpUrl.append("post="+m_syncPost+"&email="+m_syncEmail+"&pin="+m_syncPassword);
    //QFileInfo fileInfo(url.path());
    url = tmpUrl;
    //qDebug()<<url;
    QFileInfo fileInfo(SYNC_POSTS_FILE);
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    /*if (QFile::exists(fileName)) {
        if (QMessageBox::question(this, tr("HTTP"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(fileName),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        QFile::remove(fileName);
    }*/

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

//#ifndef Q_WS_MAEMO_5
    //ui->progressDialog->
   // ui->progressDialog->setWindowTitle(tr("HTTP"));
   // ui->progressDialog->setLabelText(tr("Downloading %1.").arg(fileName));
//#endif
    ui->pushButton_5->setEnabled(false);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void MainWindow::cancelDownload()
{
    /*statusLabel->setText(tr("Download canceled."));
    httpRequestAborted = true;
    reply->abort();*/
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::httpFinished()
{
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
/*#ifndef Q_WS_MAEMO_5
        progressDialog->hide();
#endif*/
        return;
    }
/*
#ifndef Q_WS_MAEMO_5
    progressDialog->hide();
#endif*/
    file->flush();
    file->close();


    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        ui->pushButton_5->setEnabled(true);
    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(this, tr("HTTP"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            url = newUrl;
            reply->deleteLater();
            file->open(QIODevice::WriteOnly);
            file->resize(0);
            startRequest(url);
            return;
        }
    } else {
        //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        ui->pushButton_5->setEnabled(true);

        //After downloading all the files
        //Add data to the list widget
        //Lets start reading from the file to display from the text file
        QString fileName =SYNC_POSTS_FILE;
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                //qDebug()<<"Cannot read file";
                return;
            }

            QTextStream in(&file);
            QString lines = in.readLine();
            //qDebug()<<"Lines "<<lines;
            QStringList list = lines.split(" $$$ ");
            list.removeDuplicates();
            //qDebug()<<"list "<<list;
            QListWidgetItem *item;
            ui->synclistwidget->clear();
            for (int i = 0; i < list.size(); ++i)
            {
                QString tmpString = list.at(i);
                if(tmpString.size()>2)
                {
                   qDebug()<<"temp str "<<tmpString;
                   item=new QListWidgetItem(QIcon(":/images/red.png"),tmpString,ui->synclistwidget);
                   ui->synclistwidget->addItem(item);
                   ui->synclistwidget->setCurrentItem(item);
                }
            }

        }
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void MainWindow::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    if (httpRequestAborted)
        return;
/*
#ifndef Q_WS_MAEMO_5
    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(bytesRead);
#else
    Q_UNUSED(bytesRead);
    Q_UNUSED(totalBytes);
#endif*/
}

void MainWindow::enableDownloadButton()
{
    ui->pushButton_5->setEnabled(true);
    //downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}

void MainWindow::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
{
    /*QDialog dlg;
    Ui::Dialog ui;
    ui.setupUi(&dlg);
    dlg.adjustSize();
    ui.siteDescription->setText(tr("%1 at %2").arg(authenticator->realm()).arg(url.host()));

    // Did the URL have information? Fill the UI
    // This is only relevant if the URL-supplied credentials were wrong
    ui.userEdit->setText(url.userName());
    ui.passwordEdit->setText(url.password());

    if (dlg.exec() == QDialog::Accepted) {
        authenticator->setUser(ui.userEdit->text());
        authenticator->setPassword(ui.passwordEdit->text());
    }*/
}
void MainWindow::startRequest(QUrl url)
{
    /*if (!qconfnet.isOnline()) {
        QMessageBox::warning(this, tr("Offline"),
            tr("The device is currently offline, the network request should trigger a connection attempt automatically"));
    }*/
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error(QNetworkReply::NetworkError)));
}

void MainWindow::error(QNetworkReply::NetworkError ne)
{
    reply->disconnect();
    reply->deleteLater();
    QMessageBox::warning(this, tr("HTTP"),
                         tr("An error has occured: %1 (%2 attempts remaining)").arg(reply->errorString()).arg(retryCount));
    if (--retryCount > 0)
        startRequest(url);
}

QString MainWindow::getSyncEmail()
{
    QString fileName =SYNC_EMAIL_FILE;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            return "error";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "";
}
QString MainWindow::getSyncPin()
{
    QString fileName =SYNC_PASSWORD_FILE;
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            return "error";
        }
        QTextStream in(&file);
        QString line = in.readLine();
        return line;
    }
    return "";
}

void MainWindow::setInfo()
{
    QString qEmail=getNokiaUserID();
    //QString qPwd=getPin();
    QString qSEmail=getSyncEmail();
    QString qSPin=getSyncPin();
    QString finalStr = "<b>Nokia User ID: </b> "+qEmail+
            "<br><br> <b>Sync Handle: </b>"+
            qSEmail+"<br><br> <b>Sync Pin: </b>"+qSPin;
    ui->textBrowser->setText(finalStr);
}

//For saving the password and email
void MainWindow::on_pushButton_7_clicked()
{

    QString fileName = SYNC_EMAIL_FILE;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QString qemail=ui->syncemail->text();
    bool bSet=true;
    if(qemail.size()> 4)
        stream<<qemail;
    else
    {
        QMessageBox::information(this, tr("Error"),
                                 tr("Handle should be greater than 4 characters"));
        bSet=false;
    }
    file.close();

    fileName = SYNC_PASSWORD_FILE;
    QFile file2(fileName);
    file2.open(QIODevice::WriteOnly);
    QTextStream stream2(&file2);
    QString qpwd=ui->syncpassword->text();
    if(qpwd.size()> 4)
        stream2<<qpwd;
    else
    {
        QMessageBox::information(this, tr("Error"),
                                 tr("PIN should not be greater than 4 characters"));
        bSet=false;
    }

    file2.close();
    if(bSet==true)
        setInfo();
}

//Delete the sync posts
void MainWindow::on_pushButton_6_clicked()
{
    //ui->listWidget->takeItem(iCRow);
    QList<QListWidgetItem*> items = ui->synclistwidget->selectedItems();
    if(items.size() <1)
        return;
    int iCRow = ui->synclistwidget->currentRow();
    QListWidgetItem *qlwItem = ui->synclistwidget->takeItem(iCRow);
    QString qStr=qlwItem->text();
    QString sPost=qStr;
    if(qStr.startsWith('.')==true)
        qStr = qStr;
    else
        qStr = "."+qStr;
    //Delete the posts
    //WEB_ADDRESSdelete.php?post=divyadsasasda&email=kmdarshan%40gmail.com&date=
    //QNetworkAccessManager* m_manager = new QNetworkAccessManager(this);
    QString sEmail=getSyncEmail();
    QString sFinalPath=WEB_ADDRESS;
    sFinalPath+="deleteSyncPosts.php?post=";
    sFinalPath=sFinalPath+sPost+"&email="+sEmail+"&date=";
    sendHttpRequests(sFinalPath);
    ////qDebug()()<<sFinalPath;
    //m_manager->get(QNetworkRequest(QUrl(sFinalPath)));
}

//For setting personal email
void MainWindow::on_pushButton_8_clicked()
{
    //setEmail();
    //setPin();
}
#include <QList>
void MainWindow::createFiles()
{
    QList<QString> qlist;
    qlist.push_back(EMAIL);
    qlist.push_back(SYNC_EMAIL_FILE);;
    qlist.push_back(SYNC_PASSWORD_FILE);;
    qlist.push_back(PIN);;
    qlist.push_back(SYNC_POSTS_FILE);;
    qlist.push_back(TASK_DB_NAME);
    qlist.push_back(NOTIFY_FILE);

    for (int i = 0; i < qlist.size(); ++i) {
        QFile file(qlist.at(i));
        file.open(QIODevice::Append);
        QTextStream stream(&file);
        stream<<"";
        file.close();
     }

}


void MainWindow::setUpNotifications()
{


    iHttpManager = new QNetworkAccessManager(this);
    connect(iHttpManager, SIGNAL(sslErrors(QNetworkReply *, QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply *, QList<QSslError>)));

#ifndef Q_OS_SYMBIAN
    if (http_proxy != "")
    {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, http_proxy, proxy_port);
        iHttpManager->setProxy(proxy);
    }

    else
    {
        QNetworkProxyFactory::setUseSystemConfiguration (true);
    }
#endif

    // Connect to Notifications
    bool success = initialize();

    iIconData =
            "";

    // Update the status to the screen.
    if (!success)
    {
        displayErrorbox("OviServiceInterace was not loaded.");
    }
    else
    {
        ui->textBrowser_3->append("Ready");
        //displayErrorbox("Ready.");
    }
}

void MainWindow::on_registerButton_clicked()
{
    // Register to Notifications
    //displayErrorbox("Registering to Notifications ...");
    ui->textBrowser_3->append("Registering to Notifications ...");
    iNotificationSession->registerApplication(application_id);
}

void MainWindow::on_unregisterButton_clicked()
{
    // Unregister from Notifications
    //displayErrorbox("Unregistering from Notifications...");
    iNotificationSession->unregisterApplication();
}

void MainWindow::on_notificationIdButton_clicked()
{
    // Request notification address for this application
    displayErrorbox("Requesting notification info...");
    iNotificationSession->getNotificationInformation(service_id);
}

void MainWindow::on_sendNotificationIdButton_clicked()
{
    if (application_id == "com.example"
        && service_id == "example.com")
    {
       displayErrorbox("To send Notification Id to developer console, "
                                 "you must request your own application and service id from: "
                                 "https://projects.forum.nokia.com/notificationsapi/wiki/registerservice");
    }
    else
    {

        if (iNotificationId.isEmpty())
        {
            displayErrorbox("Get Notification Id first by pressing \"Get NID\" button. ");
        }
        else
        {
            displayErrorbox("Sending NID to service..");
            QByteArray dataArray = QUrl::toPercentEncoding( iNotificationId );
            QString post_url = "https://account.nnapi.ovi.com/cm/ext/addnid";
            QString post_data = "nid=" + dataArray + "&sid=" + service_id;
            QUrl qUrl(post_url);
            iHttpManager->post(QNetworkRequest(qUrl), post_data.toLatin1());
            displayErrorbox("Notification Id: '" + iNotificationId + "' sent to service.");
        }

    }
}

void MainWindow::on_settingsButton_clicked()
{
    displayErrorbox("Notification UI: " + QString::number(iNotificationSession->isNotificationUi())
                            + " Wakeup: " + QString::number(iNotificationSession->isWakeUp()));
}

void MainWindow::on_notificationUiCheckBox_stateChanged(int state )
{
    if(state == Qt::Checked)
    {
        iNotificationSession->setNotificationUi(true, iIconData);
    }
    else
    {
        iNotificationSession->setNotificationUi(false, iIconData);
    }
}

void MainWindow::on_wakeupCheckBox_stateChanged(int state )
{
    if(state == Qt::Checked)
    {
        iNotificationSession->setWakeUp(true);
    }
    else
    {
        iNotificationSession->setWakeUp(false);
    }
}

void MainWindow::on_notificationIconSelectionBox_highlighted(QString item)
{
    if(item == "GIF")
    {
       iIconData = "R0lGODlhQABAAPcAAPb3+fH09/b4+vz9/vr7/Pn6+/j5+urv8+/z9sbV39Le5tji6d7n7d3m7OXs8eju8vT3+fP2+LPI1cHS3cvZ4s/c5Nbh6Ja0xZ25ya/CzbvO2cPU3sLT3cjX4Mza4tXh6Nnk6tfi6OXs8Ovw84Swx9He5dzm6+Pr7+vx9O7z9ff6+/v8/P////7+/gAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACwAAAAAQABAAAAI/wBJCBxIsKDBgwgTKkzYoqHDhxAjSpxIsSLFFRgzatzIsaPHjyA/qhhJsqTJkyhTqlypEoLLlzBjypxJs6bNmgFy6tzJs6fPn0CDAk1BtKjRo0iTKl3KtKnTp1CjKkVBtarVq1izat3KdeuBr2DDih1LtqzZs2YfqF3Ltq3bt3Djyo17oq7du3jz6t3Lty9fBoADCx5MuLDhw4gPg1jMuLHjx5AjS54sOYTly5gza97MubPnz6BDix7N+YPp06hTq17NurXr17Bjy55Nu7bt27hz697Nu7fv38CDx2ZBvLjx48iTK1/OvLnz59CjS59Ovbr169iza9/Ovbv37+DDizAfT768+fPo06tfz769+/fw48ufT7++/fv48+vfz7+///8ABijggAQWaOCBCCZoYEAAOw==";
    }
    else if (item == "JPEG")
    {
       iIconData = "/9j/4AAQSkZJRgABAQEAYABgAAD/4QBGRXhpZgAASUkqAAgAAAABAGmHBAABAAAAGgAAAAAAAAABAIaSAgASAAAALAAAAAAAAABDcmVhdGVkIHdpdGggR0lNUAD/2wBDAAgGBgcGBQgHBwcJCQgKDBQNDAsLDBkSEw8UHRofHh0aHBwgJC4nICIsIxwcKDcpLDAxNDQ0Hyc5PTgyPC4zNDL/2wBDAQkJCQwLDBgNDRgyIRwhMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjL/wAARCAA6ADsDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREAAgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRChYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD1voalhtZZ/ujj1NSWVt9ofc33F5PvWuoVBtUAAdhTGUY9LXH7xyT7VJ/Zdv3D/nVzIo3CkBnvpEJB2sw+tUbjTpoVLAbl9RWrf3X2OxnuTG0nlIX2J1bA6Csfwt4im8QWVxNc6dJZPFJsCsdwkHqDgUubWwr9CoTTcGtfUbBWRriIYI5KjuKx92PU1Qzo7EiOzix/Eu4/jzXL+MfEV7Y3VppWnuIri5wWlwDsBIHH61t6XObi12KR5kXyMufTofyrnPFWkSPrtjqzCTyoVVCEGcbWJGfzNcuLm4Um1oZ1U2rIq6ne634Tv7JpdTlv7W4yJFkXkHvg/wAqu+FNV1RtbvrTUbh5ogpMLSEdj/gc/hTtdl/tqayt7IeYwOScfdz61V14voOsRXKRSS+ZAVAjwATgjkmvMlXmqjlT1irHO7xfNfQelzqd/HrV2uqXEcUW7yVQKAuM8DI/WtPwTNeXVlcNeXUs5EgwZMZAx7AUun2Etv4InVYhFdSwOxVm3YYg4yaTwHZ31pptwL6WOR2lypjHAGK3pOarQu91cqPNzxOqKgjHbpXIzny7iRAD8rkfrXV3EyW8LzSEKiKSSa48SPMWlLBTIxfBHTJzXqnSPMk9pci7teZBw6f3x/jXTWV1FqNos6qdrcFXGCD6EVzZrf0XnTx/10b+dDSasMupbxRklIkQnuqgUkkEUwAljRwpyNy5wayNW15bSQ2toonuz1H8KD3NZo1/WwMfZLYk999SopKyQrdDrCq7cYGCMEe1QTT21hAzyukMY5yeK5aTVNdn4823twe6qSaq/YvNk827mkuXznMjfKPwp8qvcZcvdSk1mUKgaOxU8Z4Mv/1qTavdST7UnA4/KiqAU0w316LY2Vt+5RmZnl7gE9BTv4aU9T9aAIYII7aMpGMZOSTySfU1NSA9KWiwBRRRQAlFKKD1oA//2Q==";
    }
    else if (item == "PNG")
    {
       iIconData = "iVBORw0KGgoAAAANSUhEUgAAADIAAAAMCAIAAACvLXk7AAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgAABdwnLpRPAAAABl0RVh0U29mdHdhcmUAQWRvYmUgSW1hZ2VSZWFkeXHJZTwAAAQuSURBVEhLxZX9T1tlFMfv/NWY+IPJ/gBNiNFkvywZTIyJCkQgRJnAhIBYy6AZ8tLymsJYZYNRoEMoLSxIoE4pCkJAdCm1FBjvLy0MCqXgGsKrLTCg9/3l8dyysE1/ZfHk3pPnPPd5nvO553vaew7xAnYOwzAEN4a9IjoYwow4+f8ZEgT/xSMBiRfv9y+aj0M7x4TrgJ3fOjCu8jjz7wVnHmMi01OiZ4dvEujhDqqd8iot7iiD/cNfNqMsxMd/srmPUP48uvwb/2j75aJhwOR6gjZxwboj2PaQ47Hd/tj9+wbq30afDKA37nuCzcz1WRQ7QAZobR+U/Zp8q6HuXuvi3pkX6IUDAQt1jw6ljKLBXVTmQI0O4rMhX0APif1E32nVBuuGpZqWeLlSnpbUUnNLXZQhT4sPkyn3eXSw583Ly9vf34cTNjY2PB7P8PAwTdNtbW3PZ+B5XhAFeWpjY2MwgslTPz09XVFRsb6+/vwuEWtzdfHtltVX232YzvlauSm4oj264NsbRbk3i/Oyr0tKbhRKJEnh1xRBOdp3VH+EGreW/2Zhl0KuAB8TEzM4OBgREbG0tGQ0GrOysiIjIysrK9PT06VSaU9PT05Ojs/ni4uL0+v1iYmJ5eXlDQ0NhYWFKpVKo9H09/d3dnYqlcqmpqbR0dGqqqqQkBA4VsTadjtV+nufJsQmxYYGXgz4WprwRWy4JC01NKP0o+yCYl1J6g9V35jtF66Vfq55YLL2Lqxuw6671XfNZnN3d3dQUNDc3NzU1FRjYyOO43V1dTKZrKOjY3Z2Vi6XR0dH5+fnR0VFabVaiUTS3NysVquhNsnJyfX19QMDAwaDAVZmZmZWV1eXlpYqFIqVlRURq2d49jvNzcSUhJj46LfCwiLULYG6qas/Nlw2PCz4ucYyaModoVO+N78f/O7tqsqVhUVEsAIj6uJwOMCTJHlSf1DwNNz0G4Rerxckoyhqfn4eRD9dcHR0lJ2dDdLDDGCBP9FxeXnZXy0ezW0xGTWtcV/Gxl8Nv1RUez5C+vqVvCtWXt9vK9FUy4tTa3U6l30SUTTiBETxiIY/FATvBG0B2plMpoWFhZMxQRCQw2azQQhtBAaFBD6Xy+V2u6E2drsd0judTpDv+PgYtgwNDUEIj2ZmZk7bC+MIljvwKCyHgV9lvCkrw2SthVlJF967WHzn9oNu4/72BqIoRHM8yXEEjUhOoHmeFhv26PCwr68PGgvez2q1gh8ZGZmcnIR8UMWurq6JiQnIB492d3chBHTIDQ20trYGA4vFAnzABOjj4+MwDy3xDAt/gh96Pe6/lovv95aoy9tba3t7OxFFIIrhSZbBKZYgBZIWKEagaYHheEbgoVr+n9LLM4zBaRanOJxENIlYDrE8KMWLHJSfgxIYUmCgmcR+AiDwAuvH+s/H4Awp/wFDMVeqa7TkRQAAAABJRU5ErkJggg==";
    }
    else if(item == "SVG")
    {
       iIconData = "PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+DQo8IURPQ1RZUEUgc3ZnIFBVQkxJQyAiLS8vVzNDLy9EVEQgU1ZHIDEuMSBUaW55Ly9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLXRpbnkuZHRkIj4NCjxzdmcgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiB4bWxuczp4bGluaz0iaHR0cDovL3d3dy53My5vcmcvMTk5OS94bGluayIgYmFzZVByb2ZpbGU9InRpbnkiIGhlaWdodD0iMTI4IiB2ZXJzaW9uPSIxLjAiIHdpZHRoPSIxMjgiPg0KPGRlZnM+DQo8bGluZWFyR3JhZGllbnQgaWQ9ImxpbmVhckdyYWRpZW50MjI1NSI+DQo8c3RvcCBvZmZzZXQ9IjAiIHN0eWxlPSJzdG9wLWNvbG9yOiMwMDNmYTI7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8c3RvcCBvZmZzZXQ9IjEiIHN0eWxlPSJzdG9wLWNvbG9yOiMyYjdlZmY7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8L2xpbmVhckdyYWRpZW50Pg0KPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXJHcmFkaWVudDIzODEiPg0KPHN0b3Agb2Zmc2V0PSIwIiBzdHlsZT0ic3RvcC1jb2xvcjojMDAwMDAwO3N0b3Atb3BhY2l0eToxOyIvPg0KPHN0b3Agb2Zmc2V0PSIxIiBzdHlsZT0ic3RvcC1jb2xvcjojMDAwMDAwO3N0b3Atb3BhY2l0eTowOyIvPg0KPC9saW5lYXJHcmFkaWVudD4NCjxsaW5lYXJHcmFkaWVudCBpZD0ibGluZWFyR3JhZGllbnQyMzA4Ij4NCjxzdG9wIG9mZnNldD0iMCIgc3R5bGU9InN0b3AtY29sb3I6IzBlMDAwMDtzdG9wLW9wYWNpdHk6MTsiLz4NCjxzdG9wIG9mZnNldD0iMSIgc3R5bGU9InN0b3AtY29sb3I6IzBlMDAwMDtzdG9wLW9wYWNpdHk6MDsiLz4NCjwvbGluZWFyR3JhZGllbnQ+DQo8bGluZWFyR3JhZGllbnQgaWQ9ImxpbmVhckdyYWRpZW50MjI5OCI+DQo8c3RvcCBvZmZzZXQ9IjAiIHN0eWxlPSJzdG9wLWNvbG9yOiMwZTAwMDA7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8c3RvcCBvZmZzZXQ9IjAuNjMxODY4MTIiIHN0eWxlPSJzdG9wLWNvbG9yOiM0YjAwMDA7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8c3RvcCBvZmZzZXQ9IjEiIHN0eWxlPSJzdG9wLWNvbG9yOiM5NTAwMDA7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8L2xpbmVhckdyYWRpZW50Pg0KPGxpbmVhckdyYWRpZW50IGlkPSJsaW5lYXJHcmFkaWVudDI0NTAiPg0KPHN0b3Agb2Zmc2V0PSIwIiBzdHlsZT0ic3RvcC1jb2xvcjojZmZmZmZmO3N0b3Atb3BhY2l0eToxOyIvPg0KPHN0b3Agb2Zmc2V0PSIxIiBzdHlsZT0ic3RvcC1jb2xvcjojZmZmZmZmO3N0b3Atb3BhY2l0eTowOyIvPg0KPC9saW5lYXJHcmFkaWVudD4NCjxsaW5lYXJHcmFkaWVudCBpZD0ibGluZWFyR3JhZGllbnQyNDM0Ij4NCjxzdG9wIG9mZnNldD0iMCIgc3R5bGU9InN0b3AtY29sb3I6I2ZmZmZmZjtzdG9wLW9wYWNpdHk6MTsiLz4NCjxzdG9wIG9mZnNldD0iMSIgc3R5bGU9InN0b3AtY29sb3I6I2ZmZmZmZjtzdG9wLW9wYWNpdHk6MDsiLz4NCjwvbGluZWFyR3JhZGllbnQ+DQo8bGluZWFyR3JhZGllbnQgaWQ9ImxpbmVhckdyYWRpZW50MjMxOSI+DQo8c3RvcCBvZmZzZXQ9IjAiIHN0eWxlPSJzdG9wLWNvbG9yOiNmZmZiZmI7c3RvcC1vcGFjaXR5OjE7Ii8+DQo8c3RvcCBvZmZzZXQ9IjEiIHN0eWxlPSJzdG9wLWNvbG9yOiNmZmZiZmI7c3RvcC1vcGFjaXR5OjA7Ii8+DQo8L2xpbmVhckdyYWRpZW50Pg0KPHJhZGlhbEdyYWRpZW50IGN4PSI2My45MTIyMDkiIGN5PSIxMTUuNzA5MTkiIGZ4PSIxNC4wNDY2MzkiIGZ5PSIxMTUuNzA5MTkiIGdyYWRpZW50VHJhbnNmb3JtPSJtYXRyaXgoMSwwLDAsMC4xOTc4MDIsMCw5Mi44MjE2NikiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiBpZD0icmFkaWFsR3JhZGllbnQzMjk3IiByPSI2My45MTIyMDkiIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDMyOTEiLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgaWQ9ImxpbmVhckdyYWRpZW50MjMwNCIgeDE9IjExLjg5ODc1MyIgeDI9IjExNS44NzgwMSIgeGxpbms6aHJlZj0iI2xpbmVhckdyYWRpZW50MjI5OCIgeTE9IjEyNC44MTk1MSIgeTI9IjE5LjM0MDkyNSIvPg0KPGxpbmVhckdyYWRpZW50IGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiBpZD0ibGluZWFyR3JhZGllbnQyMzE0IiBzcHJlYWRNZXRob2Q9InJlZmxlY3QiIHgxPSI5OS4yMTk5MzMiIHgyPSI4OS4wNDM0MzQiIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDIzMDgiIHkxPSI0NC4xODY1ODQiIHkyPSIzNC4wMTAwODYiLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgaWQ9ImxpbmVhckdyYWRpZW50MjMzOCIgeDE9Ijc4LjMyMTkzOCIgeDI9IjQyLjIyMDQ0NCIgeGxpbms6aHJlZj0iI2xpbmVhckdyYWRpZW50MjMzMiIgeTE9IjQzLjEwMTQwNiIgeTI9IjUzLjUyOTc3OCIvPg0KPHJhZGlhbEdyYWRpZW50IGN4PSI0OS4zNzA2ODYiIGN5PSI4Mi42NDY3ODIiIGZ4PSI0OS4zNzA2ODYiIGZ5PSI4Mi42NDY3ODIiIGdyYWRpZW50VHJhbnNmb3JtPSJtYXRyaXgoMS4wMjEzMzgsLTAuNTAyMDgsMC4zMTIyMDMsMC42MzUwODUsLTI4LjQxMzI0LDQzLjk0MjM4KSIgZ3JhZGllbnRVbml0cz0idXNlclNwYWNlT25Vc2UiIGlkPSJyYWRpYWxHcmFkaWVudDIzNDYiIHI9IjI0LjAxNTc1OCIgeGxpbms6aHJlZj0iI2xpbmVhckdyYWRpZW50MjQxOCIvPg0KPGxpbmVhckdyYWRpZW50IGdyYWRpZW50VHJhbnNmb3JtPSJtYXRyaXgoMS4wMzA1OCwwLDAsMS4wMzA1OCwtMy4wNjcwOTksLTEuMjAzMDA5KSIgZ3JhZGllbnRVbml0cz0idXNlclNwYWNlT25Vc2UiIGlkPSJsaW5lYXJHcmFkaWVudDIzNDkiIHgxPSI1MS4wODE0MjUiIHgyPSI1My4yMDI0NDYiIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDI0NTAiIHkxPSI2Ny45MTE2MjEiIHkyPSI5My4zNjgxMDMiLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFRyYW5zZm9ybT0ibWF0cml4KDEuMDMwNTgsMCwwLDEuMDMwNTgsLTMuMDY3MDk5LC0xLjIwMzAwOSkiIGdyYWRpZW50VW5pdHM9InVz"
"ZXJTcGFjZU9uVXNlIiBpZD0ibGluZWFyR3JhZGllbnQyMzUzIiB4MT0iNjEuNTkzNzUiIHgyPSI4My4xMDQ3NzQiIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDI0NDIiIHkxPSI0NS40Njk4NDUiIHkyPSI2NS44NTA2NDciLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFRyYW5zZm9ybT0ibWF0cml4KDEuMDMwNTgsMCwwLDEuMDMwNTgsLTMuMDY3MDk5LC0xLjIwMzAwOSkiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiBpZD0ibGluZWFyR3JhZGllbnQyMzU3IiB4MT0iODguODg0MTQ4IiB4Mj0iMTA3LjU2OTI1IiB4bGluazpocmVmPSIjbGluZWFyR3JhZGllbnQyNDM0IiB5MT0iMjEuMDgyOTA1IiB5Mj0iNDIuMzM5MjQxIi8+DQo8bGluZWFyR3JhZGllbnQgZ3JhZGllbnRUcmFuc2Zvcm09Im1hdHJpeCgxLjAzMDU4LDAsMCwxLjAzMDU4LC0zLjA2NzA5OSwtMS4yMDMwMDkpIiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgaWQ9ImxpbmVhckdyYWRpZW50MjM2MSIgeDE9IjgwLjY0MjE5NyIgeDI9IjY3LjE2MDA4IiB4bGluazpocmVmPSIjbGluZWFyR3JhZGllbnQyMzE5IiB5MT0iMTI2LjAyMTIiIHkyPSI3My4zNjg1MTUiLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFRyYW5zZm9ybT0ibWF0cml4KDEuMDMwNTgsMCwwLDEuMDMwNTgsLTMuMDY3MDk5LC0xLjIwMzAwOSkiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiBpZD0ibGluZWFyR3JhZGllbnQyMzY0IiB4MT0iOTEuMzM1NDE5IiB4Mj0iNjAuNjY3NzciIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDIzMTkiIHkxPSIxMTIuNDYzNzIiIHkyPSI2Ny42NDAwMDciLz4NCjxsaW5lYXJHcmFkaWVudCBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgaWQ9ImxpbmVhckdyYWRpZW50MjM4NyIgeDE9Ijc2LjUxMjM1MiIgeDI9IjY0Ljc5MDQwNSIgeGxpbms6aHJlZj0iI2xpbmVhckdyYWRpZW50MjM4MSIgeTE9IjU4Ljk0NzA3MSIgeTI9IjEwMC4wMDk0MSIvPg0KPGxpbmVhckdyYWRpZW50IGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iLTEwMi4xODQzOSIgeDI9Ii0yNy4yMDI2NzUiIHhsaW5rOmhyZWY9IiNsaW5lYXJHcmFkaWVudDIyOTgiIHkxPSItNDEuODQyMyIgeTI9Ii00MS44NDIzIi8+DQo8bGluZWFyR3JhZGllbnQgZ3JhZGllbnRVbml0cz0idXNlclNwYWNlT25Vc2UiIGlkPSJsaW5lYXJHcmFkaWVudDIyNjEiIHgxPSItMzIuMzIzNTU5IiB4Mj0iLTM3LjY2NjM4OSIgeGxpbms6aHJlZj0iI2xpbmVhckdyYWRpZW50MjI1NSIgeTE9IjE5MS44NDExMSIgeTI9IjE2MC43MTIxIi8+DQo8L2RlZnM+DQo8Zz4NCjxwYXRoIGQ9Ik0gNDIuNzY5NTEsNzEuNTY3MTc3IEMgMzcuMjIzMjI1LDc0LjM0NzQ4OSAzMi4zMzMxNjQsNzguMTU3MTU4IDI3LjkxMzE0Miw4Mi41NDg2OTQgQyAyNy4xMzgzNTUsODMuMjU5ODAxIDI4Ljc5NjA0NCw4NC4xNTc1NTkgMjkuMjEwODI2LDg0LjAzMjk4NCBDIDMyLjEyMDM5OCw4Mi45NDc2ODEgMzQuMjQzMzE4LDgzLjU2Njc4NiAzNy4xNTI4OTEsODIuNDgxNDgyIiBzdHlsZT0iZmlsbDojMjgwMDAwO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDowLjc5MDA2MDY0cHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA1MC44OTI3OTksMy4yODEyOTU5IEwgNTAuODkyNzk5LDAuNDg2NTg3NDcgTCA1MC44OTI3OTksMy4yODEyOTU5IHogIiBzdHlsZT0iZmlsbDojZmZmZmZmO2ZpbGwtb3BhY2l0eTowLjc1Njg4MDc2O2ZpbGwtcnVsZTpub256ZXJvO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDowLjU7c3Ryb2tlLWxpbmVjYXA6cm91bmQ7c3Ryb2tlLWxpbmVqb2luOnJvdW5kO3N0cm9rZS1taXRlcmxpbWl0OjQ7c3Ryb2tlLWRhc2hhcnJheTpub25lO3N0cm9rZS1kYXNob2Zmc2V0OjQ7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSAxMjcuODI0NDIgMTE1LjcwOTE5IEEgNjMuOTEyMjA5IDEyLjY0MTk3NSAwIDEgMSAgMCwxMTUuNzA5MTkgQSA2My45MTIyMDkgMTIuNjQxOTc1IDAgMSAxICAxMjcuODI0NDIgMTE1LjcwOTE5IHoiIHN0eWxlPSJvcGFjaXR5OjAuMzgxMzk1MzU7ZmlsbDp1cmwoI3JhZGlhbEdyYWRpZW50MzI5Nyk7ZmlsbC1vcGFjaXR5OjEuMDtmaWxsLXJ1bGU6bm9uemVybztzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MDtzdHJva2UtbGluZWNhcDpyb3VuZDtzdHJva2UtbGluZWpvaW46cm91bmQ7c3Ryb2tlLW1pdGVybGltaXQ6NDtzdHJva2UtZGFzaGFycmF5Om5vbmU7c3Ryb2tlLWRhc2hvZmZzZXQ6NDtzdHJva2Utb3BhY2l0eToxIiB0cmFuc2Zvcm09Im1hdHJpeCgxLDAsMCwwLjQxNjY2NywwLDc0Ljg3MTUxKSIvPg0KPGcgdHJhbnNmb3JtPSJtYXRyaXgoMC40ODM0MDIsMC41Mzc3NywtMC43MTM3OTgsMC42NDE2MzQsMTY2Ljg3NTQsOC4zOTMwMjcpIj4NCjxwYXRoIGQ9Ik0gLTQwLDE1NS40Mjk2OCBDIC0zNi44MzMzMzMsMTUyLjAwOTQ3IC0zMi40MjYxMzEsMTUyLjM3NTkyIC0yOSwxNTUuNDI5NjggQyAtMjUuNTczODY5LDE1OC40ODM0NCAtMTkuMTMxODE1LDE2Ny43OTM3MyAtMTkuNjMxODE1LDE3Ni4yMjIxMiBDIC0yMC4xMzE4MTUsMTg0LjY1MDUxIC0yMS43OTQyNTEsMTkwLjY3OTEgLTMwLjIxMTIzMiwxOTguOTkzMTYgQyAtNDAuMDE5OTUsMTkyLjMwMjg3IC00NS42MTY3ODIsMTg2LjM4OTE2IC00Ni45NTAxMTUsMTc3Ljk2MDc3IEMgLTQ4LjI4MzQ0OCwxNjkuNTMyMzggLTQzLjE2NjY2NywxNTguODQ5OSAtNDAsMTU1LjQyOTY4IHogIiBzdHlsZT0iZmlsbDojYjVhOGE4O2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MTtvcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gLTM4LjAxMTMzMSwxNTQuODYzMjYgQyAtMzUuODU1NzYzLDE1Mi41MzUxIC0zMi44NTU3NTcsMTUyLjc4NDU1IC0zMC41MjM1NzEsMTU0Ljg2"
"MzI2IEMgLTI4LjE5MTM4NSwxNTYuOTQxOTcgLTIzLjY3Nzg2MiwxNjEuNTk4MjkgLTI0LjAxODIxNCwxNjcuMzM1NTQgQyAtMjQuMzU4NTY3LDE3My4wNzI3OSAtMjYuNjk2ODczLDE4MS4zODk0OSAtMzIuNDQyMDM4LDE4Ny4xMzQ2NiBDIC0zNy45NjU1NjksMTgzLjE1NzU1IC00My40MDY0NTksMTc1LjI4NzgxIC00NC4zMTQwNjYsMTY5LjU1MDU2IEMgLTQ1LjIyMTY3MywxNjMuODEzMzEgLTQwLjE2Njg5OCwxNTcuMTkxNDIgLTM4LjAxMTMzMSwxNTQuODYzMjYgeiAiIHN0eWxlPSJmaWxsOnVybCgjbGluZWFyR3JhZGllbnQyMjYxKTtmaWxsLW9wYWNpdHk6MS4wO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MTtvcGFjaXR5OjAuNDA1NzM3NyIvPg0KPHBhdGggZD0iTSAtMzcuMzkyNDg5LDE1NC43NDkzMyBDIC0zNi4xMTc0ODQsMTUzLjM3MjI0IC0zNC4zNDI5OTksMTUzLjUxOTc5IC0zMi45NjM1MjYsMTU0Ljc0OTMzIEMgLTMxLjU4NDA1MiwxNTUuOTc4ODggLTI4LjkxNDMzMiwxNTguNzMzMDYgLTI5LjExNTY0OCwxNjIuMTI2NjEgQyAtMjkuMzE2OTY0LDE2NS41MjAxNiAtMzIuMDc3OTQyLDE3MC45NTEyNyAtMzUuNDc2MTcxLDE3NC4zNDk1MSBDIC0zOC41OTU0OTEsMTcxLjIzMDE5IC00MC4wNzY3MDksMTY2LjQwNTQzIC00MC42MTM1NTMsMTYzLjAxMTg4IEMgLTQxLjE1MDM5NywxNTkuNjE4MzMgLTM4LjY2NzQ5MywxNTYuMTI2NDIgLTM3LjM5MjQ4OSwxNTQuNzQ5MzMgeiAiIHN0eWxlPSJmaWxsOiNkZmRlZmY7ZmlsbC1vcGFjaXR5OjE7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIi8+DQo8L2c+DQo8ZyB0cmFuc2Zvcm09Im1hdHJpeCgwLjc4ODUxMywwLjc4ODUxMywtMC43ODg1MTMsMC43ODg1MTMsODEuMTI2MzQsMi4wODk2ODIpIj4NCjxwYXRoIGQ9Ik0gMTI2LjUzMTI1LDAuODEyNSBDIDEyMS4xMiwwLjk0MzU2MzY1IDExNS4wOTIyNSwzLjMwMzA4MDkgMTEwLjQzNzUsNi40MDYyNSBDIDk4LjM4ODIwMiwxNC40MzkxMTUgODUuMDYzOTE2LDI3LjE3MDg3MiA3My4wOTM3NSwzOS4xNTYyNSBDIDQ2Ljg4NTU5NSw0My4yOTc2NzQgMjIuNzY2MjU3LDU2LjcyODI2NiA1LjEyNSw3Mi42ODc1IEMgNS4xMTk2NTQzLDcyLjY5MjgxIDUuMDk4ODg4Miw3Mi43MTMxODkgNS4wOTM3NSw3Mi43MTg3NSBDIDUuMDg4ODEyNSw3Mi43MjQ1MzQgNS4wNjcyNDM1LDcyLjc0NDAyMiA1LjA2MjUsNzIuNzUgQyA1LjAxMjM4MTQsNzIuODE3NTc3IDQuOTY5ODU1Niw3Mi45MDIwMzcgNC45Mzc1LDcyLjk2ODc1IEMgNC45MzQ4MDUzLDcyLjk3NDkwMyA0LjkwODgwNzksNzIuOTkzNzMgNC45MDYyNSw3MyBDIDQuODMzNjE4NCw3My4xOTE0MzIgNC44MjUyMjQ5LDczLjQzNTcyNCA0Ljg3NSw3My42NTYyNSBDIDUuMTI0MTg2Niw3NC42NTE3MzEgNi40NzE3MTE4LDc1Ljg0NDQxNiA3LjUzMTI1LDc1Ljg3NSBDIDcuNTg1ODA3Nyw3NS44NzU1NiA3LjY2NTg4NjIsNzUuODQ5NTM1IDcuNzE4NzUsNzUuODQzNzUgQyA3Ljc1Mzc4MDEsNzUuODM5MTY1IDcuODA5NjM4OCw3NS44NTEzMTcgNy44NDM3NSw3NS44NDM3NSBDIDcuODY2OTk3OCw3NS44Mzc4MjUgNy44ODM0ODA5LDc1LjgxOTg5MyA3LjkwNjI1LDc1LjgxMjUgQyAxOC45MzQ2ODMsNzIuMjMxNTA5IDMyLjQzNTIzMyw2OC42MTIxOTUgNDMuMjgxMjUsNzAuMzQzNzUgQyA0MS41Njg4NjcsNzIuNzI3MjM5IDM5Ljg0Njc0Miw3NS40Njk2MTQgMzcuOTM3NSw3OC45MDYyNSBDIDM1LjEwMzgxMyw4NC4wMDY4ODMgMzIuMTI0MTM5LDg4LjY4NjYzOSAzNS43MTg3NSw5Mi4yODEyNSBDIDM5LjEzODk4Nyw5NS43MDE0ODkgNDMuOTkzMTE3LDkyLjg5NjE4NiA0OS4wOTM3NSw5MC4wNjI1IEMgNTIuNTMwMzg3LDg4LjE1MzI1NyA1NS4yNzI3NjEsODYuNDMxMTMzIDU3LjY1NjI1LDg0LjcxODc1IEMgNTkuMzg3ODA0LDk1LjU2NDc2NiA1NS43Njg0ODcsMTA5LjA2NTMyIDUyLjE4NzUsMTIwLjA5Mzc1IEMgNTIuMTgxOTU1LDEyMC4xMTA4MyA1Mi4xNjIyODEsMTIwLjEzNzUzIDUyLjE1NjI1LDEyMC4xNTYyNSBDIDUyLjE0MzIzLDEyMC4yMTQ5NCA1Mi4xNjA1OTUsMTIwLjMxMzgyIDUyLjE1NjI1LDEyMC4zNzUgQyA1Mi4xNTQ2NDUsMTIwLjQxMTk3IDUyLjE1NDkyOSwxMjAuNDkzNTggNTIuMTU2MjUsMTIwLjUzMTI1IEMgNTIuMjIxMzIsMTIxLjYxNzA1IDUzLjQ2Njk5OCwxMjIuOTgxMDIgNTQuNDY4NzUsMTIzLjE1NjI1IEMgNTQuNTU2MzYzLDEyMy4xNjkyNyA1NC42NTkxNzcsMTIzLjE2MTI0IDU0Ljc1LDEyMy4xNTYyNSBDIDU0Ljc3NDM1NSwxMjMuMTU0MzUgNTQuODIxMTM2LDEyMy4xNTk4NSA1NC44NDM3NSwxMjMuMTU2MjUgQyA1NS4wMTE1NTYsMTIzLjExNzc4IDU1LjE4MzczNywxMjMuMDE3MzMgNTUuMzEyNSwxMjIuODc1IEMgNzEuMjcxNzMzLDEwNS4yMzM3NCA4NC43MDIzMjYsODEuMTE0NDA1IDg4Ljg0Mzc1LDU0LjkwNjI1IEMgMTAwLjgyOTEzLDQyLjkzNjA4MyAxMTMuNTYwODgsMjkuNjExNzk4IDEyMS41OTM3NSwxNy41NjI1IEMgMTI0LjgyMzA2LDEyLjcxODUzIDEyNy4yNDAzMiw2LjM4OTc4ODIgMTI3LjE4NzUsMC44MTI1IEMgMTI2Ljk2OTY0LDAuODEwNDM2ODQgMTI2Ljc1MTIyLDAuODA3MTcyMjEgMTI2LjUzMTI1LDAuODEyNSB6ICIgc3R5bGU9ImZpbGw6dXJsKCNsaW5lYXJHcmFkaWVudDIzMDQpO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIgdHJhbnNmb3JtPSJtYXRyaXgoMC42MzQxMDUsLTAuNjM0MTA1LDAuNjM0MTA1LDAuNjM0MTA1LC01Mi45OTMxNyw1MS42OTU5OCkiLz4NCjxwYXRoIGQ9Ik0gMTI2LjUzMTI1LDAuODEyNSBDIDEyMS4xMiwwLjk0MzU2MzY1IDExNS4wOTIyNSwzLjMw"
"MzA4MDkgMTEwLjQzNzUsNi40MDYyNSBDIDk4LjM4ODIwMiwxNC40MzkxMTUgODUuMDYzOTE2LDI3LjE3MDg3MiA3My4wOTM3NSwzOS4xNTYyNSBDIDM5LjUwNjkwNCw0My45MTI1NjUgMzIuNDM1MjMzLDY4LjYxMjE5NSA0My4yODEyNSw3MC4zNDM3NSBDIDQxLjU2ODg2Nyw3Mi43MjcyMzkgMzkuODQ2NzQyLDc1LjQ2OTYxNCAzNy45Mzc1LDc4LjkwNjI1IEMgMzUuMTAzODEzLDg0LjAwNjg4MyAzMi4xMjQxMzksODguNjg2NjM5IDM1LjcxODc1LDkyLjI4MTI1IEMgMzkuMTM4OTg3LDk1LjcwMTQ4OSA0My45OTMxMTcsOTIuODk2MTg2IDQ5LjA5Mzc1LDkwLjA2MjUgQyA1Mi41MzAzODcsODguMTUzMjU3IDU1LjI3Mjc2MSw4Ni40MzExMzMgNTcuNjU2MjUsODQuNzE4NzUgQyA1OS42MTExNDIsMTA0LjA5Nzk4IDc1LjUzMjAzNiwxMTMuOTk3OTEgODguODQzNzUsNTQuOTA2MjUgQyAxMDAuODI5MTMsNDIuOTM2MDgzIDExMy41NjA4OCwyOS42MTE3OTggMTIxLjU5Mzc1LDE3LjU2MjUgQyAxMjQuODIzMDYsMTIuNzE4NTMgMTI3LjI0MDMyLDYuMzg5Nzg4MiAxMjcuMTg3NSwwLjgxMjUgQyAxMjYuOTY5NjQsMC44MTA0MzY4NCAxMjYuNzUxMjIsMC44MDcxNzIyMSAxMjYuNTMxMjUsMC44MTI1IHogIiBzdHlsZT0iZmlsbDp1cmwoI2xpbmVhckdyYWRpZW50MjMxNCk7ZmlsbC1vcGFjaXR5OjE7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIiB0cmFuc2Zvcm09Im1hdHJpeCgwLjYzNDEwNSwtMC42MzQxMDUsMC42MzQxMDUsMC42MzQxMDUsLTUyLjk5MzE3LDUxLjY5NTk4KSIvPg0KPC9nPg0KPHBhdGggZD0iTSAxMjUuNzU1NCwxLjg4ODczMSBDIDExMS40MzM2MSwzLjcxNDkxMSAxMDAuMzQ2OTQsMTYuNzY4OTI0IDc0LjIyNjQwMSw0MC4yODk1NjIgQyA3Ni4wMTQxNzMsNDQuNzI2MTQ4IDczLjI2NjMzOCw0NS44OTU0NTMgNjIuNjUyODE0LDU2LjQ1Mzg1NSBDIDUxLjk0NDA3MSw2Ny4xMDY5ODEgNDkuOTI1Nzk4LDY5LjQ1MDI0MiA0NC43OTkyNTUsNzEuMjg2MDMxIEMgNDEuMDIwNDYxLDc2Ljg5ODYwNCAzMi44NjQ3MTYsODUuMzY1NzExIDM0LjAzMzc4MSw5MS41NDkxOTEgQyAzOC4yOTY2MjksODEuMjE3ODgxIDQ2LjQ3NTM3NSw3Ni44NTQzNDkgNjcuNDUzMzAxLDU2LjkwMDAzIEMgNzguOTMzNTM2LDQ1Ljk3OTk2OCAxMTIuODc0NDEsNS41OTc2MzE5IDEyNS43NTU0LDEuODg4NzMxIHogIiBzdHlsZT0ib3BhY2l0eTowLjE4MDMyNzg5O2ZpbGw6I2YyZjJmMjtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gMTI1Ljc1NTQsMS44ODg3MzEgQyAxMTEuNDMzNjEsMy43MTQ5MTEgMTAwLjM0Njk0LDE2Ljc2ODkyNCA3NC4yMjY0MDEsNDAuMjg5NTYyIEMgNzYuMDE0MTczLDQ0LjcyNjE0OCA3My4yNjYzMzgsNDUuODk1NDUzIDYyLjY1MjgxNCw1Ni40NTM4NTUgQyA1MS45NDQwNzEsNjcuMTA2OTgxIDQ5LjkyNTc5OCw2OS40NTAyNDIgNDQuNzk5MjU1LDcxLjI4NjAzMSBDIDQxLjAyMDQ2MSw3Ni44OTg2MDQgMzIuODY0NzE2LDg1LjM2NTcxMSAzNC4wMzM3ODEsOTEuNTQ5MTkxIEMgMzYuOTY0NTEzLDgwLjgzNzI3NyA0My44MTExNDMsNzYuMDkzMTQgNjQuNzg5MDcsNTYuMTM4ODIxIEMgNzYuMjY5MzA0LDQ1LjIxODc1OSAxMDEuNjQ2NTgsOC4yNjE4NjM1IDEyNS43NTU0LDEuODg4NzMxIHogIiBzdHlsZT0ib3BhY2l0eTowLjE4MDMyNzg5O2ZpbGw6I2YyZjJmMjtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gMTI1Ljc1NTQsMS44ODg3MzEgQyAxMTEuNDMzNjEsMy43MTQ5MTEgOTkuMzk1NDI1LDE2LjM4ODMyIDczLjI3NDg5LDM5LjkwODk1NyBDIDc1LjA2MjY2Miw0NC4zNDU1NDQgNzIuNjk1NDMyLDQ1Ljg5NTQ1MyA2Mi4wODE5MDgsNTYuNDUzODU1IEMgNTEuMzczMTY1LDY3LjEwNjk4MSA0OS4zNTQ4OTEsNjguNDk4NzMyIDQ0LjIyODM0OCw3MC4zMzQ1MiBDIDQwLjQ0OTU1NSw3NS45NDcwOTMgMzIuODY0NzE2LDg1LjM2NTcxMSAzNC4wMzM3ODEsOTEuNTQ5MTkxIEMgMzguMjk2NjI5LDgxLjQwODE4MyA0NC41NzIzNTIsNzYuNjY0MDQ2IDY1LjU1MDI3OSw1Ni43MDk3MjcgQyA3Ny4wMzA1MTMsNDUuNzg5NjY1IDEwMi41OTgwOSw5LjU5Mzk3ODggMTI1Ljc1NTQsMS44ODg3MzEgeiAiIHN0eWxlPSJvcGFjaXR5OjAuMTgwMzI3ODk7ZmlsbDojZjJmMmYyO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSAxMjUuNzU1NCwxLjg4ODczMSBDIDExMS43MDMyMSw0LjQzMzgzMDcgOTkuODQ0NzQ5LDE2LjU2ODA1IDczLjcyNDIxNSw0MC4wODg2ODcgQyA3NS41MTE5ODcsNDQuNTI1Mjc0IDcyLjk2NTAyNyw0NS45ODUzMTggNjIuMzUxNTAzLDU2LjU0MzcxOSBDIDUxLjY0Mjc1OSw2Ny4xOTY4NDUgNDkuNDQ0NzU2LDY4Ljk0ODA1NiA0NC4zMTgyMTMsNzAuNzgzODQ1IEMgNDAuNTM5NDE5LDc2LjM5NjQxOCAzMy4zMTQwNCw4NS4yNzU4NDYgMzQuMDMzNzgxLDkxLjU0OTE5MSBDIDM5LjI4NTE0NCw4MC42ODkyNjQgNDUuMTExNTQyLDc3LjAyMzUwNiA2Ni4wODk0NjksNTcuMDY5MTg3IEMgNzcuNTY5NzA0LDQ2LjE0OTEyNSAxMDMuNDk2NzQsMTAuMjIzMDM0IDEyNS43NTU0LDEuODg4NzMxIHogIiBzdHlsZT0ib3BhY2l0eTowLjE4MDMyNzg5O2ZpbGw6I2YyZjJmMjtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5l"
"Y2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gNS4xNzc1NDEsNzQuMDI5MzMxIEMgMjQuMTk4MjgyLDU3Ljg4MDAxNyA0NS41MjY3MzMsNDUuNzQ0MTA5IDcxLjEzNDY2MSw0MS4wNTA3NzEgQyA3My4wNzE5MDgsNDAuNTk1MjU2IDcyLjk2NDI4Myw0Mi4zOTk4NjIgNzEuMzQ5OTExLDQyLjgwNTM0NSBDIDQ3LjM0MTM4NSw0NS40MjIwMjYgMjUuNDYwODUxLDU4LjUxNzY3MSA1LjE3NzU0MSw3NC4wMjkzMzEgeiAiIHN0eWxlPSJmaWxsOiNmZWZlZmU7ZmlsbC1vcGFjaXR5OjAuNTQ0NzE1NDk7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIi8+DQo8cGF0aCBkPSJNIDUuMTc3NTQxLDc0LjAyOTMzMSBDIDI0LjE5ODI4Miw1Ny44ODAwMTcgNDUuNTI2NzMzLDQ1Ljc0NDEwOSA3MS4xMzQ2NjEsNDEuMDUwNzcxIEMgNzMuMDcxOTA4LDQwLjU5NTI1NiA3My4zOTQ3ODIsNDIuNzIyNzM3IDcxLjc4MDQxLDQzLjEyODIxOSBDIDQ3Ljc3MTg4NCw0NS43NDQ5IDI1LjQ2MDg1MSw1OC41MTc2NzEgNS4xNzc1NDEsNzQuMDI5MzMxIHogIiBzdHlsZT0iZmlsbDojZmVmZWZlO2ZpbGwtb3BhY2l0eTowLjM5MDI0Mzg5O2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA1LjE3NzU0MSw3NC4wMjkzMzEgQyAyNC4xOTgyODIsNTcuODgwMDE3IDQ1LjUyNjczMyw0NS43NDQxMDkgNzEuMTM0NjYxLDQxLjA1MDc3MSBDIDczLjA3MTkwOCw0MC41OTUyNTYgNzMuNTAyNDA2LDQzLjE1MzIzNiA3MS44ODgwMzUsNDMuNTU4NzE4IEMgNDcuODc5NTA5LDQ2LjE3NTM5OSAyNS40NjA4NTEsNTguNTE3NjcxIDUuMTc3NTQxLDc0LjAyOTMzMSB6ICIgc3R5bGU9ImZpbGw6I2ZlZmVmZTtmaWxsLW9wYWNpdHk6MC4yMzU3NzIzNTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gODIuODEzMTMzLDYxLjIyMjE2IEMgODMuNzM5OTQ1LDU4LjgwMDM2OSA3Ni4zNDYwNzEsNjkuMzI5OTkxIDczLjk4Mjk4LDc0LjQyMjkxMSBDIDcwLjY4NTU2MSw4MS41Mjk0ODggNzAuMTU1ODQ0LDkzLjMzNDAzIDY3LjAxMjM0MSw5Ny4yMzAyODMgQyA2My44MTg3ODUsOTkuMzc1OTA1IDYyLjc4OTkxNiw5MS44Nzg4MzMgNjEuMDcyMjgyLDg3LjkyMzk3NiBDIDYwLjUzMzY3Niw4Ny4wNDk5OTEgNTkuNjAxNDkxLDg3LjA2MTU1OSA1OS4zNTgwNyw4OC44NDQyMzQgQyA1OS42ODM5MDcsMTAwLjM1OTA3IDU3LjQxOTMyLDEwNy41MDcyNCA1NC4xNTg1MzgsMTE3Ljk5NzMzIEMgNTMuNTEyODgxLDExOC44MzI4MyA1NS40MjU0ODksMTE5Ljg2NTEyIDU1LjY2NTM4NSwxMTguODMxMTIgQyA2OS40MDIxMjQsMTAxLjE2MjA2IDc5LjAwMDc3Nyw4NC44NDM3MjkgODIuODEzMTMzLDYxLjIyMjE2IHogIiBzdHlsZT0ib3BhY2l0eTowLjI5NTA4MjtmaWxsOnVybCgjbGluZWFyR3JhZGllbnQyMzYxKTtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gNS4xNzc1NDEsNzQuMDI5MzMxIEMgMjQuMTk4MjgyLDU3Ljg4MDAxNyA0NS41MjY3MzMsNDUuNzQ0MTA5IDcxLjEzNDY2MSw0MS4wNTA3NzEgQyA3My4wNzE5MDgsNDAuNTk1MjU2IDc0LjA0MDUzMSw0My43OTg5ODUgNzIuNDI2MTU5LDQ0LjIwNDQ2NyBDIDQ4LjQxNzYzMyw0Ni44MjExNDggMjUuNDYwODUxLDU4LjUxNzY3MSA1LjE3NzU0MSw3NC4wMjkzMzEgeiAiIHN0eWxlPSJmaWxsOiNmZWZlZmU7ZmlsbC1vcGFjaXR5OjAuMTM4MjExMzY7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIi8+DQo8cGF0aCBkPSJNIDg0LjU4NDIzOSw2MC4yMzgyMTEgQyA4NS41MTEwNTEsNTcuODE2NDIxIDc1LjU1ODkxMiw2OC45MzY0MTIgNzMuMTk1ODIxLDc0LjAyOTMzMSBDIDY5Ljg5ODQwMiw4MS4xMzU5MDkgNjMuNTc3MDc1LDg5LjMyMDU2OCA2MS44NTk0NDEsODUuMzY1NzExIEMgNjEuMzIwODM1LDg0LjQ5MTcyNiA1OS4wMTExMjIsODUuMDkzNjYzIDU4Ljc2NzcwMSw4Ni44NzYzMzcgQyA1OS4wOTM1MzgsOTguMzkxMTc1IDU1Ljg0NTAwMywxMDguODg0NzYgNTIuNTg0MjIxLDExOS4zNzQ4NSBDIDUxLjkzODU2NCwxMjAuMjEwMzUgNTQuODM1MTIsMTIxLjQzOTQzIDU1LjA3NTAxNiwxMjAuNDA1NDMgQyA2OC44MTE3NTUsMTAyLjczNjM3IDgwLjc3MTg4NCw4My44NTk3ODEgODQuNTg0MjM5LDYwLjIzODIxMSB6ICIgc3R5bGU9Im9wYWNpdHk6MC41Njk2NzIxMTtmaWxsOnVybCgjbGluZWFyR3JhZGllbnQyMzY0KTtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gMTA5LjQ3MTE3LDcuMTkwMjEzIEwgMTE0LjkzOTE4LDEyLjc1MTY5NyBMIDEwNC4wNDk4OCwyMy41MDA3ODMgTCA5Ny40MTM0ODcsMTYuMjU2ODMzIEMgMTAxLjIzNjQsMTMuMDM4MzEzIDEwNS4yNzQ1NywxMC4wMzUwNTEgMTA5LjQ3MTE3LDcuMTkwMjEzIHogIiBzdHlsZT0iZmlsbDojZmZmZmZmO2ZpbGwtb3BhY2l0eTowLjQ1OTM0OTYzO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9w"
"YWNpdHk6MSIvPg0KPHBhdGggZD0iTSAxMDQuMDA0MzYsMjMuNTA3NTg3IEwgMTEwLjg3ODA4LDMwLjkxMDA1OSBDIDEwNy4xOTE5MywzNS4zMzc1MDMgMTAzLjI2ODQ4LDM5LjYyOTMzOCA5OS4yNDU2MjcsNDMuODY0MzgzIEwgOTEuODQzMTU1LDM1LjY2ODc5IEwgMTA0LjAwNDM2LDIzLjUwNzU4NyB6ICIgc3R5bGU9ImZpbGw6dXJsKCNsaW5lYXJHcmFkaWVudDIzNTcpO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA4NC41NDIzNTEsMjcuNjc4OTkzIEwgOTEuNzkzMDY0LDM1LjY5MDgzMiBMIDc5LjEzNDM2LDQ4LjIyOTM1NyBMIDc0LjI0NzEzOCw0My4xMDE3ODIgQyA3NC41MTU5MjIsNDAuNjQ2MzcgNzMuMDU2MDY4LDM5Ljc1MDY0NSA3MS43MjM0MSw0MC4yOTc2MzggQyA3NS43Mjc3MzQsMzYuMTM4ODIyIDc5LjkyNjAyLDMxLjgzNjI0NCA4NC41NDIzNTEsMjcuNjc4OTkzIHogIiBzdHlsZT0iZmlsbDojZmZmZmZmO2ZpbGwtb3BhY2l0eTowLjQ1OTM0OTYzO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA4Ny4wNTU4NjUsNTYuMjgyMDQ1IEMgODcuMDY4NjUsNjguNjEyNzQ0IDcxLjA4MTQsMTAzLjIyNTQ5IDY4LjIwNzMwMSwxMDEuNzc2NTUgQyA2Ny40MDEwMzgsMTAwLjM1NjIzIDcwLjc2MjUwNSw5Ni44NzQ3NzggNzEuOTUwMTI4LDg3LjYzMTk4MiBDIDcxLjk1MDEyOCw4NC43MTI2MTkgNjkuNTEzOTQ3LDgwLjcwMTQwOCA2Ni4yNTM3NjgsODEuNzkyMTg5IEMgNjQuNjY1MjgxLDgyLjMyMzY2IDU5LjM5MzIyMSw5NC40MTM3NDkgNTcuODYwOTQ2LDkyLjg4MTQ3NCBDIDU4LjQ2MDM1OCw4OS4wMDI5MjIgNTkuMDU5NzcxLDg1LjEyNDM2OSA1OS42NTkxODMsODEuMjQ1ODE3IEMgNjAuMTkyNjU4LDc5LjkxMzE2MiA4NS4wOTY2MDksNTUuMDM2NzIxIDg3LjA1NTg2NSw1Ni4yODIwNDUgeiAiIHN0eWxlPSJmaWxsOnVybCgjbGluZWFyR3JhZGllbnQyMzg3KTtmaWxsLW9wYWNpdHk6MS4wO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA4Ni44NjU3ODMsNTYuMzIxMzE0IEMgODIuMTg2NTUxLDU5LjE1MTgwOSA3Ny40MDc3Nyw2NS4yMDk5NTkgNzIuNjg0ODMxLDY5LjY2MTAyNSBMIDY1LjU1NDI5NCw2MS44ODk1NDIgTCA3OS4xNzQ0MTksNDguMjI5MzU3IEwgODYuODY1NzgzLDU2LjMyMTMxNCB6ICIgc3R5bGU9ImZpbGw6dXJsKCNsaW5lYXJHcmFkaWVudDIzNTMpO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA2MS4yNjc5NjEsNTcuMjgyNzM1IEwgNjUuNDc0MTc2LDYxLjkyOTYwMSBMIDQ5LjQ1MDQ5OSw3Ny43MTI5MjIgTCA0My4yODEzODUsNzEuNTAzNzQ3IEwgNDQuMDAyNDQ5LDcwLjM4MjA5IEMgNDcuOTUzNzQ0LDY5LjQ5MzEwMyA1MS42NzYzODEsNjYuNzI1ODIzIDU0LjQ5Nzk1OCw2NC4wOTI3OTcgTCA2MS4yNjc5NjEsNTcuMjgyNzM1IHogIiBzdHlsZT0iZmlsbDojZmZmZmZmO2ZpbGwtb3BhY2l0eTowLjQ1OTM0OTYzO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA0OS40MTA0NDEsNzcuNzEyOTIyIEwgNTUuNjE5NjE1LDg0LjA0MjI3NCBMIDU2LjIyMDUwMyw4NS43MjQ3NiBDIDUzLjEwNjcxLDg4LjE2NTg0MSA0OS40MzQ4NjYsOTAuMDQ4ODcyIDQ1LjkyNTI5MSw5Mi4wOTQxNzEgTCA0MC4zMTcwMDUsODYuODA2MzU4IEwgNDkuNDEwNDQxLDc3LjcxMjkyMiB6ICIgc3R5bGU9ImZpbGw6dXJsKCNsaW5lYXJHcmFkaWVudDIzNDkpO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSA3MS42NDM0Miw0Ni43OTk5MDkgQyA3MS42NDM0Miw0Ni43OTk5MDkgNTQuNDM0NTM1LDY0LjA1OTEzMiA1Mi4xOTY3NDYsNjYuMDc0NDE5IEMgNTAuMzI3ODAyLDY3Ljc1NzUzMyA0NS43ODMyNDMsNzAuNTgyNjk0IDQzLjgxMjQ0Nyw3MC4yMjgxMzUgQyAzMi43NTk2OSw2OC4yMzk2NyAyMi4xNDMxLDcxLjY0MjA3NiAyMi4xNDMxLDcxLjY0MjA3NiBDIDMyLjgyMzUwOSw1Ny42NjI4OTkgNTEuOTM1NDAzLDUxLjkzOTU1MiA3MS42NDM0Miw0Ni43OTk5MDkgeiAiIHN0eWxlPSJvcGFjaXR5OjAuNDk1OTAxNjc7ZmlsbDp1cmwoI3JhZGlhbEdyYWRpZW50MjM0Nik7ZmlsbC1vcGFjaXR5OjE7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIi8+DQo8cGF0aCBkPSJNIDQwLjM0NjA0NCw4Ni43NjgwODggTCAzNS4zMTEwNTUsODIuMDc2MDQgQyAzMy4zNzQyNjEsODUuNzUyOTkgMzEuMTI5MjIzLDg5LjcxMTczNiAzMy45MzkyOTQsOTIuOTcyMTkzIEwgNDAuMzQ2MDQ0LDg2Ljc2ODA4OCB6ICIgc3R5bGU9ImZpbGw6I2ZmZmZmZjtmaWxsLW9wYWNpdHk6MC4zNDk1OTM1MjtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gMTI1Ljc1"
"NTQsMS44ODg3MzEgQyAxMTEuNzAzMjEsNC40MzM4MzA3IDEwMC43Nzk3OSwxNy4wMzU1NyA3NC42NTkyNTYsNDAuNTU2MjA4IEMgNzYuNDQ3MDI4LDQ0Ljk5Mjc5NCA3Mi45NjUwMjcsNDYuNjg2NTk5IDYyLjM1MTUwMyw1Ny4yNDUgQyA1MS42NDI3NTksNjcuODk4MTI2IDQ5LjQ0NDc1Niw2OC45NDgwNTYgNDQuMzE4MjEzLDcwLjc4Mzg0NSBDIDQwLjUzOTQxOSw3Ni4zOTY0MTggMzMuMzE0MDQsODUuMjc1ODQ2IDM0LjAzMzc4MSw5MS41NDkxOTEgQyAzNy44ODI1ODIsODAuNjg5MjY0IDQyLjQ5OTMsNzUuNDM1MzgyIDY0LjY4NjkwNyw1Ni44MzU0MjcgQyA3OC4yNzA5ODQsNDUuNDQ3ODQ1IDEwMy4wMjkyMiw4LjU4NjcxMjIgMTI1Ljc1NTQsMS44ODg3MzEgeiAiIHN0eWxlPSJvcGFjaXR5OjAuNjM1MjQ2MDc7ZmlsbDojZjJmMmYyO2ZpbGwtb3BhY2l0eToxO2ZpbGwtcnVsZTpldmVub2RkO3N0cm9rZTpub25lO3N0cm9rZS13aWR0aDoxcHg7c3Ryb2tlLWxpbmVjYXA6YnV0dDtzdHJva2UtbGluZWpvaW46bWl0ZXI7c3Ryb2tlLW9wYWNpdHk6MSIvPg0KPHBhdGggZD0iTSAxMjUuNzU1NCwxLjg4ODczMSBDIDExMS43MDMyMSw0LjQzMzgzMDcgMTAwLjE0NDYyLDE2LjQ3OTc5OSA3NC4wMjQwODksNDAuMDAwNDM3IEMgNzUuODExODYxLDQ0LjQzNzAyMyA3Mi44MDYyMzUsNDYuNTI3ODA3IDYyLjE5MjcxMSw1Ny4wODYyMDggQyA1MS40ODM5NjgsNjcuNzM5MzM0IDQ5LjQ0NDc1Niw2OC45NDgwNTYgNDQuMzE4MjEzLDcwLjc4Mzg0NSBDIDQwLjUzOTQxOSw3Ni4zOTY0MTggMzMuMzE0MDQsODUuMjc1ODQ2IDM0LjAzMzc4MSw5MS41NDkxOTEgQyA0MS44NTY1MDYsODIuNTU5MzQ1IDQ1LjA3MDY2Miw3Ny41MzkyMjQgNjcuMjU4MjY5LDU4LjkzOTI2OCBDIDgwLjg0MjM0Niw0Ny41NTE2ODYgMTA3LjAwMzE0LDEzLjAyODE1NiAxMjUuNzU1NCwxLjg4ODczMSB6ICIgc3R5bGU9Im9wYWNpdHk6MC40NzEzMTE1O2ZpbGw6I2YyZjJmMjtmaWxsLW9wYWNpdHk6MTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6bm9uZTtzdHJva2Utd2lkdGg6MXB4O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjEiLz4NCjxwYXRoIGQ9Ik0gNzEuNjU5ODc3LDQwLjE5NzQzMyBDIDcyLjgzMjcxNiwzOS45OTY0NDUgNzMuNjc1MTgzLDQwLjI3MjY2IDc0LjA1MTM4Nyw0MS4yMjIzNjYgQyA3NC41OTY4NTIsNDIuNTA3NjkyIDc0LjEwNjE5OSw0My42OTM3ODYgNzMuNzk1MTUzLDQ0LjI5NzE2NCBDIDY5LjUwMjE4Nyw1MS40OTE3MTcgNTkuOTg0NTUzLDU4LjM0MDExOSA1Mi45NTQ4NTYsNjUuMzA4Mjg0IEwgMzguMzQ5NTY1LDYzLjAwMjE4NSBMIDM5LjM3NDQ5Nyw1MC4wMTk3MDUgQyA1MC40MzgyMTEsNDUuNzM5MjE0IDYxLjI3NzU4NSw0Mi4yMDY1MTggNzEuNjU5ODc3LDQwLjE5NzQzMyB6ICIgc3R5bGU9ImZpbGw6dXJsKCNsaW5lYXJHcmFkaWVudDIzMzgpO2ZpbGwtb3BhY2l0eToxLjA7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOm5vbmU7c3Ryb2tlLXdpZHRoOjFweDtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxIi8+DQo8cGF0aCBkPSJNIDcxLjQxNTI1MSw0MC4xODc2NDYgQyA3MS40MTcwMTcsNDAuMTU3NDQ5IDc2LjEzMTkzNiwzNS42MDg5NjYgODIuNDYzNzU4LDI5Ljc2MzM2NiBDIDg4Ljc5NTU4MSwyMy45MTc3NjUgOTkuNDUyMTAyLDE0LjQ2NDY0NyAxMDMuMjEzNjksMTEuNTU2Mzc3IEMgMTEzLjEwNzk4LDMuOTA2NjE3MSAxMjAuNDM0NDMsMS44NDgwODcxIDEyNS43NjE3MiwxLjk0MzYxNTIgQyAxMjUuNTAyODYsNC41NTA5NDUyIDEyNi41MDQ2NiwxMC44OTg1NTcgMTE1LjY2ODA0LDI0LjkyMDg1IEMgMTAzLjg4MzY2LDQwLjE4Mjc3OSA3OS4zMDYwNzksNjMuMjYyOTI5IDc5LjMwNjA3OSw2My4yNjI5MjkiIHN0eWxlPSJmaWxsOm5vbmU7ZmlsbC1vcGFjaXR5OjAuNzU7ZmlsbC1ydWxlOmV2ZW5vZGQ7c3Ryb2tlOiMwMDAwMDA7c3Ryb2tlLXdpZHRoOjAuMTtzdHJva2UtbGluZWNhcDpidXR0O3N0cm9rZS1saW5lam9pbjptaXRlcjtzdHJva2Utb3BhY2l0eToxO3N0cm9rZS1taXRlcmxpbWl0OjQ7c3Ryb2tlLWRhc2hhcnJheTpub25lIi8+DQo8cGF0aCBkPSJNIDcxLjcwNTExNCw0MC40Nzc1MDggQyA3MS42NzI3ODksNDAuNDM1OTQ4IDc2LjM0MTE3LDM1LjYzMjE0IDgyLjY1Njk2NSwyOS43OTM3NDYgQyA4OC45NzI3NTksMjMuOTU1MzUyIDk2LjgxNTE3OCwxNi44NzA5OSAxMDMuNDQ0OTcsMTEuODIxNDk4IEMgMTEzLjkyNDgsMy44Mzk2NzU0IDExOS4zNjUxOCwyLjM0MzU5NyAxMjUuNTEzOTcsMi4xMzkyMTEyIEMgMTI1LjI1NTExLDQuNzQ2NTQxMiAxMjYuMjY5OTQsMTAuNzgxMTk5IDExNS40MzMzMiwyNC44MDM0OTIgQyAxMDMuNjQ4OTQsNDAuMDY1NDIxIDgwLjIxMTg5OSw2My44MDY0MjEgODAuMjExODk5LDYzLjgwNjQyMSIgc3R5bGU9ImZpbGw6bm9uZTtmaWxsLW9wYWNpdHk6MC43NTtmaWxsLXJ1bGU6ZXZlbm9kZDtzdHJva2U6IzAwMDAwMDtzdHJva2Utd2lkdGg6MC40O3N0cm9rZS1saW5lY2FwOmJ1dHQ7c3Ryb2tlLWxpbmVqb2luOm1pdGVyO3N0cm9rZS1vcGFjaXR5OjAuMjAzMjUyMDM7c3Ryb2tlLW1pdGVybGltaXQ6NDtzdHJva2UtZGFzaGFycmF5Om5vbmUiLz4NCjwvZz4NCjwvc3ZnPg0K";
    }
    iNotificationSession->setNotificationUi(iNotificationSession->isNotificationUi(), iIconData);
}

bool MainWindow::initialize()
{
    iNotificationSession = NULL;
    bool success = false;

    QPluginLoader *loader = new QPluginLoader(ONE_PLUGIN_ABSOLUTE_PATH);
    QObject *serviceObject = loader->instance();
    delete loader;

    if (serviceObject)
    {
        success = true;

        // Store the service interface for later usage
        iNotificationSession = static_cast<OviNotificationSession *>(
            serviceObject);

        // Connext signals to slots.
        connect(serviceObject,SIGNAL(stateChanged(QObject*)),
                this,SLOT(stateChanged(QObject*)));
        connect(serviceObject,SIGNAL(received(QObject*)),
                this,SLOT(received(QObject*)));
        connect(serviceObject,SIGNAL(notificationInformation(QObject*)),
                this,SLOT(notificationInfo(QObject*)));
        connect(serviceObject,SIGNAL(version(QString)),
                this,SLOT(versionResponse(QString)));
    }
    else
    {
        // There was problem loading the Notifications Enabler. Check loader->errorString()
        // for more details.
        success = false;
    }

    return success;
}

void MainWindow::stateChanged(QObject* aState)
{
    // State of the application has changed
    OviNotificationState* state = static_cast<OviNotificationState*>(aState);

    // Print out the session state on the screen
    switch (state->sessionState())
    {
        case OviNotificationState::EStateOffline:
        {
            //displayErrorbox("Application is offline.");
            ui->textBrowser_3->append("Application is offline.");
            ui->pushButton_9->setEnabled(true);
            break;
        }
        case OviNotificationState::EStateOnline:
        {
            //displayErrorbox("Application is online.");
            ui->textBrowser_3->append("Application is online");
            writeFiles(NOTIFY_FILE,"ONLINE",false,"");
            ui->pushButton_9->setEnabled(true);
            break;
        }
        case OviNotificationState::EStateConnecting:
        {
            ui->textBrowser_3->append("Application is connecting.");
            //displayErrorbox("Application is connecting.");
            break;
        }
        default:
        {
            break;
        }
    }

    // Print out the error, if there is any
    if (state->sessionError() != OviNotificationState::EErrorNone)
    {
        displayErrorbox("Error " + state->sessionErrorString() + " occured!");
    }
    delete state;
}

void MainWindow::received(QObject* aNotification)
{
    // Casting the QObject to OviNotificationMessage to gain access
    // to all its members.
    OviNotificationMessage* notification =
            static_cast<OviNotificationMessage*>(aNotification);

    // Show the received notification in the screen
    OviNotificationPayload*  payload =  static_cast<OviNotificationPayload*>(notification->payload());
    //displayErrorbox("Notification received!");
    //displayErrorbox("Application " + notification->senderInformation()
                           // + " of the service "+notification->from()+ " service sent: \n"
                           // + "'" + payload->dataString() + "'");
    displayErrorbox("Notification-> "+payload->dataString());
    // Printing out the notification details in text console. Optional.
    ui->textBrowser_3->append("Notification received");
    //displayErrorbox("Notification received.");
    //displayErrorbox("Notification was sent at " + notification->timestamp());
    if (!payload->type().isEmpty())
    {
        //displayErrorbox("Payload type was set to " + payload->type());
    }
    if (!payload->encoding().isEmpty())
    {
        //displayErrorbox("Payload was encoded in " + payload->encoding());
    }

    delete payload;
    delete notification;

}

void MainWindow::versionResponse(QString aVersion)
{
    displayErrorbox("Version :" + aVersion);
}

void MainWindow::notificationInfo(QObject* aData)
{
    // Cast QObject to OviNotificationInfo to access the methods
    OviNotificationInfo* info = static_cast<OviNotificationInfo*>(aData);
    displayErrorbox("Notification Id: " + info->notificationId());
    // store NID for later usage
    iNotificationId = info->notificationId();
    delete info;
}

void MainWindow::sslErrors(QNetworkReply * reply, const QList<QSslError> &)
{
    reply->ignoreSslErrors();
}

void MainWindow::resizeEvent (QResizeEvent* )
{
    //showMaximized();
}

// End of file

//For setting up the notifications
void MainWindow::on_pushButton_9_clicked()
{
    QString sEmail=ui->lineEdit_NokiaUserID->text();
    if(sEmail.length()<4)
    {
        ui->textBrowser_3->append("Please enter correct nokia email id.\n Length is less than 4.\n");
        return;
    }
    else{
        QString fileName = NOKIA_USER_ID;
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                ui->textBrowser_3->append("Error: Could not open file. Contact admin@kmdarshan.com");
                return;
            }
            QTextStream stream(&file);
            stream<<sEmail;
            ui->textBrowser_3->append("finished saving email. thanks!");
            file.close();
            setInfo();
            ui->pushButton_9->setEnabled(false);
            setUpNotifications();
            on_registerButton_clicked();
        }
    }
}
