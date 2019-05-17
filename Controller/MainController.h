#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "Processing/ImageProcessing.h"
#include "Processing/ADBCommand.h"
#include "APICommunication.h"
#include "Processing/HttpRequestController.h"
#include <stdio.h>

class MainController : public QObject
{
    Q_OBJECT

private:
    explicit MainController(QObject *parent = nullptr);

public:
    static MainController* instance();
    void initController();
    EMAI_INFOR& getEmailInfor();
    void startRegGmailProgram();

private:
    bool findAndClick(QString iconPath);
    void inputInforToRegGmail();

    bool inputYourName();
    bool inputUserName();
    bool inputPassWord();
    void inputCapcha();

    void readInforFromFile();
    void setUserInforToReg();
    void saveEmailToOutput();
private:
    static MainController* m_instance;
    EMAI_INFOR m_userInfor;

    QStringList m_firstNameList;
    QStringList m_lastNameList;

signals:

public slots:
};

#endif // MAINCONTROLLER_H
