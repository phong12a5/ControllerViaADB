#include "RegFBController.h"

RegFBController* RegFBController::m_intance = nullptr;

RegFBController::RegFBController(QObject *parent) : QObject(parent)
{

}

RegFBController *RegFBController::instance()
{
    if(m_intance == nullptr){
        m_intance = new RegFBController();
    }
    return m_intance;
}

void RegFBController::initRegFBController()
{
    LOG;
}

void RegFBController::onCurrentActivityChanged()
{
    LOG << "[RegFBController]";
}
