#ifndef REGMAILCONTROLLER_H
#define REGMAILCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "Processing/ImageProcessing.h"
#include "Processing/ADBCommand.h"
#include "Processing/HttpRequestController.h"
#include <stdio.h>
#include "Base/RegControllerBase.h"

class RegMailController : public RegControllerBase
{
    Q_OBJECT

private:
    explicit RegMailController(QObject *parent = nullptr);

public:
    static RegMailController* instance();
    void initRegMailController();
    EMAI_INFOR& getEmailInfor();
    void setUserInforToReg();
    void saveEmailToOutput();

private:
    bool inputYourName();
    bool inputUserName();
    bool inputPassWord();

    void readInforFromFile();
    QString sendCaptcherScreen(QString screenPath);

private:
    static RegMailController* m_instance;
    EMAI_INFOR m_userInfor;

    QStringList m_firstNameList;
    QStringList m_lastNameList;

signals:

public slots:
    void onCurrentActivityChanged() override;
};

#endif // REGMAILCONTROLLER_H
