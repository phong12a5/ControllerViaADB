#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include "AppDefines.h"
#include <QQmlContext>
#include <QQuickView>
#include "AppEnums.h"
#include "Controller/RegMailController.h"
#include "Controller/RegDeviceInfoController.h"
#include "Controller/RegFBController.h"
#include "Processing/ADBCommand.h"

class AppMain : public QObject
{
    Q_OBJECT

private:
    explicit AppMain(QObject *parent = nullptr);

public:
    static AppMain *instance();

public:
    void initApplication();
    void startProgram();

    // Property
    QString getCurrentActivity();
    void setCurrentActivity(QString _activity);

    AppEnums::E_EXCUTE_STEPS currentExcuteStep();
    void setCurrentExcuteStep(AppEnums::E_EXCUTE_STEPS step);

private:
    static AppMain* m_instance;

private:
    QString m_currentActivity;
    QTimer m_updateCurrActTimer;
    AppEnums::E_EXCUTE_STEPS m_currentExcuteStep;

signals:
    void currentActivityChanged();
    void processFinished(int stepId, int exitCode);

public slots:
    void onUpdateCurrentActivity();
    void onProcessFinished(int currentStep, int exitCode);
};

#endif // APPMAIN_H
