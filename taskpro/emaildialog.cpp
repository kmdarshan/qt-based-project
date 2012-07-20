#include "emaildialog.h"
#include "ui_emaildialog.h"

EmailDialog::EmailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailDialog)
{
    ui->setupUi(this);
}

EmailDialog::~EmailDialog()
{
    delete ui;
}

QString EmailDialog::getEmail()
{
    return ui->lineEdit->text();
}
