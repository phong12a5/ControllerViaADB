#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QTest>

typedef struct email_infor{
    QString firstName;
    QString lastName;
    QString userName;
    QString password;
    QString captcha;

    email_infor(){
       firstName = "Phong";
       lastName = "Dang";
       userName = "PhongDepTrai11889977";
       password = "Canyouhelpme1276$";
       captcha = "";
    }

} EMAI_INFOR;

#define LOG qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "] >>"

#define delay(milescond)    QTest::qSleep(milescond)

#define IMAGE_FOLDER        "/storage/emulated/legacy/DCIM/"
#define FIRST_NAME_FILE     QDir::currentPath()+"/firstname.txt"
#define LAST_NAME_FILE      QDir::currentPath()+"/lastname.txt"
#define OUTPUT_FILE         QDir::currentPath()+"/emailList.txt"

#define SETTING_PKG             "com.android.settings"
#define SETTING_ACTIVITYMAIN    ".Settings"
#define ACCOUNT_SETTING_ACT     "android.settings.ADD_ACCOUNT_SETTINGS"

#define XGAME_PKG               "app.haonam.xgame"
#define XGAME_ACTIVITYMAIN      ".MainActivity"

#define FBLITE_PKG              "com.facebook.lite"
#define FBLITE_ACTIVITYMAIN     ".MainActivity"

#define AUTO_CHANGE_ICON        "/IconImage/autoChangeBtn.png"
#define GOOGLE_ACCOUNT_ICON     "/IconImage/googleAccIcon.png"
#define ADD_NEW_ACC_ICON        "/IconImage/addNewAccIcon.png"
#define NEXT_YOURNAME_ICON      "/IconImage/NextYourNameIcon.png"
#define NOT_NOW_ICON            "/IconImage/notNowIcon.png"
#define ACCEPT_BY_ME_ICON       "/IconImage/acceptByMe.png"

//HOME activities
#define HOME_SCREEN             "com.sonyericsson.home/com.sonymobile.home.HomeActivity"
#define NONE_SCREEN             ""

//GOOGLE SETTING activities
#define ACCOUNT_SETTING_SCREEN  "com.android.settings/.accounts.ChooseAccountActivity"
#define ADD_A_GGACCOUNT_SCREEN  "com.google.android.gsf.login/.AccountIntroUIActivity"
#define INPUT_YOURNAME_SCREEN   "com.google.android.gsf.login/.NameActivity"
#define INPUT_USERNAME_SCREEN   "com.google.android.gsf.login/.UsernameActivity"
#define INPUT_PASSWORD_SCREEN   "com.google.android.gsf.login/.ChoosePasswordActivity"
#define RECOVERY_INTRO_SCREEN   "com.google.android.gsf.login/.RecoveryIntroActivity"
#define GOOGLE_SERVICE_SCREEN   "com.google.android.gsf.login/.GoogleServicesActivity"
#define TERM_SERVICE_SCREEN     "com.google.android.gsf.login/.TermsOfServiceActivity"
#define AUTHENTICATING_SCREEN   "com.google.android.gsf.login/.CaptchaActivity"
#define WIFI_PICKER_SCREEN      "com.android.settings/.wifi.WifiPickerActivity"
#define SYNC_INTRO_SCREEN       "com.google.android.gsf.login/.SyncIntroActivity"
#define PAYMENT_SETTING_SCREEN  "com.android.vending/com.google.android.finsky.billing.promptforfop.SetupWizardPromptForFopActivity"


// XGAME activities
#define XGAME_SCREEN            "app.haonam.xgame/.MainActivity"

#define UNKNOW_SCREEN           "UNKNOW_SCREEN"


#endif // APPDEFINES_H

