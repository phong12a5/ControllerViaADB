#include <QGuiApplication>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QQuickView>
#include <QProcess>
#include <QTest>
#include "AppMain.h"
#include "Processing/ADBCommand.h"

int main(int argc, char *argv[])
{
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();
    QCoreApplication app(argc, argv);

    AppMain appMain;
    appMain.initApplication();
    appMain.startProgram();

    return app.exec();
}

