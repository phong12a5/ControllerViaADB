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
#include "AppModel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>

class AppMain : public QObject
{
    Q_OBJECT

private:
    explicit AppMain(QObject *parent = nullptr);

public:
    static AppMain *instance();

private:
    void wipeData();
    void killCurrentApp();
    QJsonDocument loadJson(QString fileName);
    void saveJson(QJsonDocument document, QString fileName);

public:
    void initApplication();
    void restartProgram();

    // Property
    QString getCurrentActivity();
    void setCurrentActivity(QString _activity);

    QString getCurrentPackage();
    void setCurrentPackage(QString _package);

    AppEnums::E_EXCUTE_STEPS currentExcuteStep();
    void setCurrentExcuteStep(AppEnums::E_EXCUTE_STEPS step);

private:
    static AppMain* m_instance;

private:
    QString m_currentActivity;
    QString m_currentPackage;
    QTimer m_updateCurrActTimer;
    AppEnums::E_EXCUTE_STEPS m_currentExcuteStep;

signals:
    void currentActivityChanged();
    void processFinished(int stepId, int exitCode);

public slots:
    void onUpdateCurrentActivity();
    void onProcessFinished(int currentStep, int exitCode);
    void startProgram(QString tokenID);
    void closeProgram(QString tokenID);
    void loadConfig();
    void saveConfig();
};

#endif // APPMAIN_H
