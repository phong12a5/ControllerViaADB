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
    LOG << "[RegMailController]";
    srand(time(nullptr));
    this->readInforFromFile();
    this->setUserInforToReg();
}


bool RegMailController::inputYourName()
{
    LOG << "[RegMailController]";
    EMAI_INFOR info = this->getEmailInfor();
    ADBCommand::enterText(info.firstName);
    ADBCommand::pressTap();
    ADBCommand::enterText(info.lastName);
    delay(500);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}

bool RegMailController::inputUserName()
{
    LOG << "[RegMailController]";
    EMAI_INFOR info = this->getEmailInfor();
    ADBCommand::enterText(info.userName);
    delay(100);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}

bool RegMailController::inputPassWord()
{
    LOG << "[RegMailController]";
    EMAI_INFOR info = this->getEmailInfor();
    if(info.gmailPassword.length() < 8){
        LOG << "[RegMailController]" << "Password is invalid";
        return false;
    }
    ADBCommand::enterText(info.gmailPassword);
    ADBCommand::pressTap();
    ADBCommand::enterText(info.gmailPassword);
    delay(100);
    return ADBCommand::findAndClick(NEXT_YOURNAME_ICON);
}



void RegMailController::readInforFromFile()
{
    LOG << "[RegMailController]";
    QFile firstNameFile(FIRST_NAME_FILE);
    if (!firstNameFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG << "[RegMailController]" << "Couldn't read first name file";
        return;
    }

    QFile lastNameFile(LAST_NAME_FILE);
    if (!lastNameFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        LOG << "[RegMailController]" << "Couldn't read last name file";
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

    LOG << "[RegMailController]" << "m_firstNameList: " << m_firstNameList.length();
    LOG << "[RegMailController]" << "m_lastNameList: " << m_lastNameList.length();
}

void RegMailController::setUserInforToReg()
{
    LOG << "[RegMailController]";
    if(m_firstNameList.isEmpty() || m_lastNameList.isEmpty())
        return;
#ifdef USE_KEYBOARD
    m_userInfor.firstName = m_firstNameList.at(rand() % (m_firstNameList.length())).toLower();
    m_userInfor.lastName = m_lastNameList.at(rand() % (m_lastNameList.length())).toLower();
#else
    m_userInfor.firstName = m_firstNameList.at(rand() % (m_firstNameList.length()));
    m_userInfor.lastName = m_lastNameList.at(rand() % (m_lastNameList.length()));
#endif
    m_userInfor.userName = m_userInfor.firstName + m_userInfor.lastName + QString::number(rand() % 1000000000 + 3000000);
    m_userInfor.gmailPassword = m_userInfor.firstName + m_userInfor.lastName + QString::number(rand() % 30000 + 10000);
    m_userInfor.captcha = "";

#ifdef USE_KEYBOARD
    QStringList charList;
    charList << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h" << "i" << "k"
             << "l" << "m" << "n" << "o" << "p" << "r" << "s" << "t" << "x" << "y" << "z";
    m_userInfor.fbPassword = m_userInfor.lastName + m_userInfor.firstName + charList.at(rand() % charList.length());
    while (m_userInfor.fbPassword.length() < 8) {
        m_userInfor.fbPassword += charList.at(rand() % charList.length());
    }
#else
    QStringList charList;
    charList << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h" << "i" << "k"
             << "l" << "m" << "n" << "o" << "p" << "r" << "s" << "t" << "x" << "y" << "z";
    QStringList numberList = QStringList() << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "z";

    m_userInfor.fbPassword = m_userInfor.firstName;
    while (m_userInfor.fbPassword.length() < 8) {
        m_userInfor.fbPassword += numberList.at(rand() % numberList.length());
    }
#endif

    LOG << "[RegMailController]" << QString("[%1][%2][%3]").arg(m_userInfor.userName)\
                                  .arg(m_userInfor.gmailPassword)\
                                  .arg(m_userInfor.fbPassword);
}

void RegMailController::saveEmailToOutput()
{
    LOG << "[RegMailController]";
    QFile outputFile(OUTPUT_FILE);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        LOG << "[RegMailController]" << "Couldn't open output file";
        return;
    }

    QTextStream out(&outputFile);
    out << (this->getEmailInfor().userName + "@gmail.com|" + this->getEmailInfor().gmailPassword) << "|" << this->getEmailInfor().fbPassword <<  "\n";
}

