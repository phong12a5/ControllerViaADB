#include "RegFBController.h"
#include "AppMain.h"

#define APP_MAIN        AppMain::instance()

RegFBController* RegFBController::m_intance = nullptr;

RegFBController::RegFBController(QObject *parent) : QObject(parent)
{
    m_currentScreenID = -1;
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
    m_checkScreenTimer.setInterval(100);
    m_checkScreenTimer.setSingleShot(false);

    connect(&m_checkScreenTimer,SIGNAL(timeout()),this,SLOT(onCheckCurrentScreen()));
    connect(this,SIGNAL(currentScreenChange()),this,SLOT(onUpdateAction()));
}

void RegFBController::clearCacheFBLite()
{
    LOG;
    this->setCurrentScreen(-1);
    ADBCommand::clearCacheOfPackage(FBLITE_PKG);
}

EMAI_INFOR &RegFBController::getUserInfo()
{
    return m_userInfo;
}

void RegFBController::setUserInfo(EMAI_INFOR userInfor)
{
    m_userInfo = userInfor;
}

void RegFBController::saveAccInforToOutput()
{
    LOG << getUserInfo().userName;
}

int RegFBController::currentScreen() const
{
    return m_currentScreenID;
}

void RegFBController::setCurrentScreen(const int screenID)
{
    if(m_currentScreenID != screenID){
        LOG << screenID;
        m_currentScreenID = screenID;
        emit currentScreenChange();
    }
}

bool RegFBController::isCurrentScreen(int screenID) const
{
    bool retVal = false;
    switch (screenID) {
        case AppEnums::E_FBLITE_SCREEN_ID_LOGIN:
        retVal = ADBCommand::isOnScreen(CREATE_NEW_FBACC_ICON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB:
        retVal = ADBCommand::isOnScreen(JOIN_FB_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME:
        retVal = ADBCommand::isOnScreen(WHAT_YOUR_NAME_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        retVal = ADBCommand::isOnScreen(ENTER_MOBILE_NUM_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS:
        retVal = ADBCommand::isOnScreen(ENTER_YOUR_EMAIL);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        retVal = ADBCommand::isOnScreen(WHAT_YOUR_BIRTHDAY);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER:
        retVal = ADBCommand::isOnScreen(WHAT_YOUR_GENDER);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD:
        retVal = ADBCommand::isOnScreen(CREATE_PASS_SCREEN);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO:
        retVal = ADBCommand::isOnScreen(SAVE_LOGIN_TEXT);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE:
        retVal = ADBCommand::isOnScreen(ADD_A_PICTURE);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS:
        retVal = ADBCommand::isOnScreen(TURN_ON_FIND_FRIEND);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_NEW_FEEDS:
        retVal = ADBCommand::isOnScreen(PROFILE_ICON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_CHECK_POINT:
        retVal = ADBCommand::isOnScreen(CHECK_POINT_SCREEN);
        break;
    }

    LOG << "screenID: " << screenID << " --- reval:" << retVal;

    return retVal;
}

int RegFBController::findCurrentScreen() const
{
    LOG;
    if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_LOGIN))                     return AppEnums::E_FBLITE_SCREEN_ID_LOGIN;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB))              return AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME))           return AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM))     return AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS))  return AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY))       return AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER))         return AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD))       return AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO))      return AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL))        return AppEnums::E_FBLITE_SCREEN_ID_CONFIRM_EMAIL;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE))      return AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS))         return AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_NEW_FEEDS))            return AppEnums::E_FBLITE_SCREEN_ID_NEW_FEEDS;
    else if(isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_CHECK_POINT))          return AppEnums::E_FBLITE_SCREEN_ID_CHECK_POINT;
    else return -1;
}

int RegFBController::getGenderRandomly() const
{
    return rand() %2 + 0;
}

void RegFBController::pressKeyBoard(int number)
{
    if(number <0){
        LOG << "Invalid number: " << number;
        return;
    }
    QPoint keyboard = ADBCommand::findAnImageOnScreen(KEYBOARD);

    if(!keyboard.isNull()){
        QList<int> listNumber;
        while (number) {
            int temp = number%10;
            listNumber.prepend(temp);
            number /= 10;
        }
        while (!listNumber.isEmpty()) {
            switch (listNumber.takeFirst()) {
            case 1:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 450,keyboard.y() - 58));
                break;
            case 2:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 270,keyboard.y() - 58));
                break;
            case 3:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 90,keyboard.y() - 58));
                break;
            case 4:
                ADBCommand::tapScreen(QPoint(keyboard.x() + 90,keyboard.y() - 58));
                break;
            case 5:
                ADBCommand::tapScreen(QPoint(keyboard.x() + 270,keyboard.y() - 58));
                break;
            case 6:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 450,keyboard.y() + 58));
                break;
            case 7:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 270,keyboard.y() + 58));
                break;
            case 8:
                ADBCommand::tapScreen(QPoint(keyboard.x() - 90,keyboard.y() + 58));
                break;
            case 9:
                ADBCommand::tapScreen(QPoint(keyboard.x() + 90,keyboard.y() + 58));
                break;
            case 0:
                ADBCommand::tapScreen(QPoint(keyboard.x() + 270,keyboard.y() + 58));
                break;
            default:
                break;
            }
        }
    }
}

