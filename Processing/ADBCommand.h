#ifndef ADBCOMMAND_H
#define ADBCOMMAND_H

#include <QObject>
#include <QDir>
#include "AppDefines.h"
#include <QProcess>
#include "Processing/ImageProcessing.h"

class ADBCommand : public QObject
{
    Q_OBJECT

public:

    static QString screenShot(QString fileName = "screen.png", QString path = QDir::currentPath());
    static void tapScreen(QPoint point);
    static void swipeScreen(QPoint sourcePoint, QPoint desPoint);
    static bool requestShowApp(QString packageName, QString activity);
    static bool goHomeScreen();
    static bool requestShowAppDirectly(QString activity);
    static bool enterText(QString text);
    static bool pressTap();
    static bool rebootDevice();
    static bool checkConnection();
    static bool customCommand(QString cmd);
    static QString currentActivity();
    static void killSpecificApp(QString packageName);
    static bool findAndClick(QString iconPath);
    static void wakeUpScreen();
};

#endif // ADBCOMMAND_H
