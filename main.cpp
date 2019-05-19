#include <QGuiApplication>
#include <QTest>
#include "AppMain.h"
#include "Controller/RegFBController.h"

int main(int argc, char *argv[])
{
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();
    QCoreApplication app(argc, argv);

    AppMain::instance()->initApplication();
    AppMain::instance()->startProgram();

    return app.exec();
}

