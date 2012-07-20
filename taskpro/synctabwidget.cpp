#include "synctabwidget.h"
#include "ui_synctabwidget.h"
#include <QSize>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#define SYNC_EMAIL_FILE "syncEmail.txt"
#define SYNC_PASSWORD_FILE "syncPassword.txt"
#define SYNC_POSTS_FILE "syncPosts.txt"
#define SYNC_URL "http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?"
#include <QScrollArea>

SyncTabWidget::SyncTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SyncTabWidget)
{
    ui->setupUi(this);
    retryCount = 3;
    QWidget *qw=new QWidget(ui->tab1);


    QLabel *qlb=new QLabel;
    qlb->setText("How to sync: Enter \n new username and password \n in this phone. \n Give this username \n and password to the \n other person you want \n to sync your posts with.");
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(qlb);
    ui->scrollArea->setWidgetResizable(true);
    QWidget *qw2=new QWidget(ui->tab_2);

}

SyncTabWidget::~SyncTabWidget()
{
    delete ui;
}
#include "mainwindow.h"
void SyncTabWidget::on_pushButton_clicked()
{
    //qDebug()<<"in quit";
    this->close();
    //MainWindow *mw = new MainWindow;
    /*MainWindow mw;
    const QRect rect = QApplication::desktop()->geometry();
    int height=rect.height();
    int width=rect.width();
    QRect tmprect(0,0,width,height);
    mw.setGeometry(tmprect);
    mw.showMaximized();
    qDebug()<<rect.width();
    qDebug()<<rect.height();*/

}

QString SyncTabWidget::getEmail()
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
QString SyncTabWidget::getPin()
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

//Slot for clicking on SAVE, saving email and password
//which will be used for syncing
void SyncTabWidget::on_pushButton_2_clicked()
{
    QString fileName = SYNC_EMAIL_FILE;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    QString qemail=ui->lineEdit->text();
    stream<<qemail;
    file.close();

    fileName = SYNC_PASSWORD_FILE;
    QFile file2(fileName);
    file2.open(QIODevice::WriteOnly);
    QTextStream stream2(&file2);
    QString qpwd=ui->lineEdit_2->text();
    stream2<<qpwd;
    file2.close();
}

//this method is used for adding items to the listwidget
void SyncTabWidget::on_pushButton_3_clicked()
{
    QString qStr=ui->lineEdit_3->text();
    if(qStr.size() == 0)
        return;

    QString email=getEmail();
    QString pwd=getPin();
    if(email.endsWith("error") || email.size()==0
       || pwd.endsWith("error") || pwd.size()==0)
    {
        QMessageBox::information(this, tr("Error"),
                                 tr("Unable to sync post, set email and password."));

    }else
    {
        m_syncEmail=email;
        m_syncPassword=pwd;
        m_syncPost=qStr;

        downloadFile();
    }

}

//delete the posts
void SyncTabWidget::on_pushButton_4_clicked()
{

}

void SyncTabWidget::downloadFile()
{

    url = SYNC_URL;
    //url = "http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=from post rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan";
    //http://www.kmdarshan.com/qt/insertAndDisplaySyncPost.php?post=rrrrdaddfrshandfdf&email=kmd%40yahoo.com&pin=darshan
    QString tmpUrl=SYNC_URL;
    tmpUrl.append("post="+m_syncPost+"&email="+m_syncEmail+"&pin="+m_syncPassword);
    //QFileInfo fileInfo(url.path());
    url = tmpUrl;
    qDebug()<<url;
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
    ui->pushButton_3->setEnabled(false);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void SyncTabWidget::cancelDownload()
{
    /*statusLabel->setText(tr("Download canceled."));
    httpRequestAborted = true;
    reply->abort();*/
    ui->pushButton_3->setEnabled(true);
}

void SyncTabWidget::httpFinished()
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
        ui->pushButton_3->setEnabled(true);
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
        ui->pushButton_3->setEnabled(true);

        //After downloading all the files
        //Add data to the list widget
        //Lets start reading from the file to display from the text file
        QString fileName =SYNC_POSTS_FILE;
        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug()<<"Cannot read file";
                return;
            }

            QTextStream in(&file);
            QString lines = in.readLine();
            qDebug()<<"Lines "<<lines;
            QStringList list = lines.split(" $$$ ");
            qDebug()<<"list "<<list;
            QListWidgetItem *item;

            for (int i = 0; i < list.size(); ++i)
            {
                QString tmpString = list.at(i);
                if(tmpString.size()>2)
                {
                   qDebug()<<"temp str "<<tmpString;
                   item=new QListWidgetItem(QIcon(":/images/red.png"),tmpString,ui->listWidget);
                   ui->listWidget->addItem(item);
                   ui->listWidget->setCurrentItem(item);
                }
            }

        }
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void SyncTabWidget::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void SyncTabWidget::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
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

void SyncTabWidget::enableDownloadButton()
{
    ui->pushButton_3->setEnabled(true);
    //downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}

void SyncTabWidget::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)
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
void SyncTabWidget::startRequest(QUrl url)
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

void SyncTabWidget::error(QNetworkReply::NetworkError ne)
{
    reply->disconnect();
    reply->deleteLater();
    QMessageBox::warning(this, tr("HTTP"),
                         tr("An error has occured: %1 (%2 attempts remaining)").arg(reply->errorString()).arg(retryCount));
    if (--retryCount > 0)
        startRequest(url);
}
/*
#ifndef QT_NO_OPENSSL
void SyncTabWidget::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("HTTP"),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
    reply->deleteLater();
    if (--retryCount > 0)
        startRequest(url);
}
#endif*/
