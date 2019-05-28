#include "AppMain.h"

#define MODEL Model::instance()
#define REG_MAIL_CTR        RegMailController::instance()
#define REG_DEVICE_INFO_CTR RegDeviceInfoController::instance()
#define REG_FBACC_CTR       RegFBController::instance()

AppMain* AppMain::m_instance = nullptr;

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_currentActivity = QString("---");
    m_updateCurrActTimer.setInterval(200);
    m_updateCurrActTimer.setSingleShot(false);
    m_currentExcuteStep = AppEnums::E_EXCUTE_CHANGE_INFO;
}

AppMain *AppMain::instance()
{
    if(m_instance == nullptr){
        m_instance = new AppMain();
    }
    return m_instance;
}

void AppMain::initApplication()
{
    LOG << "[AppMain]";
    REG_DEVICE_INFO_CTR->initRegDeviceInfoController();
    REG_MAIL_CTR->initRegMailController();
    REG_FBACC_CTR->initRegFBController();

    QObject::connect(&m_updateCurrActTimer, SIGNAL(timeout()), this, SLOT(onUpdateCurrentActivity()));
    QObject::connect(this, SIGNAL(processFinished(int,int)), this, SLOT(onProcessFinished(int,int)));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_DEVICE_INFO_CTR,   SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_MAIL_CTR,          SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_FBACC_CTR,         SLOT(onCurrentActivityChanged()));
}

void AppMain::startProgram()
{
    LOG << "[AppMain]";
    this->restartProgram();
    m_updateCurrActTimer.start();
}

void AppMain::restartProgram()
{
    ADBCommand::killSpecificApp(SETTING_PKG);
//    ADBCommand::killSpecificApp(XGAME_PKG);
    ADBCommand::killSpecificApp(FBLITE_PKG);

    ADBCommand::clearCacheOfPackage(FBLITE_PKG);
    ADBCommand::goHomeScreen();
}

QString AppMain::getCurrentActivity()
{
    return m_currentActivity;
}

void AppMain::setCurrentActivity(QString _activity)
{
    if(m_currentActivity != _activity){
        LOG << "[AppMain]" << _activity;
        m_currentActivity = _activity;
        this->setCurrentPackage(m_currentActivity.split("/").at(0));
        emit currentActivityChanged();
    }
}

QString AppMain::getCurrentPackage()
{
    return m_currentPackage;
}

void AppMain::setCurrentPackage(QString _package)
{
    LOG << "[AppMain]" << _package;
    if(m_currentPackage != _package){
        m_currentPackage = _package;
    }
}

AppEnums::E_EXCUTE_STEPS AppMain::currentExcuteStep()
{
    return m_currentExcuteStep;
}

void AppMain::setCurrentExcuteStep(AppEnums::E_EXCUTE_STEPS step)
{
    if(m_currentExcuteStep != step){
        LOG << "[AppMain]" << step;
        m_currentExcuteStep = step;
    }
}

void AppMain::onUpdateCurrentActivity()
{
    this->setCurrentActivity(ADBCommand::currentActivity());
}

void AppMain::onProcessFinished(int currentStep, int exitCode)
{
    LOG << "[AppMain]" << "currentStep: " << currentStep << " --- exitCode: " << exitCode;
    if(exitCode == 1){
        LOG << "[AppMain]" << "Process incompleted! -> Restart process";
        this->setCurrentExcuteStep(AppEnums::E_EXCUTE_CHANGE_INFO);
        this->restartProgram();
    }else if(exitCode == 0 ){
        if(currentStep == AppEnums::E_EXCUTE_CHANGE_INFO){
            this->setCurrentExcuteStep(AppEnums::E_EXCUTE_REG_GMAIL);
            LOG << "[AppMain]" << "Change infor device completed -> Reboot device!!!";
            ADBCommand::rebootDevice();
        }else if(currentStep == AppEnums::E_EXCUTE_REG_GMAIL){
            REG_FBACC_CTR->setUserInfo(REG_MAIL_CTR->getEmailInfor());
            LOG << "[AppMain]" << "Reg gmail completed! -> Start reg facebook";
            this->setCurrentExcuteStep(AppEnums::E_EXCUTE_REG_FACBOOK);
            ADBCommand::goHomeScreen();
        }else if(currentStep == AppEnums::E_EXCUTE_REG_FACBOOK){
            REG_MAIL_CTR->saveEmailToOutput();
            REG_MAIL_CTR->setUserInforToReg();
            LOG << "[AppMain]" << "Process completed! -> Restart process";
            this->setCurrentExcuteStep(AppEnums::E_EXCUTE_CHANGE_INFO);
            this->restartProgram();
        }
    }
}
