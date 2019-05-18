#include "AppMain.h"

#define MODEL Model::instance()
#define REG_MAIL_CTR        RegMailController::instance()
#define REG_DEVICE_INFO_CTR RegDeviceInfoController::instance()
#define REG_FBACC_CTR       RegFBController::instance()

AppMain* AppMain::m_instance = nullptr;

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_currentActivity = QString("/0");
    m_updateCurrActTimer.setInterval(200);
    m_updateCurrActTimer.setSingleShot(false);
    m_currentExcuteStep = AppEnums::E_EXCUTE_REG_GMAIL;
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
    LOG;
    REG_DEVICE_INFO_CTR->initRegDeviceInfoController();
    REG_MAIL_CTR->initRegMailController();
    REG_FBACC_CTR->initRegFBController();

    QObject::connect(&m_updateCurrActTimer, SIGNAL(timeout()), this, SLOT(onUpdateCurrentActivity()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_DEVICE_INFO_CTR,   SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_MAIL_CTR,          SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_FBACC_CTR,         SLOT(onCurrentActivityChanged()));
}

void AppMain::startProgram()
{
    LOG;
    ADBCommand::goHomeScreen();
    m_updateCurrActTimer.start();
}

QString AppMain::getCurrentActivity()
{
    return m_currentActivity;
}

void AppMain::setCurrentActivity(QString _activity)
{
    if(m_currentActivity != _activity){
        LOG << _activity;
        m_currentActivity = _activity;
        emit currentActivityChanged();
    }
}

AppEnums::E_EXCUTE_STEPS AppMain::currentExcuteStep()
{
    return m_currentExcuteStep;
}

void AppMain::setCurrentExcuteStep(AppEnums::E_EXCUTE_STEPS step)
{
    if(m_currentExcuteStep != step){
        LOG << step;
        m_currentExcuteStep = step;
    }
}

void AppMain::onUpdateCurrentActivity()
{
    this->setCurrentActivity(ADBCommand::currentActivity());
}
