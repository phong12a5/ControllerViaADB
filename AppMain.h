#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include "AppDefines.h"
#include <QQmlContext>
#include <QQuickView>
#include "AppEnums.h"
#include "Controller/MainController.h"
#include "Processing/ADBCommand.h"

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    void initApplication();
    void startProgram();

private:

private:

signals:
    void startRegGmailProgram();

public slots:
};

#endif // APPMAIN_H
