#include "MainController.h"

#define ADB_CMD ADBCommand::instance()
#define API_COM APICommunication::instance()
#define HTTP_REQUEST HttpRequestController::instance()

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
    srand(time(nullptr));
    this->readInforFromFile();
    this->setUserInforToReg();
}

void MainController::inputInforToRegGmail()
{
    LOG;
    while(ADB_CMD->currentActivity() == HOME_SCREEN || ADB_CMD->currentActivity() == WIFI_PICKER_SCREEN);
    if(ADB_CMD->currentActivity() == INPUT_YOURNAME_SCREEN){
        // if current screen is enter your name -> enter your name
        if(this->inputYourName()){
            // if input your name is completed, waiting for enter username screen is loaded
            while(ADB_CMD->currentActivity() != INPUT_USERNAME_SCREEN);
            delay(500);
            // if current screen is enter username -> username
            if(this->inputUserName()){
                // if Enter username is completed, waiting for create password screen is loaded
                LOG << "Wait for load INPUT_PASSWORD_SCREEN";
                while(ADB_CMD->currentActivity() != INPUT_PASSWORD_SCREEN);
                delay(500);
                // If current screen is enter password -> input password
                if(this->inputPassWord()){
                    // If enter password is completed, waiting for creat
                    LOG << "Wait for load RECOVERY_INTRO_SCREEN";
                    while(ADB_CMD->currentActivity() != RECOVERY_INTRO_SCREEN);
                    delay(500);
                    // If current screen is goole password recovery screen -> click Not Now button
                    if(this->findAndClick(NOT_NOW_ICON)){
                        LOG << "Wait for load GOOGLE_SERVICE_SCREEN";
                        while(ADB_CMD->currentActivity() != GOOGLE_SERVICE_SCREEN);
                        delay(500);
                        // If current screen is goole service screen -> click Next button
                        if(this->findAndClick(NEXT_YOURNAME_ICON)){
                            LOG << "Wait for load TERM_SERVICE_SCREEN";
                            while(ADB_CMD->currentActivity() != TERM_SERVICE_SCREEN);
                            delay(500);
                            // If current screen is Finish account screen -> click I accept button
                            if(this->findAndClick(ACCEPT_BY_ME_ICON)){
                                LOG << "Wait for load AUTHENTICATING_SCREEN";
                                while(ADB_CMD->currentActivity() != AUTHENTICATING_SCREEN);
                                delay(500);
                                this->inputCapcha();
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
    delay(100);
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
    delay(100);
    return this->findAndClick(NEXT_YOURNAME_ICON);
}

void MainController::inputCapcha()
{
    LOG;
    while(ADB_CMD->currentActivity() == AUTHENTICATING_SCREEN){
        this->getEmailInfor().captcha = API_COM->sendCaptcherScreen(ADB_CMD->screenShot());

        if(this->getEmailInfor().captcha != ""){
            // Enter captcha
            ADB_CMD->enterText(this->getEmailInfor().captcha);
            if(this->findAndClick(NEXT_YOURNAME_ICON)){
                while(ADB_CMD->currentActivity() == AUTHENTICATING_SCREEN);
                while(ADB_CMD->currentActivity() == "com.google.android.gsf.login/.CreateAccountTask"||
                      ADB_CMD->currentActivity() == "com.google.android.gsf.login/.CreateAccountActivity"||
                      ADB_CMD->currentActivity() == "com.google.android.gsf.login/.SyncIntroActivity"||
                      ADB_CMD->currentActivity() == "com.google.android.gsf.login/.AccountIntroActivity"||
                      ADB_CMD->currentActivity() ==  "com.android.settings/.accounts.AddAccountSettings"){
                    LOG << "Saving account";
                }

                if(ADB_CMD->currentActivity() ==  AUTHENTICATING_SCREEN){
                    LOG << "Get and enter captcha again";
                    continue;
                }else if(ADB_CMD->currentActivity() == HOME_SCREEN){
                    this->saveEmailToOutput();
                    this->setUserInforToReg();
                    LOG << "Register finished !!!";
                    delay(1000);
                    break;
                }else{
                    LOG << "UNKNOW RESULT -> EXIT";
                }
            }
        }
    }
}

void MainController::readInforFromFile()
{
    LOG;
    QFile firstNameFile(FIRST_NAME_FILE);
    if (!firstNameFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG << "Couldn't read first name file";
        return;
    }

    QFile lastNameFile(LAST_NAME_FILE);
    if (!lastNameFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG << "Couldn't read last name file";
        return;
    }

    m_firstNameList.clear();
    m_lastNameList.clear();

    while (!firstNameFile.atEnd()) {
        QString tmp = firstNameFile.readLine().simplified();
        m_firstNameList.append(tmp);
    }

    while (!lastNameFile.atEnd()) {
        QString tmp = lastNameFile.readLine().simplified();
        m_lastNameList.append(tmp);
    }

    LOG << "m_firstNameList: " << m_firstNameList.length();
    LOG << "m_lastNameList: " << m_lastNameList.length();
}

void MainController::setUserInforToReg()
{
    QStringList specialCharList = QStringList() << "#" << "@" << "!" << "*" << "%" << "$";
    m_userInfor.firstName = m_firstNameList.at(rand() % (m_firstNameList.length()));
    m_userInfor.lastName = m_lastNameList.at(rand() % (m_lastNameList.length()));
    m_userInfor.userName = m_userInfor.firstName + m_userInfor.lastName + QString::number(rand() % 100000000000 + 10000000);
    m_userInfor.password = m_userInfor.firstName + m_userInfor.lastName + specialCharList.at(rand() % (specialCharList.length())) + QString::number(rand() % 10000000 + 1000000);
    LOG << QString("[%1][%2][%3][%4]").arg(m_userInfor.firstName)\
                                        .arg(m_userInfor.lastName)\
                                        .arg(m_userInfor.userName)\
           .arg(m_userInfor.password);
}

void MainController::saveEmailToOutput()
{
    QFile outputFile(OUTPUT_FILE);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        LOG << "Couldn't open output file";
        return;
    }

    QTextStream out(&outputFile);
    out << (this->getEmailInfor().userName + "@gmail.com|" + this->getEmailInfor().password) << "\n";
}

void MainController::startRegGmailProgram()
{
    LOG;

    while (true) {
        LOG << "Checking connection ...";
        while (!ADB_CMD->checkConnection());
        // when device is connected

        //Go home screen
        ADB_CMD->goHomeScreen();

        // Open xgame
        ADB_CMD->requestShowApp(XGAME_PKG,XGAME_ACTIVITYMAIN);
        delay(1000);

        if(this->findAndClick(AUTO_CHANGE_ICON)){
            delay(8000);
        }else{
            continue;
        }

        // reboot device
        ADB_CMD->rebootDevice();
        delay(2000);
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
            }else{
                LOG << "Couldn't click ADD_NEW_ACC_ICON";
                continue;
            }
        }else{
            LOG << "Couldn't click GOOGLE_ACCOUNT_ICON";
            continue;
        }
    }
}

EMAI_INFOR& MainController::getEmailInfor()
{
    if(m_userInfor.userName == "")
        this->readInforFromFile();
    return m_userInfor;
}

bool MainController::findAndClick(QString iconPath)
{
    QString screenImgPath = ADB_CMD->screenShot();
    QPoint point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    if(!point.isNull()){
        ADB_CMD->tapScreen(point);
        return true;
    }else{
        screenImgPath = ADB_CMD->screenShot();
        point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
        if(!point.isNull()){
            ADB_CMD->tapScreen(point);
            return true;
        }else{
            return false;
        }
    }
}
