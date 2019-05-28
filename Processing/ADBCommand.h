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
    static void tapScreen(QPoint point, bool noDelay = false);
    static void swipeScreen(QPoint sourcePoint, QPoint desPoint);
    static bool requestShowApp(QString packageName, QString activity);
    static bool goHomeScreen();
    static void pressBack();
    static bool requestShowAppDirectly(QString activity);
    static bool enterText(QString text);
    static bool pressTap();
    static bool rebootDevice();
    static bool checkConnection();
    static bool customCommand(QString cmd);
    static QString currentActivity();
    static void killSpecificApp(QString packageName);
    static bool isOnScreen(QString iconPath);
    static QPoint findAnImageOnScreen(QString iconPath);
    static bool findAndClick(QString iconPath);
    static void wakeUpScreen();
    static void clearCacheOfPackage(QString packagName);
};

#endif // ADBCOMMAND_H
