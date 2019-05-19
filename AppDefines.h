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
       firstName = "";
       lastName = "";
       userName = "";
       password = "";
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


// GOOGLE SETTING icons
#define AUTO_CHANGE_ICON        "/IconImage/autoChangeBtn.png"
#define GOOGLE_ACCOUNT_ICON     "/IconImage/googleAccIcon.png"
#define ADD_NEW_ACC_ICON        "/IconImage/addNewAccIcon.png"
#define NEXT_YOURNAME_ICON      "/IconImage/NextYourNameIcon.png"
#define NOT_NOW_ICON            "/IconImage/notNowIcon.png"
#define ACCEPT_BY_ME_ICON       "/IconImage/acceptByMe.png"

// FACEBOOK LITE icons
#define CREATE_NEW_FBACC_ICON   "/IconImage/createNewAccIcon.png"
#define JOIN_FB_TEXT            "/IconImage/JoinFBText.png"
#define NEXT_BUTTON             "/IconImage/nextBtn.png"
#define WHAT_YOUR_NAME_TEXT     "/IconImage/InputNameScr.png"
#define FIRSTNAME_FIELD         "/IconImage/FirstNameField.png"
#define LASTNAME_FIELD          "/IconImage/LastNameField.png"
#define ENTER_MOBILE_NUM_TEXT   "/IconImage/enterMobileNumberScr.png"
#define WHAT_YOUR_BIRTHDAY      "/IconImage/whatYourBirthdayScr.png"
#define WHAT_YOUR_GENDER        "/IconImage/whatYourGender.png"
#define FEMALE_BUTTON           "/IconImage/femaleIcon.png"
#define MALE_BUTTON             "/IconImage/maleIcon.png"
#define CREATE_PASS_SCREEN      "/IconImage/createPassWord.png"
#define PASSWORD_FIELD          "/IconImage/passwordField.png"
#define SIGN_UP_BUTTON          "/IconImage/signUpBtn.png"
#define SAVE_LOGIN_TEXT         "/IconImage/saveLoginInfo.png"
#define NOT_NOW_BUTTON          "/IconImage/notNowBtn.png"
#define ADD_YOUR_EMAIL          "/IconImage/addYourEmail.png"
#define GAMIL_RADIO_BTN         "/IconImage/gmailRadioButton.png"
#define YES_BTN                 "/IconImage/yesButton.png"
#define CONFIRM_EMAIL           "/IconImage/confirmEmail.png"

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

// FACEBOOK LITE activity
#define FACEBOOK_LITE_SCREEN    "com.facebook.lite/.MainActivity"

// UNKNOW_SCREEN
#define UNKNOW_SCREEN           "UNKNOW_SCREEN"


#endif // APPDEFINES_H

