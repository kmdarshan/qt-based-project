#-------------------------------------------------
#
# Project created by QtCreator 2010-11-08T14:44:01
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = taskpro
TEMPLATE = app
CONFIG += ovinotifications

SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    errordialog.cpp \
    emaildialog.cpp \
    httpcommunicator.cpp \
    dialog.cpp \
    synctabwidget.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    errordialog.h \
    emaildialog.h \
    httpcommunicator.h \
    httpcommunicator.h \
    dialog.h \
    synctabwidget.h

FORMS    += mainwindow.ui \
    finddialog.ui \
    errordialog.ui \
    emaildialog.ui \
    dialog.ui \
    synctabwidget.ui

symbian {
    TARGET.UID3 = 0x20037391
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
    TARGET.CAPABILITY = NetworkServices
    TARGET.VID = 0
    TARGET.EPOCALLOWDLLDATA = 1
}

simulator {

    windows {
        DESTDIR = $$[QT_INSTALL_PREFIX]/../../OviNotifications
    }
}
OTHER_FILES += Done.png\
            red.png\
    myappico.ico \
    icon_1.svg \
    clock.png \
    search.png

RC_FILE = myapp.rc

RESOURCES += \
    donelogo.qrc\

symbian {
    ICON = icon_1.svg
}

customrules.pkg_prerules = \
        "; Localised Vendor name" \
        "%{\"Redflower Inc\"}" \
        " " \
        "; Unique Vendor name" \
        ":\"Redflower Inc\""

DEPLOYMENT += customrules
