#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>
#include <QThread>
#include "Processing/CheckCurrSrcThread.h"

class ThreadController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadController(QObject *parent = nullptr);
    ~ThreadController();

private:
    QThread m_checkCurSrcThread;
    CheckCurrSrcThread* updateScreenWorker;

signals:
    void operate(const QString &);

public slots:
};

#endif // THREADCONTROLLER_H
