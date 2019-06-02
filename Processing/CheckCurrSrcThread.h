#ifndef CHECKCURRSRCTHREAD_H
#define CHECKCURRSRCTHREAD_H

#include <QObject>
#include <AppDefines.h>
#include <QTimer>
#include "ADBCommand.h"
#include <QThread>

class CheckCurrSrcThread : public QObject
{
    Q_OBJECT
public:
    explicit CheckCurrSrcThread(QObject *parent = nullptr);
    ~CheckCurrSrcThread();

private:
    QTimer* m_updateCurrActTimer;
    QString m_currentActivity;

signals:
    void resultReady(const QString &result);

public slots:
    void doWork(const QString &parameter);
    void onUpdateCurrentActivity();
};

#endif // CHECKCURRSRCTHREAD_H
