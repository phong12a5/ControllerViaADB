#include "AppModel.h"

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) :
    QObject(parent),
    m_saveToLocal(false),
    m_saveToServer(false),
    m_useKeyboard(false),
    m_regFacebookOption(false),
    m_recoveryEmail(false),
    m_nameLang("Vietnamese")
{
    m_appDataList.clear();
    for (int i = 0; i < PACKAGE_LIST.length(); i++) {
        m_appDataList.append(new APP_DATA(PACKAGE_LIST.at(i)));
    }
}

AppModel *AppModel::instance()
{
    if(m_instance == nullptr){
        m_instance = new AppModel();
    }
    return m_instance;
}

void AppModel::startProgram(QString tokenID)
{
    emit signalStartProgram(tokenID);
}

void AppModel::closeProgram(QString tokenID)
{
    emit signalCloseProgram(tokenID);
}

void AppModel::saveSettingConfig()
{
    emit signalSaveSettingConfig();
}

QList<QObject *> AppModel::appDataList()
{
    return m_appDataList;
}

void AppModel::setAppDataList(QList<QObject *> data)
{
    if(m_appDataList != data){
        m_appDataList = data;
        emit appDataListChanged();
    }
}

bool AppModel::saveToLocal() const
{
    return m_saveToLocal;
}

void AppModel::setSaveToLocal(bool data)
{
    if(m_saveToLocal != data){
        LOG << "[AppModel]" << data;
        m_saveToLocal = data;
        emit saveToLocalChanged();
    }
}

bool AppModel::saveToServer() const
{
    return m_saveToServer;
}

void AppModel::setSaveToServer(bool data)
{
    if(m_saveToServer != data){
        LOG << "[AppModel]" << data;
        m_saveToServer = data;
        emit saveToServerChanged();
    }
}

bool AppModel::useKeyboard()
{
    return m_useKeyboard;
}

void AppModel::setUseKeyboard(bool data)
{
    if(m_useKeyboard != data){
        LOG << "[AppModel]" << data;
        m_useKeyboard = data;
        emit useKeyboardChanged();
    }
}

bool AppModel::regFacebookOption() const
{
    return m_regFacebookOption;
}

void AppModel::setRegFacebookOption(bool data)
{
    if(m_regFacebookOption != data){
        m_regFacebookOption = data;
        emit regFacebookOptionChanged();
    }
}

bool AppModel::recoveryEmail() const
{
    return m_recoveryEmail;
}

void AppModel::setRecoveryEmail(bool data)
{
    if(m_recoveryEmail != data){
        m_recoveryEmail = data;
        emit recoveryEmailChanged();
    }
}

QString AppModel::nameLang() const
{
    return m_nameLang;
}

void AppModel::setNameLang(QString data)
{
    if(m_nameLang != data){
        m_nameLang = data;
        emit nameLangChanged();
    }
}
