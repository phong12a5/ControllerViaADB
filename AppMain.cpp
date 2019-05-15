#include "AppMain.h"

#define MODEL Model::instance()
#define MAIN_CONTROLLER MainController::instance()

AppMain::AppMain(QObject *parent) : QObject(parent)
{

}

void AppMain::initApplication()
{
    LOG;

    // Init Main controller
    MAIN_CONTROLLER->initController();

    // connect signal - slot
    QObject::connect(this, SIGNAL(startRegGmailProgram()), MAIN_CONTROLLER, SLOT(onStartRegGmailProgram()));
}

void AppMain::startProgram()
{
    LOG;
    emit startRegGmailProgram();
}
