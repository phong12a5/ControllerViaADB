#include "HttpRequestController.h"

HttpRequestController* HttpRequestController::m_instance = nullptr;

HttpRequestController::HttpRequestController(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(requestFinished(QNetworkReply*)));
}

void HttpRequestController::sendHttpRequest(QString uploadUrl, QString photoPath)
{
    LOG << "uploadUrl: " << uploadUrl;
    LOG << "imgPath: " << photoPath;

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart functionPart;
    functionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"function\""));
    functionPart.setBody("picture2");

    QHttpPart usernamePart;
    usernamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    usernamePart.setBody("thanhnambeo");

    QHttpPart passwordPart;
    passwordPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"password\""));
    passwordPart.setBody("4affhvpna");

    QHttpPart picTypepart;
    picTypepart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pict_type\""));
    picTypepart.setBody("0");

    QHttpPart destinationFilePart;
    destinationFilePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    destinationFilePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pict\""));

    QFile *file = new QFile(photoPath);
    file->open(QIODevice::ReadOnly);
    destinationFilePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(functionPart);
    multiPart->append(usernamePart);
    multiPart->append(passwordPart);
    multiPart->append(picTypepart);
    multiPart->append(destinationFilePart);


    const QNetworkRequest request(uploadUrl);

    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);
}

HttpRequestController *HttpRequestController::instance()
{
    if(m_instance == nullptr){
        m_instance = new HttpRequestController();
    }
    return m_instance;
}

HttpRequestController::~HttpRequestController()
{
    LOG;
    delete manager;
}

void HttpRequestController::requestFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        LOG << "ERROR!";
        LOG << reply->errorString();
    }
    else
    {
        QStringList outputList = QString(reply->readAll()).split('|');
        LOG << "outputList: " << outputList;
        if(outputList.length() > 5){
            emit takeCaptcha(outputList.at(5));
        }
        reply->deleteLater();
        manager->clearAccessCache();
    }
}
