#include "ThreadController.h"
#include "AppMain.h"
#include "Base/RegControllerBase.h"
#include "RegDeviceInfoController.h"
#include "RegMailController.h"
#include "RegFBController.h"

#define REG_MAIL_CTR        RegMailController::instance()
#define REG_DEVICE_INFO_CTR RegDeviceInfoController::instance()
#define REG_FBACC_CTR       RegFBController::instance()

ThreadController::ThreadController(QObject *parent) : QObject(parent)
{

}

ThreadController::~ThreadController()
{
    m_checkScreenThread.quit();
    m_regDeviceInfoThread.quit();
    m_regGmailThread.quit();
    m_regFacebookThread.quit();

    m_checkScreenThread.wait();
    m_regDeviceInfoThread.wait();
    m_regGmailThread.wait();
    m_regFacebookThread.wait();
}

void ThreadController::startNewThreads()
{
    LOG << "[ThreadController]";

    checkScreenWorker.moveToThread(&m_checkScreenThread);
    REG_MAIL_CTR->moveToThread(&m_regGmailThread);
    REG_DEVICE_INFO_CTR->moveToThread(&m_regDeviceInfoThread);
    REG_FBACC_CTR->moveToThread(&m_regFacebookThread);

    connect(&m_checkScreenThread, &QThread::finished, &checkScreenWorker, &QObject::deleteLater);
    connect(&m_regDeviceInfoThread, &QThread::finished, REG_DEVICE_INFO_CTR, &QObject::deleteLater);
    connect(&m_regGmailThread, &QThread::finished, REG_MAIL_CTR, &QObject::deleteLater);
    connect(&m_regFacebookThread, &QThread::finished, REG_FBACC_CTR, &QObject::deleteLater);

    connect(this, &ThreadController::operate, &checkScreenWorker, &CheckCurrSrcThread::doWork);
    connect(AppMain::instance(), &AppMain::currentActivityChanged, REG_DEVICE_INFO_CTR, &RegControllerBase::onCurrentActivityChanged);
    connect(AppMain::instance(), &AppMain::currentActivityChanged, REG_MAIL_CTR, &RegControllerBase::onCurrentActivityChanged);
    connect(AppMain::instance(), &AppMain::currentActivityChanged, REG_FBACC_CTR, &RegControllerBase::onCurrentActivityChanged);

    m_checkScreenThread.start();
    m_regDeviceInfoThread.start();
    m_regGmailThread.start();
    m_regFacebookThread.start();
}
