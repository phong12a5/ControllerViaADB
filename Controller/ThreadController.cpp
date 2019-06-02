#include "ThreadController.h"

ThreadController::ThreadController(QObject *parent) : QObject(parent)
{
    updateScreenWorker = new CheckCurrSrcThread();
    updateScreenWorker->moveToThread(&m_checkCurSrcThread);
    connect(&m_checkCurSrcThread, &QThread::finished, updateScreenWorker, &QObject::deleteLater);
    connect(this, &ThreadController::operate, updateScreenWorker, &CheckCurrSrcThread::doWork);
    m_checkCurSrcThread.start();
}

ThreadController::~ThreadController()
{
    m_checkCurSrcThread.quit();
    m_checkCurSrcThread.wait();
}
