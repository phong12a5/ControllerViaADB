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
}

void AppMain::startProgram()
{
    LOG;
    MAIN_CONTROLLER->startRegGmailProgram();
}
