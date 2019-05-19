#include "RegFBController.h"
#include "AppMain.h"

#define APP_MAIN        AppMain::instance()

RegFBController* RegFBController::m_intance = nullptr;

RegFBController::RegFBController(QObject *parent) : QObject(parent)
{
    m_currentScreenID = -1;
}

RegFBController *RegFBController::instance()
{
    if(m_intance == nullptr){
        m_intance = new RegFBController();
    }
    return m_intance;
}

void RegFBController::initRegFBController()
{
    LOG;
    m_checkScreenTimer.setInterval(100);
    m_checkScreenTimer.setSingleShot(false);

    connect(&m_checkScreenTimer,SIGNAL(timeout()),this,SLOT(onCheckCurrentScreen()));
    connect(this,SIGNAL(currentScreenChange()),this,SLOT(onUpdateAction()));
}

void RegFBController::clearCacheFBLite()
{
    LOG;
    this->setCurrentScreen(-1);
    ADBCommand::clearCacheOfPackage(FBLITE_PKG);
}

EMAI_INFOR &RegFBController::getUserInfo()
{
    return RegMailController::instance()->getEmailInfor();
}

int RegFBController::currentScreen() const
{
    return m_currentScreenID;
}

void RegFBController::setCurrentScreen(const int screenID)
{
    if(m_currentScreenID != screenID){
        m_currentScreenID = screenID;
        emit currentScreenChange();
    }
}

bool RegFBController::isCurrentScreen(int screenID) const
{
    bool retVal = false;
    switch (screenID) {
        case AppEnums::E_FBLITE_SCREEN_ID_LOGIN:
        retVal = ADBCommand::findAnImageOnScreen(CREATE_NEW_FBACC_ICON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB:
        retVal = ADBCommand::findAnImageOnScreen(JOIN_FB_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME:
        retVal = ADBCommand::findAnImageOnScreen(WHAT_YOUR_NAME_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        retVal = ADBCommand::findAnImageOnScreen(ENTER_MOBILE_NUM_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        retVal = ADBCommand::findAnImageOnScreen(WHAT_YOUR_BIRTHDAY);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER:
        retVal = ADBCommand::findAnImageOnScreen(WHAT_YOUR_GENDER);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD:
        retVal = ADBCommand::findAnImageOnScreen(CREATE_PASS_SCREEN);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO:
        retVal = ADBCommand::findAnImageOnScreen(SAVE_LOGIN_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ADD_YOUR_EMAIL:
        retVal = ADBCommand::findAnImageOnScreen(ADD_YOUR_EMAIL);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL:
        retVal = ADBCommand::findAnImageOnScreen(CONFIRM_EMAIL);
        break;
    }

    LOG << "screenID: " << screenID << " --- reval:" << retVal;

    return retVal;
}

int RegFBController::findCurrentScreen() const
{
    LOG;
}

int RegFBController::getGenderRandomly() const
{
    return rand() %2 + 0;
}

void RegFBController::onCurrentActivityChanged()
{
    LOG << "[RegFBController]";
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_REG_FACBOOK){
        // Handle when currentExcuteStep = E_EXCUTE_REG_GMAIL
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN ||
                APP_MAIN->getCurrentActivity() == NONE_SCREEN)
        {
            this->clearCacheFBLite();
            LOG << "Reqest to go to Facebook Lite application";
            ADBCommand::requestShowApp(FBLITE_PKG,FBLITE_ACTIVITYMAIN);
        }else if(APP_MAIN->getCurrentActivity() == FACEBOOK_LITE_SCREEN){
            m_checkScreenTimer.start();
        }
    }else{
        m_checkScreenTimer.stop();
    }
}

void RegFBController::onCheckCurrentScreen()
{
    LOG;
    if(this->currentScreen() < 0){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_LOGIN)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_LOGIN);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_LOGIN){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ADD_YOUR_EMAIL)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ADD_YOUR_EMAIL);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }else if(this->currentScreen() == AppEnums::E_FBLITE_SCREEN_ID_ADD_YOUR_EMAIL){
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL);
        }else{
//            this->setCurrentScreen(this->findCurrentScreen());
        }
    }
}

void RegFBController::onUpdateAction()
{
    LOG << "current screen: " << this->currentScreen();
    if(APP_MAIN->currentExcuteStep() != AppEnums::E_EXCUTE_REG_FACBOOK)
        return;

    switch (this->currentScreen()) {
        case AppEnums::E_FBLITE_SCREEN_ID_LOGIN:
        ADBCommand::findAndClick(CREATE_NEW_FBACC_ICON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB:
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME:
        ADBCommand::findAndClick(FIRSTNAME_FIELD);
        ADBCommand::enterText(getUserInfo().firstName);
        ADBCommand::findAndClick(LASTNAME_FIELD);
        ADBCommand::enterText(getUserInfo().lastName);
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        // Do something
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER:
        // Do something
    {
        QString icon;
        if(this->getGenderRandomly() == 0){
            icon = FEMALE_BUTTON;
        }else{
            icon = MALE_BUTTON;
        }
        ADBCommand::findAndClick(icon);
    }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD:
        ADBCommand::findAndClick(PASSWORD_FIELD);
        ADBCommand::enterText(getUserInfo().password);
        ADBCommand::findAndClick(SIGN_UP_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO:
        ADBCommand::findAndClick(NOT_NOW_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ADD_YOUR_EMAIL:
        ADBCommand::findAndClick(GAMIL_RADIO_BTN);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL:
        ADBCommand::findAndClick(YES_BTN);
        break;
    }
}
