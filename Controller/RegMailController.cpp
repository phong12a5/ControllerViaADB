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
    this->readInforFromFile();
    this->setUserInforToReg();
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
    LOG;
    m_userInfor.firstName = m_firstNameList.at(rand() % (m_firstNameList.length()));
    m_userInfor.lastName = m_lastNameList.at(rand() % (m_lastNameList.length()));
    m_userInfor.userName = m_userInfor.firstName + m_userInfor.lastName + QString::number(rand() % 100000000 + 1000000);
    m_userInfor.password = /*m_userInfor.firstName + */m_userInfor.lastName + QString::number(rand() % 3000 + 100);
    while (m_userInfor.password.length() < 8) {
        m_userInfor.password = m_userInfor.firstName /*+ m_userInfor.lastName*/ + QString::number(rand() % 3000 + 100);
    }
    m_userInfor.captcha = "";
    LOG << QString("[%1][%2][%3][%4]").arg(m_userInfor.firstName)\
                                        .arg(m_userInfor.lastName)\
                                        .arg(m_userInfor.userName)\
           .arg(m_userInfor.password);
}

void RegMailController::saveEmailToOutput()
{
    LOG;
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
//                this->saveEmailToOutput();
//                this->setUserInforToReg();
                emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),0);
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
            delay(500);
            if(ADBCommand::currentActivity() == SYNC_INTRO_SCREEN){
                if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                    LOG << "Couldn't click NEXT CAPTCHA";
                    this->getEmailInfor().captcha = "";
                    ADBCommand::goHomeScreen();
                }
            }
        }else if(ADBCommand::currentActivity() == WIFI_PICKER_SCREEN){
            LOG << "Back when current screen is wifi setting";
            ADBCommand::pressBack();
        }
    }
}

EMAI_INFOR& RegMailController::getEmailInfor()
{
    if(m_userInfor.userName == "")
        this->readInforFromFile();
    return m_userInfor;
}
