/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Mon Jun 6 20:47:30 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QDateEdit *dateEdit;
    QTimeEdit *timeEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(178, 320);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dateEdit = new QDateEdit(Dialog);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setBaseSize(QSize(10, 10));
        QFont font;
        font.setPointSize(13);
        dateEdit->setFont(font);
        dateEdit->setDateTime(QDateTime(QDate(2011, 3, 15), QTime(0, 0, 0)));
        dateEdit->setTime(QTime(0, 0, 0));
        dateEdit->setMinimumDate(QDate(2011, 3, 1));
        dateEdit->setDate(QDate(2011, 3, 15));

        verticalLayout->addWidget(dateEdit);

        timeEdit = new QTimeEdit(Dialog);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setBaseSize(QSize(10, 10));
        timeEdit->setFont(font);
        timeEdit->setWrapping(false);
        timeEdit->setReadOnly(false);
        timeEdit->setCalendarPopup(true);
        timeEdit->setTime(QTime(10, 10, 0));

        verticalLayout->addWidget(timeEdit);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("Dialog", "MM/dd/yyyy", 0, QApplication::UnicodeUTF8));
        timeEdit->setDisplayFormat(QApplication::translate("Dialog", "h:m:s AP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
