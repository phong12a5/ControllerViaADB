#ifndef HTTPREQUESTCONTROLLER_H
#define HTTPREQUESTCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include <QTimer>
#include <QBuffer>
#include <QHttpPart>

class HttpRequestController : public QObject
{
    Q_OBJECT
private:
    explicit HttpRequestController(QObject *parent = nullptr);

public:
    void sendHttpRequest(QString uploadUrl, QString photoPath, EMAI_INFOR& _regInfo);

public:
    static HttpRequestController* instance();
    ~HttpRequestController();
private:
    static HttpRequestController* m_instance;
    QNetworkAccessManager *manager;
    EMAI_INFOR m_regInfo;

signals:

public slots:
    void requestFinished(QNetworkReply* reply);
};

#endif // HTTPREQUESTCONTROLLER_H