BIRTHDAY_STRUCT RegFBController::getRandomBirthday()
{
    BIRTHDAY_STRUCT retVal;
    retVal.day = rand()%28 + 0;
    retVal.month = rand() %12 + 0;
    retVal.year = rand() % 45 + 1960;
    return retVal;
}

void RegFBController::enterBirthDay()
{
    LOG;
    QPoint birthDayField = ADBCommand::findAnImageOnScreen(BIRTH_DAY_FIELD);
    if(!birthDayField.isNull()){
        // CLICK MONTH FIELD
        ADBCommand::tapScreen(QPoint(birthDayField.x() - 110,birthDayField.y()));
        pressKeyBoard(this->getRandomBirthday().month);
        // CLICK DAY FIELD
        ADBCommand::tapScreen(QPoint(birthDayField.x() - 30,birthDayField.y()));
        pressKeyBoard(this->getRandomBirthday().day);
        // CLICK YEAR FIELD
        ADBCommand::tapScreen(QPoint(birthDayField.x() + 80,birthDayField.y()));
        pressKeyBoard(this->getRandomBirthday().year);
    }
}

void RegFBController::onCurrentActivityChanged()
{
    LOG << "[RegFBController]";
    if(APP_MAIN->currentExcuteStep() == AppEnums::E_EXCUTE_REG_FACBOOK){
        // Handle when currentExcuteStep = E_EXCUTE_REG_GMAIL
        if(APP_MAIN->getCurrentActivity() == HOME_SCREEN ||
                APP_MAIN->getCurrentActivity() == NONE_SCREEN)
        {
            this->clearCacheFBLite();
            LOG << "Reqest to go to Facebook Lite application";
            ADBCommand::requestShowApp(FBLITE_PKG,FBLITE_ACTIVITYMAIN);
        }else if(APP_MAIN->getCurrentActivity() == FACEBOOK_LITE_SCREEN){
            m_checkScreenTimer.start();
        }
    }else{
        m_checkScreenTimer.stop();
    }
}

void RegFBController::onCheckCurrentScreen()
{
    LOG;
    switch (this->currentScreen()) {
    case -1:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_LOGIN)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_LOGIN);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_LOGIN:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;

    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE:
        if(this->isCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS)){
            this->setCurrentScreen(AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS);
        }else{
            this->setCurrentScreen(this->findCurrentScreen());
        }
        break;
    default:
        break;
    }
}

void RegFBController::onUpdateAction()
{
    LOG << "current screen: " << this->currentScreen();
    if(APP_MAIN->currentExcuteStep() != AppEnums::E_EXCUTE_REG_FACBOOK)
        return;

    switch (this->currentScreen()) {
        case AppEnums::E_FBLITE_SCREEN_ID_LOGIN:
        ADBCommand::findAndClick(CREATE_NEW_FBACC_ICON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_JOIN_FB:
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_NAME:
        ADBCommand::findAndClick(FIRSTNAME_FIELD);
        ADBCommand::enterText(getUserInfo().firstName);
        ADBCommand::findAndClick(LASTNAME_FIELD);
        ADBCommand::enterText(getUserInfo().lastName);
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_MOBILE_NUM:
        ADBCommand::findAndClick(SIGN_UP_WITH_EMAIL);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_EMAIL_ADDRESS:
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_BIRTHDAY:
        this->enterBirthDay();
        ADBCommand::findAndClick(NEXT_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_GENDER:
        // Do something
    {
        QString icon;
        if(this->getGenderRandomly() == 0){
            icon = FEMALE_BUTTON;
        }else{
            icon = MALE_BUTTON;
        }
        ADBCommand::findAndClick(icon);
    }
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ENTER_PASSWORD:
        ADBCommand::findAndClick(PASSWORD_FIELD);
        ADBCommand::enterText(getUserInfo().password);
        ADBCommand::findAndClick(SIGN_UP_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_SAVE_LOGIN_INFO:
        ADBCommand::findAndClick(NOT_NOW_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_ADD_PIC_PROFILE:
        ADBCommand::findAndClick(SKIP_BUTTON);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_FIND_FRIENDS:
        ADBCommand::findAndClick(SKIP_FIND_FRIEND);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_NEW_FEEDS:
        emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),0);
        break;
    case AppEnums::E_FBLITE_SCREEN_ID_CHECK_POINT:
        emit APP_MAIN->processFinished(APP_MAIN->currentExcuteStep(),1);
        break;
    }
}