QString RegMailController::sendCaptcherScreen(QString screenPath)
{
    QString captchaImg = ImageProcessing::extractCaptchaImage(screenPath);
    delay(1000);
    LOG << "[RegMailController]" << "captchaImg: " << captchaImg;
    if(captchaImg != QString("")){
        return HttpRequestController::instance()->sendHttpRequest(QString("http://poster.de-captcher.com"),\
                                                           QDir::currentPath() + "/captcha.png");
    }else {
        return QString("");
    }
}

void RegMailController::onCurrentActivityChanged()
{
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_REG_GMAIL){
        // Handle when currentExcuteStep = E_EXCUTE_REG_GMAIL
        LOG << "[RegMailController]" << APP_MAIN->getCurrentActivity();
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN ||
           APP_MAIN->getCurrentActivity() == NONE_SCREEN)
        {
            if(this->getEmailInfor().captcha != ""){
//                this->saveEmailToOutput();
//                this->setUserInforToReg();
                emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),0);
            }else{
                LOG << "[RegMailController]" << "Reqest to go to account setting screen";
                ADBCommand::requestShowAppDirectly(ACCOUNT_SETTING_ACT);
            }
        }else if(APP_MAIN->getCurrentActivity() == ACCOUNT_SETTING_SCREEN){

            if(ADBCommand::findAndClick(GOOGLE_ACCOUNT_ICON)){
                // Do nothing
            }else{
                LOG << "[RegMailController]" << "Couldn't click GOOGLE_ACCOUNT_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == ADD_A_GGACCOUNT_SCREEN){
            if(ADBCommand::findAndClick(ADD_NEW_ACC_ICON)){
                // Do nothing
            }else{
                LOG << "[RegMailController]" << "Couldn't click ADD_NEW_ACC_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_YOURNAME_SCREEN){
            if(!this->inputYourName()){
                LOG << "[RegMailController]" << "Couldn't input your name";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_USERNAME_SCREEN){
            if(!this->inputUserName()){
                LOG << "[RegMailController]" << "Couldn't input username";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == INPUT_PASSWORD_SCREEN){
            if(!this->inputPassWord()){
                LOG << "[RegMailController]" << "Couldn't input password";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == RECOVERY_INTRO_SCREEN){
            if(!ADBCommand::findAndClick(NOT_NOW_ICON)){
                LOG << "[RegMailController]" << "Couldn't click NOT_NOW_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == GOOGLE_SERVICE_SCREEN){
            if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                LOG << "[RegMailController]" << "Couldn't click NEXT_YOURNAME_ICON";
                ADBCommand::goHomeScreen();
            }
        }else if(APP_MAIN->getCurrentActivity() == TERM_SERVICE_SCREEN){
            if(!ADBCommand::findAndClick(ACCEPT_BY_ME_ICON)){
                LOG << "[RegMailController]" << "Couldn't click NEXT_YOURNAME_ICON";
                ADBCommand::goHomeScreen();
            }

        }else if(APP_MAIN->getCurrentActivity() == AUTHENTICATING_SCREEN){
            this->getEmailInfor().captcha = this->sendCaptcherScreen(ADBCommand::screenShot());

            while (this->getEmailInfor().captcha == "" && APP_MAIN->getCurrentActivity() == AUTHENTICATING_SCREEN) {
                this->getEmailInfor().captcha = this->sendCaptcherScreen(ADBCommand::screenShot());
            }

            ADBCommand::enterText(this->getEmailInfor().captcha);
            if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                LOG << "[RegMailController]" << "Couldn't click NEXT CAPTCHA";
                this->getEmailInfor().captcha = "";
                ADBCommand::goHomeScreen();
            }

        }else if(ADBCommand::currentActivity() == SYNC_INTRO_SCREEN){
            delay(500);
            if(ADBCommand::currentActivity() == SYNC_INTRO_SCREEN){
                if(!ADBCommand::findAndClick(NEXT_YOURNAME_ICON)){
                    LOG << "[RegMailController]" << "Couldn't click NEXT CAPTCHA";
                    this->getEmailInfor().captcha = "";
                    ADBCommand::goHomeScreen();
                }
            }
        }else if(ADBCommand::currentActivity() == PAYMENT_SETTING_SCREEN){
            if(!ADBCommand::findAndClick(SKIP_PAYMENT_ICON)){
                LOG << "[RegMailController]" << "Couldn't click SKIP PAYMENT";
                this->getEmailInfor().captcha = "";
                ADBCommand::goHomeScreen();
            }
        }else if(ADBCommand::currentActivity() == WIFI_PICKER_SCREEN){
            LOG << "[RegMailController]" << "Back when current screen is wifi setting";
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
