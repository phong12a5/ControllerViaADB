#include "AppMain.h"

#define APP_MODEL           AppModel::instance()
#define REG_MAIL_CTR        RegMailController::instance()
#define REG_DEVICE_INFO_CTR RegDeviceInfoController::instance()
#define REG_FBACC_CTR       RegFBController::instance()

AppMain* AppMain::m_instance = nullptr;

AppMain::AppMain(QObject *parent) : QObject(parent)
{
    m_currentActivity = QString("---");
    m_updateCurrActTimer.setInterval(1000);
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

void AppMain::killCurrentApp()
{
    ADBCommand::killSpecificApp(this->getCurrentPackage());
}

void AppMain::loadConfig()
{
    LOG << "[AppMain]";
    if(!QFile(QDir::currentPath() + "/" + CONFIG_FILE_NAME).exists()){
        this->saveConfig();
    }else{
        QJsonObject config = this->loadJson(CONFIG_FILE_NAME).object();
        APP_MODEL->setSaveToLocal(config[SAVE_LOCAL_FIELD].toBool());
        APP_MODEL->setSaveToServer(config[SAVE_SERVER_FIELD].toBool());
        APP_MODEL->setUseKeyboard(config[USE_KEYBOARD_FIELD].toBool());
        APP_MODEL->setRegFacebookOption(config[REG_FAEBOOK_FIELD].toBool());
        APP_MODEL->setRecoveryEmail(config[RECOVERY_EMAIL_FIELD].toBool());
        APP_MODEL->setNameLang(config[NAME_LANG_FIELD].toString());
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
    config[REG_FAEBOOK_FIELD] = APP_MODEL->regFacebookOption();
    config[RECOVERY_EMAIL_FIELD] = APP_MODEL->recoveryEmail();
    config[NAME_LANG_FIELD] = APP_MODEL->nameLang();
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
    this->loadConfig();
    REG_DEVICE_INFO_CTR->initRegDeviceInfoController();
    REG_MAIL_CTR->initRegMailController();
    REG_FBACC_CTR->initRegFBController();

    QObject::connect(&m_updateCurrActTimer, SIGNAL(timeout()), this, SLOT(onUpdateCurrentActivity()));
    QObject::connect(this, SIGNAL(processFinished(int,int)), this, SLOT(onProcessFinished(int,int)));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_DEVICE_INFO_CTR,   SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_MAIL_CTR,          SLOT(onCurrentActivityChanged()));
    QObject::connect(this, SIGNAL(currentActivityChanged()), REG_FBACC_CTR,         SLOT(onCurrentActivityChanged()));
    QObject::connect(APP_MODEL, SIGNAL(signalStartProgram(QString)), this, SLOT(startProgram(QString)));
    QObject::connect(APP_MODEL, SIGNAL(signalCloseProgram(QString)), this, SLOT(closeProgram(QString)));
    QObject::connect(APP_MODEL, SIGNAL(signalSaveSettingConfig()), this, SLOT(saveConfig()));
}

void AppMain::startProgram(QString tokenID)
{
    LOG << "[AppMain] " << tokenID;
    this->restartProgram();
//    m_updateCurrActTimer.start();
    LOG << "Created new checking screen thread";
    emit screenController.operate("Start new thread");
}

void AppMain::closeProgram(QString tokenID)
{
    LOG << "AppMain" << tokenID;
    QCoreApplication::quit();
}

void AppMain::restartProgram()
{
    LOG << "AppMain";
    REG_MAIL_CTR->setUserInforToReg();
    this->wipeData();
    if(this->getCurrentActivity() == HOME_SCREEN){
        emit this-> currentActivityChanged();
    }else{
        ADBCommand::goHomeScreen();
    }
}

QString AppMain::getCurrentActivity()
{
    return m_currentActivity;
}

void AppMain::setCurrentActivity(QString _activity)
{
    if(m_currentActivity != _activity){
        LOG << "[AppMain]" << _activity;
        if(_activity == UNKNOW_SCREEN){
            // Do nothing
        }else{
            QMutex mutex;
            mutex.lock();
            m_currentActivity = _activity;
            mutex.unlock();
            this->setCurrentPackage(m_currentActivity.split("/").at(0));
            emit currentActivityChanged();
        }
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
//    this->setCurrentActivity(ADBCommand::currentActivity());
}

void AppMain::onProcessFinished(int currentStep, int exitCode)
{
    LOG << "[AppMain]" << "currentStep: " << (currentStep == 0? "CHANGE DEVICE" : (currentStep == 1? "REG GMAIL" : "REG FACEBOOK")) << " --- exitCode: " << exitCode;
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
            if(APP_MODEL->regFacebookOption()){
                this->setCurrentExcuteStep(AppEnums::E_EXCUTE_REG_FACBOOK);
                if(this->getCurrentActivity() == HOME_SCREEN){
                    emit this-> currentActivityChanged();
                }else{
                    ADBCommand::goHomeScreen();
                }
            }else{
                REG_MAIL_CTR->saveEmailToOutput();
                this->setCurrentExcuteStep(AppEnums::E_EXCUTE_CHANGE_INFO);
                this->restartProgram();
            }
        }else if(currentStep == AppEnums::E_EXCUTE_REG_FACBOOK){
            REG_MAIL_CTR->saveEmailToOutput();
            LOG << "[AppMain]" << "Process completed! -> Restart process";
            this->setCurrentExcuteStep(AppEnums::E_EXCUTE_CHANGE_INFO);
            this->restartProgram();
        }
    }
}
