#include "RegDeviceInfoController.h"
#include "AppMain.h"

#define APP_MAIN AppMain::instance()

RegDeviceInfoController* RegDeviceInfoController::m_intance = nullptr;

RegDeviceInfoController::RegDeviceInfoController(QObject *parent)
{
    Q_UNUSED(parent);
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
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_CHANGE_INFO){
        // Handle when currentExcuteStep = E_EXCUTE_CHANGE_INFO
        LOG << "[RegDeviceInfoController]" << APP_MAIN->getCurrentActivity();
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN)
        {
            LOG << "[RegDeviceInfoController]" << "Reqest to go to XGame application";
            ADBCommand::requestShowApp(XGAME_PKG,XGAME_ACTIVITYMAIN);
        }
        else if(APP_MAIN->getCurrentActivity() == XGAME_SCREEN){
            while(!ADBCommand::findAndClick(AUTO_CHANGE_ICON));
            delay(10000);
            emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),0);
        }else {
            LOG << "[RegDeviceInfoController]" << "Don't handle with screen: " << APP_MAIN->getCurrentActivity();
            ADBCommand::goHomeScreen();
        }
    }
}
