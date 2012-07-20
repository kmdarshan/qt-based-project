#ifndef EMAILDIALOG_H
#define EMAILDIALOG_H

#include <QDialog>

namespace Ui {
    class EmailDialog;
}

class EmailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmailDialog(QWidget *parent = 0);
    ~EmailDialog();
    QString getEmail();
private:
    Ui::EmailDialog *ui;
};

#endif // EMAILDIALOG_H
