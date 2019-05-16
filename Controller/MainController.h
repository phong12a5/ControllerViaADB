#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "Processing/ImageProcessing.h"
#include "Processing/ADBCommand.h"
#include "APICommunication.h"
#include "Processing/HttpRequestController.h"

class MainController : public QObject
{
    Q_OBJECT

private:
    explicit MainController(QObject *parent = nullptr);

public:
    static MainController* instance();
    void initController();
    EMAI_INFOR& getEmailInfor(int id = 0);

private:
    bool findAndClick(QString iconPath);
    void inputInforToRegGmail();

    bool inputYourName();
    bool inputUserName();
    bool inputPassWord();
private:
    static MainController* m_instance;
    EMAI_INFOR infor;

signals:

public slots:\
    void onStartRegGmailProgram();
};

#endif // MAINCONTROLLER_H
