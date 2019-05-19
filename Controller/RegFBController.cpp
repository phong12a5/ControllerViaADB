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
    }

    LOG << "screenID: " << screenID << " --- reval:" << retVal;

    return retVal;
}

int RegFBController::findCurrentScreen() const
{
    LOG;
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
        ADBCommand::enterText("Phong");
        ADBCommand::findAndClick(LASTNAME_FIELD);
        ADBCommand::enterText("Dang ");
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        // Do something
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    }
}
