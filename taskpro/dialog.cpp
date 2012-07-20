#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getDate()
{
    return ui->dateEdit->text();
}

QString Dialog::getTime()
{
    return ui->timeEdit->text();
}
