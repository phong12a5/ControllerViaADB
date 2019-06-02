#include "CheckCurrSrcThread.h"
#include "AppModel.h"
#include "AppMain.h"

#define APP_MODEL   AppModel::instance()
#define APP_MAIN    AppMain::instance()

CheckCurrSrcThread::CheckCurrSrcThread(QObject *parent) : QObject(parent)
{
    m_currentActivity = "";
}

CheckCurrSrcThread::~CheckCurrSrcThread()
{
    LOG;
    m_updateCurrActTimer->stop();
    delete m_updateCurrActTimer;
}

void CheckCurrSrcThread::doWork(const QString &parameter)
{
    QString result;
    LOG << "[CheckCurrSrcThread] " << parameter;
    m_updateCurrActTimer = new QTimer(this);
    m_updateCurrActTimer->setInterval(100);
    m_updateCurrActTimer->setSingleShot(false);
    QObject::connect(m_updateCurrActTimer, SIGNAL(timeout()), this, SLOT(onUpdateCurrentActivity()));
    m_updateCurrActTimer->start();
    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}

void CheckCurrSrcThread::onUpdateCurrentActivity()
{
    QString _currAct = ADBCommand::currentActivity();
    if(m_currentActivity != _currAct){
        APP_MAIN->setCurrentActivity(ADBCommand::currentActivity());
    }
}
