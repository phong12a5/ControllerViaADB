#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTest>
#include "AppMain.h"
#include "AppModel.h"

int main(int argc, char *argv[])
{
    LOG << "STARTING ....";
    LOG << "CURRENT DIR: " << QDir::currentPath();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    AppMain::instance()->initApplication();
    engine.rootContext()->setContextProperty("AppModel",AppModel::instance());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()){
        LOG << "rootObject is NULL";
    }

    return app.exec();
}

