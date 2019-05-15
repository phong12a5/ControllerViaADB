#ifndef ADBCOMMAND_H
#define ADBCOMMAND_H

#include <QObject>
#include <QDir>
#include "AppDefines.h"
#include <QProcess>

class ADBCommand : public QObject
{
    Q_OBJECT
private:
    explicit ADBCommand(QObject *parent = nullptr);

public:
    static ADBCommand* instance();

    QString screenShot(QString fileName = "screen.png", QString path = QDir::currentPath());
    void tapScreen(QPoint point);
    void swipeScreen(QPoint sourcePoint, QPoint desPoint);
    bool requestShowApp(QString packageName, QString activity);
    bool goHomeScreen();
    bool requestShowAppDirectly(QString activity);
    bool enterText(QString text);
    bool pressTap();
    bool rebootDevice();
    bool checkConnection();
    bool customCommand(QString cmd);
    QString currentActivity();
    void killSpecificApp(QString packageName);
private:
    static ADBCommand* m_instance;

signals:

public slots:
};

#endif // ADBCOMMAND_H
