#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "Processing/ImageProcessing.h"
#include "Processing/ADBCommand.h"
#include "APICommunication.h"

class MainController : public QObject
{
    Q_OBJECT

private:
    explicit MainController(QObject *parent = nullptr);

public:
    static MainController* instance();
    void initController();

private:
    EMAI_INFOR getEmailInfor(int id = 0);
    bool findAndClick(QString iconPath);
    void inputInforToRegGmail();

    bool inputYourName();
    bool inputUserName();
    bool inputPassWord();
private:
    static MainController* m_instance;

signals:

public slots:\
    void onStartRegGmailProgram();
};

#endif // MAINCONTROLLER_H
