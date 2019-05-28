#include "AppModel.h"

AppModel* AppModel::m_instance = nullptr;

void AppModel::startProgram()
{
    emit signalStartProgram();
}

void AppModel::closeProgram()
{
    emit signalCloseProgram();
}

AppModel::AppModel(QObject *parent) :
    QObject(parent),
    m_saveToLocal(false),
    m_saveToServer(false),
    m_useKeyboard(false)
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
        m_useKeyboard = data;
        emit useKeyboardChanged();
    }
}
