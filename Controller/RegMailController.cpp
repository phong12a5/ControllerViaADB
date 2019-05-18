#include "RegMailController.h"
#include "AppMain.h"

#define APP_MAIN        AppMain::instance()
#define HTTP_REQUEST    HttpRequestController::instance()

RegMailController* RegMailController::m_instance = nullptr;

RegMailController::RegMailController(QObject *parent) : QObject(parent)
{

}

RegMailController *RegMailController::instance()
{
    if(m_instance == nullptr){
        m_instance = new RegMailController();
    }
    return m_instance;
}

void RegMailController::initRegMailController()
{
    LOG;
    srand(time(nullptr));
//    this->readInforFromFile();
//    this->setUserInforToReg();
}

void RegMailController::inputInforToRegGmail()
{
    LOG;
    while(ADBCommand::currentActivity() == HOME_SCREEN || ADBCommand::currentActivity() == WIFI_PICKER_SCREEN);
    if(ADBCommand::currentActivity() == INPUT_YOURNAME_SCREEN){
        // if current screen is enter your name -> enter your name
        if(this->inputYourName()){
            // if input your name is completed, waiting for enter username screen is loaded
            while(ADBCommand::currentActivity() != INPUT_USERNAME_SCREEN);
            delay(500);
            // if current screen is enter username -> username
            if(this->inputUserName()){
                // if Enter username is completed, waiting for create password screen is loaded
                LOG << "Wait for load INPUT_PASSWORD_SCREEN";
                while(ADBCommand::currentActivity() != INPUT_PASSWORD_SCREEN);
                delay(500);
                // If current screen is enter password -> input password
                if(this->inputPassWord()){
                    // If enter password is completed, waiting for creat
                    LOG << "Wait for load RECOVERY_INTRO_SCREEN";
                    while(ADBCommand::currentActivity() != RECOVERY_INTRO_SCREEN);
                    delay(500);
                    // If current screen is goole password recovery screen -> click Not Now button
                    if(ADBCommand::findAndClick(NOT_NOW_ICON)){
                        LOG << "Wait for load GOOGLE_SERVICE_SCREEN";
                        while(ADBCommand::currentActivity() != GOOGLE_SERVICE_SCREEN);
                        delay(500);
                        // If current screen is goole service screen -> click Next button
                        if(ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                            LOG << "Wait for load TERM_SERVICE_SCREEN";
                            while(ADBCommand::currentActivity() != TERM_SERVICE_SCREEN);
                            delay(500);
                            // If current screen is Finish account screen -> click I accept button
                            if(ADBCommand::findAndClick(ACCEPT_BY_ME_ICON)){
                                LOG << "Wait for load AUTHENTICATING_SCREEN";
                                while(ADBCommand::currentActivity() != AUTHENTICATING_SCREEN);
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

bool RegMailController::inputYourName()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    ADBCommand::enterText(info.firstName);
    ADBCommand::pressTap();
    ADBCommand::enterText(info.lastName);
    delay(500);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}

bool RegMailController::inputUserName()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    ADBCommand::enterText(info.userName);
    delay(100);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}

bool RegMailController::inputPassWord()
{
    LOG;
    EMAI_INFOR info = this->getEmailInfor();
    if(info.password.length() < 8){
        LOG << "Password is invalid";
        return false;
    }
    ADBCommand::enterText(info.password);
    ADBCommand::pressTap();
    ADBCommand::enterText(info.password);
    delay(100);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}

void RegMailController::inputCapcha()
{
    LOG;
    while(ADBCommand::currentActivity() == AUTHENTICATING_SCREEN){
        this->getEmailInfor().captcha = this->sendCaptcherScreen(ADBCommand::screenShot());

        if(this->getEmailInfor().captcha != ""){
            // Enter captcha
            ADBCommand::enterText(this->getEmailInfor().captcha);
            if(ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                while(ADBCommand::currentActivity() == AUTHENTICATING_SCREEN);
                while(ADBCommand::currentActivity() == "com.google.android.gsf.login/.CreateAccountTask"||
                      ADBCommand::currentActivity() == "com.google.android.gsf.login/.CreateAccountActivity"||
                      ADBCommand::currentActivity() == "com.google.android.gsf.login/.AccountIntroActivity"||
                      ADBCommand::currentActivity() ==  "com.android.settings/.accounts.AddAccountSettings"){
                    LOG << "Saving account";
                }

                if(ADBCommand::currentActivity() ==  AUTHENTICATING_SCREEN){
                    LOG << "Get and enter captcha again";
                    continue;
                }else if(ADBCommand::currentActivity() == PAYMENT_SETTING_SCREEN){
                    ADBCommand::screenShot();
                    while(true);
                }else if(ADBCommand::currentActivity() == "com.google.android.gsf.login/.SyncIntroActivity"){
                    if(ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                        this->saveEmailToOutput();
                        this->setUserInforToReg();
                        LOG << "Register finished !!!";
                    }else{
                        if(ADBCommand::currentActivity() == HOME_SCREEN){
                            this->saveEmailToOutput();
                            this->setUserInforToReg();
                            LOG << "Register finished !!!";
                            break;
                        }else{
                            LOG << "Couln't determine which screen";
                        }
                    }
                }else if(ADBCommand::currentActivity() == HOME_SCREEN){
                    this->saveEmailToOutput();
                    this->setUserInforToReg();
                    LOG << "Register finished !!!";
                    break;
                }else{
                    LOG << "UNKNOW RESULT -> EXIT";
                }
            }
        }
    }
}

void RegMailController::readInforFromFile()
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

void RegMailController::setUserInforToReg()
{
    QStringList specialCharList = QStringList() << "#" << "@" << "!" << "*" << "%" << "$";
    m_userInfor.firstName = m_firstNameList.at(rand() % (m_firstNameList.length()));
    m_userInfor.lastName = m_lastNameList.at(rand() % (m_lastNameList.length()));
    m_userInfor.userName = m_userInfor.firstName + m_userInfor.lastName + QString::number(rand() % 100000000000 + 10000000);
    m_userInfor.password = m_userInfor.firstName + m_userInfor.lastName + specialCharList.at(rand() % (specialCharList.length())) + QString::number(rand() % 10000000 + 1000000);
    m_userInfor.captcha = "";
    LOG << QString("[%1][%2][%3][%4]").arg(m_userInfor.firstName)\
                                        .arg(m_userInfor.lastName)\
                                        .arg(m_userInfor.userName)\
           .arg(m_userInfor.password);
}

void RegMailController::saveEmailToOutput()
{
    QFile outputFile(OUTPUT_FILE);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        LOG << "Couldn't open output file";
        return;
    }

    QTextStream out(&outputFile);
    out << (this->getEmailInfor().userName + "@gmail.com|" + this->getEmailInfor().password) << "\n";
}

QString RegMailController::sendCaptcherScreen(QString screenPath)
{
    QString captchaImg = ImageProcessing::extractCaptchaImage(screenPath);
    delay(1000);
    LOG << "captchaImg: " << captchaImg;
    if(captchaImg != QString("")){
        return HttpRequestController::instance()->sendHttpRequest(QString("http://poster.de-captcher.com"),\
                                                           QDir::currentPath() + "/captcha.png");
    }else {
        return QString("");
    }
}

void RegMailController::onCurrentActivityChanged()
{
    LOG << "[RegMailController]";
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_REG_GMAIL){
        // Handle when currentExcuteStep = E_EXCUTE_REG_GMAIL
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN ||
           APP_MAIN->getCurrentActivity() == NONE_SCREEN)
        {
            if(this->getEmailInfor().captcha != ""){
                this->setUserInforToReg();
                this->saveEmailToOutput();
                APP_MAIN->setCurrentExcuteStep(AppEnums::E_EXCUTE_REG_FACBOOK);
                emit APP_MAIN->currentActivityChanged();
            }else{
                LOG << "Reqest to go to account setting screen";
                ADBCommand::requestShowAppDirectly(ACCOUNT_SETTING_ACT);
            }
        }else if(APP_MAIN->getCurrentActivity() == ACCOUNT_SETTING_SCREEN){

            if(ADBCommand::findAndClick(GOOGLE_ACCOUNT_ICON)){
                // Do nothing
            }else{
                LOG << "Couldn't click GOOGLE_ACCOUNT_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == ADD_A_GGACCOUNT_SCREEN){
            if(ADBCommand::findAndClick(ADD_NEW_ACC_ICON)){
                // Do nothing
            }else{
                LOG << "Couldn't click ADD_NEW_ACC_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_YOURNAME_SCREEN){
            if(!this->inputYourName()){
                LOG << "Couldn't input your name";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_USERNAME_SCREEN){
            if(!this->inputUserName()){
                LOG << "Couldn't input username";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_PASSWORD_SCREEN){
            if(!this->inputPassWord()){
                LOG << "Couldn't input password";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == RECOVERY_INTRO_SCREEN){
            if(!ADBCommand::findAndClick(NOT_NOW_ICON)){
                LOG << "Couldn't click NOT_NOW_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == GOOGLE_SERVICE_SCREEN){
            if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                LOG << "Couldn't click NEXT_YOURNAME_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == TERM_SERVICE_SCREEN){
            if(!ADBCommand::findAndClick(ACCEPT_BY_ME_ICON)){
                LOG << "Couldn't click NEXT_YOURNAME_ICON";
                ADBCommand::goHomeScreen();
            }

        }else if(APP_MAIN->getCurrentActivity() == AUTHENTICATING_SCREEN){
            this->getEmailInfor().captcha = this->sendCaptcherScreen(ADBCommand::screenShot());

            while (this->getEmailInfor().captcha == "" && APP_MAIN->getCurrentActivity() == AUTHENTICATING_SCREEN) {
                this->getEmailInfor().captcha = this->sendCaptcherScreen(ADBCommand::screenShot());
            }

            ADBCommand::enterText(this->getEmailInfor().captcha);
            if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                LOG << "Couldn't click NEXT CAPTCHA";
                this->getEmailInfor().captcha = "";
                ADBCommand::goHomeScreen();
            }

        }else if(ADBCommand::currentActivity() == SYNC_INTRO_SCREEN){
            if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                LOG << "Couldn't click NEXT CAPTCHA";
                this->getEmailInfor().captcha = "";
                ADBCommand::goHomeScreen();
            }
        }
    }
}

void RegMailController::startRegGmailProgram()
{
    LOG;

    while (true) {
        LOG << "Checking connection ...";
        while (!ADBCommand::checkConnection());
        // when device is connected

    }
}

EMAI_INFOR& RegMailController::getEmailInfor()
{
//    if(m_userInfor.userName == "")
//        this->readInforFromFile();
    return m_userInfor;
}
