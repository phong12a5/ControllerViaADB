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
    static HttpRequestController* instance();
    ~HttpRequestController();

    QString sendHttpRequest(QString, QString);

private:
    static HttpRequestController* m_instance;
    QNetworkAccessManager *manager;
    QEventLoop eventLoop;

signals:
    void takeCaptcha(QString captcha);

public slots:
};

#endif // HTTPREQUESTCONTROLLER_H
