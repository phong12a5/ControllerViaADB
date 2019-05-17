#ifndef APICOMMUNICATION_H
#define APICOMMUNICATION_H

#include <QObject>
#include "AppDefines.h"
#include "Processing/HttpRequestController.h"

class APICommunication : public QObject
{
    Q_OBJECT
private:
    explicit APICommunication(QObject *parent = nullptr);

public:
    static APICommunication *instance();

    QString sendCaptcherScreen(QString screenPath);

private:
    static APICommunication* m_instance;
signals:

public slots:
};

#endif // APICOMMUNICATION_H
