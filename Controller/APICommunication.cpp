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

QString APICommunication::sendCaptcherScreen(QString screenPath)
{
    LOG << "screenPath: " << screenPath;

    QString captchaImg = ImageProcessing::extractCaptchaImage(screenPath);
    delay(1000);
    LOG << "captchaImg: " << captchaImg;
    if(captchaImg != QString("")){
        return HttpRequestController::instance()->sendHttpRequest(QString("http://poster.de-captcher.com"),\
                                                           QDir::currentPath() + "/captcha.png");
    }else {
        return QString("");
    }
}
