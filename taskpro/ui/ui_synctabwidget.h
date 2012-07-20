/********************************************************************************
** Form generated from reading UI file 'synctabwidget.ui'
**
** Created: Mon Jun 6 20:47:30 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNCTABWIDGET_H
#define UI_SYNCTABWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyncTabWidget
{
public:
    QWidget *tab;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QWidget *tab1;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;

    void setupUi(QTabWidget *SyncTabWidget)
    {
        if (SyncTabWidget->objectName().isEmpty())
            SyncTabWidget->setObjectName(QString::fromUtf8("SyncTabWidget"));
        SyncTabWidget->resize(233, 341);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SyncTabWidget->sizePolicy().hasHeightForWidth());
        SyncTabWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        SyncTabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_3 = new QLineEdit(tab);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 0, 0, 1, 2);

        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 1, 1, 1);

        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 2);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 2);

        SyncTabWidget->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        sizePolicy.setHeightForWidth(tab1->sizePolicy().hasHeightForWidth());
        tab1->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(tab1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(tab1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(tab1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setBaseSize(QSize(0, 15));

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(tab1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(tab1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setBaseSize(QSize(0, 15));

        verticalLayout->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(tab1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        SyncTabWidget->addTab(tab1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(106, 104, 100, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        scrollArea->setPalette(palette);
        QFont font3;
        font3.setPointSize(12);
        scrollArea->setFont(font3);
        scrollArea->setAutoFillBackground(false);
        scrollArea->setLineWidth(2);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 207, 293));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);

        SyncTabWidget->addTab(tab_2, QString());

        retranslateUi(SyncTabWidget);

        SyncTabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SyncTabWidget);
    } // setupUi

    void retranslateUi(QTabWidget *SyncTabWidget)
    {
        SyncTabWidget->setWindowTitle(QApplication::translate("SyncTabWidget", "TabWidget", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("SyncTabWidget", "SYNC POST", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("SyncTabWidget", "DELETE POST", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SyncTabWidget", "BACK", 0, QApplication::UnicodeUTF8));
        SyncTabWidget->setTabText(SyncTabWidget->indexOf(tab), QApplication::translate("SyncTabWidget", "Synched Posts", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SyncTabWidget", "Username", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SyncTabWidget", "Password", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("SyncTabWidget", "SAVE", 0, QApplication::UnicodeUTF8));
        SyncTabWidget->setTabText(SyncTabWidget->indexOf(tab1), QApplication::translate("SyncTabWidget", "Configuration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SyncTabWidget", "How to sync: Enter new username and password in this phone. Give this username and password to the other person you want to sync your posts with.", 0, QApplication::UnicodeUTF8));
        SyncTabWidget->setTabText(SyncTabWidget->indexOf(tab_2), QApplication::translate("SyncTabWidget", "HELP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SyncTabWidget: public Ui_SyncTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNCTABWIDGET_H
