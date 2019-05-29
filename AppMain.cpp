#include "AppMain.h"

#define APP_MODEL           AppModel::instance()
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

void AppMain::wipeData()
{
    LOG << "[AppMain]";
    for(int i = 0; i < APP_MODEL->appDataList().length(); i++){
        APP_DATA* app = dynamic_cast<APP_DATA*>(APP_MODEL->appDataList().at(i));
        if(app != nullptr && app->checkedState()){
            ADBCommand::clearCacheOfPackage(app->packageName());
        }else{
            // Do nothing
        }
    }
}

void AppMain::loadConfig()
{
    LOG << "[AppMain]";
    QJsonObject config = this->loadJson(CONFIG_FILE_NAME).object();
    APP_MODEL->setSaveToLocal(config[SAVE_LOCAL_FIELD].toBool());
    APP_MODEL->setSaveToServer(config[SAVE_SERVER_FIELD].toBool());
    APP_MODEL->setUseKeyboard(config[USE_KEYBOARD_FIELD].toBool());
    QJsonObject appDataObj = config[APP_DATA_FIELD].toObject();
    if(!appDataObj.isEmpty()){
        QJsonObject appData;
        for(int i = 0; i < APP_MODEL->appDataList().length(); i++){
            APP_DATA* app = dynamic_cast<APP_DATA*>(APP_MODEL->appDataList().at(i));
            QString packageName = app->packageName();
            bool state = appDataObj[packageName].toBool();
            app->setCheckedState(state);
        }
    }else{
        LOG << "[AppMain]" << " appDataObj is empty";
    }
}

void AppMain::saveConfig()
{
    LOG << "[AppMain]";
    QJsonObject config;
    QJsonObject appData;

    for(int i = 0; i < APP_MODEL->appDataList().length(); i++){
        APP_DATA* app = dynamic_cast<APP_DATA*>(APP_MODEL->appDataList().at(i));
        QString packageName = app->packageName();
        appData[packageName] = app->checkedState();
    }
    config[SAVE_LOCAL_FIELD] = APP_MODEL->saveToLocal();
    config[SAVE_SERVER_FIELD] = APP_MODEL->saveToServer();
    config[USE_KEYBOARD_FIELD] = APP_MODEL->useKeyboard();
    config[APP_DATA_FIELD] = appData;

    this->saveJson(QJsonDocument(config),CONFIG_FILE_NAME);
}

QJsonDocument AppMain::loadJson(QString fileName)
{
    LOG << "[AppMain]";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void AppMain::saveJson(QJsonDocument document, QString fileName)
{
    LOG << "[AppMain]";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

void AppMain::initApplication()
{
    LOG << "[AppMain]";

    REG_DEVICE_INFO_CTR->initRegDeviceInfoController();
    REG_MAIL_CTR->initRegMailController();
    REG_FBACC_CTR->initRegFBController();
    this->loadConfig();

    QObject::connect(&m_updateCurrActTimer, SIGNAL(timeout()), this, SLOT(onUpdateCurrentActivity()));
    QObject::connect(this, SIGNAL(processFinished(int,int)), this, SLOT(onProcessFinished(int,int)));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_DEVICE_INFO_CTR,   SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_MAIL_CTR,          SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_FBACC_CTR,         SLOT(onCurrentActivityChanged()));
    QObject::connect(APP_MODEL, SIGNAL(signalStartProgram()), this, SLOT(startProgram()));
    QObject::connect(APP_MODEL, SIGNAL(signalCloseProgram()), this, SLOT(closeProgram()));
    QObject::connect(APP_MODEL, SIGNAL(signalSaveSettingConfig()), this, SLOT(saveConfig()));
}

void AppMain::startProgram()
{
    LOG << "[AppMain]";
    this->restartProgram();
    m_updateCurrActTimer.start();
}

void AppMain::closeProgram()
{
    LOG << "AppMain";
}

void AppMain::restartProgram()
{
    LOG << "AppMain";
    this->wipeData();
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
