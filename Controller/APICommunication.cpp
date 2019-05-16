#include "APICommunication.h"
#include "MainController.h"

APICommunication* APICommunication::m_instance = nullptr;

APICommunication::APICommunication(QObject *parent) : QObject(parent)
{

}

APICommunication *APICommunication::instance()
{
    if(m_instance == nullptr){
        m_instance = new APICommunication();
    }
    return m_instance;
}

void APICommunication::sendCaptcherScreen(QString screenPath)
{
    LOG << "screenPath: " << screenPath;
    HttpRequestController::instance()->sendHttpRequest(QString("http://poster.de-captcher.com"),\
                                                       QDir::currentPath() + "/screen.png", \
                                                       MainController::instance()->getEmailInfor());
}
