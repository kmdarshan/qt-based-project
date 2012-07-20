#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDate>
#include <QTime>
namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString getDate();
    QString getTime();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
