#include "RegDeviceInfoController.h"
#include "AppMain.h"

#define APP_MAIN AppMain::instance()

RegDeviceInfoController* RegDeviceInfoController::m_intance = nullptr;

RegDeviceInfoController::RegDeviceInfoController(QObject *parent) : QObject(parent)
{

}

RegDeviceInfoController *RegDeviceInfoController::instance()
{
    if(m_intance == nullptr){
        m_intance = new RegDeviceInfoController();
    }
    return m_intance;
}

void RegDeviceInfoController::initRegDeviceInfoController()
{

}

void RegDeviceInfoController::onCurrentActivityChanged()
{
    LOG << "[RegDeviceInfoController]";
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_CHANGE_INFO){
        // Handle when currentExcuteStep = E_EXCUTE_CHANGE_INFO
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN ||
           APP_MAIN->getCurrentActivity() == NONE_SCREEN)
        {
            LOG << "Reqest to go to XGame application";
            ADBCommand::requestShowApp(XGAME_PKG,XGAME_ACTIVITYMAIN);
        }
        else if(APP_MAIN->getCurrentActivity() == XGAME_SCREEN){
            if(ADBCommand::findAndClick(AUTO_CHANGE_ICON)){
                delay(8000);
                // reboot device]
                emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),0);
            }else{
                ADBCommand::goHomeScreen();
            }
        }else {
            LOG << "Don't handle with screen: " << APP_MAIN->getCurrentActivity();
        }
    }
}
