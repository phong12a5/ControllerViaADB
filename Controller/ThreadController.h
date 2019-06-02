#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>
#include <QThread>
#include "Processing/CheckCurrSrcThread.h"
#include "Base/RegControllerBase.h"

class ThreadController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadController(QObject *parent = nullptr);
    ~ThreadController();

private:
    QThread m_checkScreenThread;
    QThread m_regDeviceInfoThread;
    QThread m_regGmailThread;
    QThread m_regFacebookThread;

    CheckCurrSrcThread checkScreenWorker;

public:
    void startNewThreads();

signals:
    void operate(const QString &);

public slots:
};

#endif // THREADCONTROLLER_H
