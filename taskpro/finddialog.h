#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include "QList"
#include "QListWidgetItem"
namespace Ui {
    class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    void displayPosts(QList<QListWidgetItem*> qList);

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
