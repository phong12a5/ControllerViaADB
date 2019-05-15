#include "APICommunication.h"

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

void APICommunication::sendCaptchaScreen(QString screenPath)
{
    LOG << "screenPath: " << screenPath;
}
