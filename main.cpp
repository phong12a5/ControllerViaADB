#include <QGuiApplication>
#include <QTest>
#include "AppMain.h"

int main(int argc, char *argv[])
{
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();
    QCoreApplication app(argc, argv);

//    ADBCommand::screenShot("addPicuteProfile.png");
    AppMain::instance()->initApplication();
    AppMain::instance()->startProgram();

    return app.exec();
}

