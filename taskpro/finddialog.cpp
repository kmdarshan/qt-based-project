#include "finddialog.h"
#include "ui_finddialog.h"
#include "qdebug.h"
FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::displayPosts(QList<QListWidgetItem*> qList)
{
    //qDebug()<<qList;
    QList<QListWidgetItem*>::iterator i;
    QString finalString="";
    for (i = qList.begin(); i != qList.end(); ++i)
    {
        QListWidgetItem *qlwItem;
        qlwItem=*i;
        QString qsTxt=qlwItem->text();
        finalString=finalString+qsTxt+"<br>";
    }
    //qDebug()<<finalString;
    ui->textBrowser->setText(finalString);
}
