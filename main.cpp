#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTest>
#include "AppMain.h"
#include "AppModel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>


QJsonDocument loadJson(QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}

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

//    QVariantMap map;
//    map.insert("integer", 1);
//    map.insert("double", 2.34);
//    map.insert("bool", QVariant(true));
//    map.insert("string", "word");
//    QJsonObject object = QJsonObject::fromVariantMap(map);

//    QJsonDocument document;
//    document.setObject(object);

//    saveJson(document,"Phong.JS");

    return app.exec();
}



