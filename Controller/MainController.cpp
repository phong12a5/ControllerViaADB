#include "MainController.h"

#define ADB_CMD ADBCommand::instance()
#define API_COM APICommunication::instance()

MainController* MainController::m_instance = nullptr;

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController *MainController::instance()
{
    if(m_instance == nullptr){
        m_instance = new MainController();
    }
    return m_instance;
}

void MainController::initController()
{
    LOG;
}

void MainController::inputInforToRegGmail()
{
    LOG;
    if(ADB_CMD->currentActivity() == INPUT_YOURNAME_SCREEN){
        // if current screen is enter your name -> enter your name
        if(this->inputYourName()){
            // if input your name is completed, waiting for enter username screen is loaded
            while(ADB_CMD->currentActivity() != INPUT_USERNAME_SCREEN);
            // if current screen is enter username -> username
            if(this->inputUserName()){
                // if Enter username is completed, waiting for create password screen is loaded
                while(ADB_CMD->currentActivity() != INPUT_PASSWORD_SCREEN);
                // If current screen is enter password -> input password
                if(this->inputPassWord()){
                    // If enter password is completed, waiting for creat
                    while(ADB_CMD->currentActivity() != RECOVERY_INTRO_SCREEN);
                    // If current screen is goole password recovery screen -> click Not Now button
                    if(this->findAndClick(NOT_NOW_ICON)){
                        while(ADB_CMD->currentActivity() != GOOGLE_SERVICE_SCREEN);
                        // If current screen is goole service screen -> click Next button
                        if(this->findAndClick(NEXT_YOURNAME_ICON)){
                            while(ADB_CMD->currentActivity() != TERM_SERVICE_SCREEN);
                            // If current screen is Finish account screen -> click I accept button
                            if(this->findAndClick(ACCEPT_BY_ME_ICON)){
                                while(ADB_CMD->currentActivity() != AUTHENTICATING_SCREEN);
                                API_COM->sendCaptchaScreen(ADB_CMD->screenShot());
                            }else{
                                LOG << "Couldn't press Ignore \"Finish accout screen\"";
                            }
                        }else{
                            LOG << "Couldn't press Ignore \"Goole service screen\"";
                        }
                    }else{
                        LOG << "Couldn't press Ignore \"Goole password recovery screen\"";
                    }
                }
            }
        }else{
            LOG << "Enter yourname failed";
            return;
        }
    }else{
        return;
    }
}

bool MainController::inputYourName()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    ADB_CMD->enterText(info.firstName);
    ADB_CMD->pressTap();
    ADB_CMD->enterText(info.lastName);
    delay(500);
    return this->findAndClick(NEXT_YOURNAME_ICON);
}

bool MainController::inputUserName()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    ADB_CMD->enterText(info.userName);
    delay(500);
    return this->findAndClick(NEXT_YOURNAME_ICON);
}

bool MainController::inputPassWord()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    if(info.password.length() < 8){
        LOG << "Password is invalid";
        return false;
    }
    ADB_CMD->enterText(info.password);
    ADB_CMD->pressTap();
    ADB_CMD->enterText(info.password);
    delay(500);
    return this->findAndClick(NEXT_YOURNAME_ICON);
}

void MainController::onStartRegGmailProgram()
{
    LOG;
//    ADB_CMD->screenShot();
//    return;
    int count = 1;
    while (count --) {
//        LOG << "Checking connection ...";
//        while (!ADB_CMD->checkConnection());
//        // when device is connected

//        //Go home screen
//        ADB_CMD->goHomeScreen();

//        // Open xgame
//        ADB_CMD->requestShowApp(XGAME_PKG,XGAME_ACTIVITYMAIN);
//        delay(2000);

//        if(this->findAndClick(AUTO_CHANGE_ICON)){
//            delay(5000);
//        }else{
//            break;
//        }

//        // reboot device
//        ADB_CMD->rebootDevice();
//        delay(2000);
        LOG << "Rebooting and connecting again ...";
        while (!ADB_CMD->checkConnection());

        //Go home screen
        ADB_CMD->goHomeScreen();

        // Open account setting
        ADB_CMD->requestShowAppDirectly(ACCOUNT_SETTING_ACT);
        delay(500);
        // Find google acc icon

        if(this->findAndClick(GOOGLE_ACCOUNT_ICON)){
            delay(500);
            if(this->findAndClick(ADD_NEW_ACC_ICON)){
                this->inputInforToRegGmail();
            }
        }
    }
}

EMAI_INFOR MainController::getEmailInfor(int id)
{
    Q_UNUSED(id);
    EMAI_INFOR infor;
    infor.firstName = "phong";
    infor.lastName = "ba";
    infor.userName = "phong120648293";
    infor.password = "phongdeptrai";
    return infor;
}

bool MainController::findAndClick(QString iconPath)
{
    QString screenImgPath = ADB_CMD->screenShot();
    QPoint point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    if(!point.isNull()){
        ADB_CMD->tapScreen(point);
        return true;
    }else{
        return false;
    }
}
