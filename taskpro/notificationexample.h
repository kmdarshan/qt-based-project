/*
 *  This file is part of Notifications API 
 *  Copyright © 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *  Contact:  notifications.support@nokia.com
 *  This software, including documentation, is protected by copyright controlled by Nokia Corporation. 
 *  All rights reserved. You may use this file only in accordance with the Nokia Developer Software 
 *  Agreement version 2.0 and accompanying Ovi any additional terms. This material also contains 
 *  confidential information which may not be disclosed to others without the prior written consent of Nokia.
 */

#ifndef NOTIFICATIONEXAMPLE_H
#define NOTIFICATIONEXAMPLE_H

#include <QMainWindow>
#include <QNetworkAccessManager>

class OviNotificationSession;

namespace Ui {
    class NotificationExample;
}

class NotificationExample
{
    Q_OBJECT

public:
    explicit NotificationExample();
    ~NotificationExample();
    void displayErrorbox(QString qError);

private slots:
    void on_wakeupCheckBox_stateChanged(int );
    void on_notificationUiCheckBox_stateChanged(int );
    void on_settingsButton_clicked();
    void on_sendNotificationIdButton_clicked();
    void on_notificationIdButton_clicked();
    void on_unregisterButton_clicked();
    void on_registerButton_clicked();
    void on_notificationIconSelectionBox_highlighted(QString );
	
private slots:


    /*!
     * State of the Notifications application session has been changed. Check the new state
     * and possible error.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aMessage OviNotificationMessage from OviNotificationInterface.
     */
    void stateChanged(QObject* aState);

    /*!
     * Received notification from the Notifications service.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aNotification OviNotificationMessage from OviNotificationInterface.
     */
    void received(QObject* aNotification);

    /*!
     * Callback for version request
     *
     */
    void versionResponse(QString aVersion);

    /*!
     * Address for the service to identify Notifications application.
     *
     * Note! Ownership is passed and you must handle the deletion of the object.
     * @param aData OviNotificationMessage from OviNotificationInterface.
     */
    void notificationInfo(QObject* aData);

    /*!
     * Callback for handling possible SSL errors
     *
     */
    void sslErrors(QNetworkReply * reply, const QList<QSslError> & errors);

    /*!
     * Handles orientation change
     *
     */
    void resizeEvent (QResizeEvent* event);

private:

    /*!
     * Loads Notifications Enabler interface and connects the signals to example application.
     */
    bool initialize();

private:

    OviNotificationSession*   iNotificationSession;
    QString                     iIconData;
    QNetworkAccessManager*      iHttpManager;
    QString                     iNotificationId;

};

#endif // NOTIFICATIONEXAMPLE_H

