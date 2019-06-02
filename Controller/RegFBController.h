#ifndef REGFBCONTROLLER_H
#define REGFBCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppEnums.h"
#include "Processing/ADBCommand.h"
#include "Processing/ImageProcessing.h"
#include <QTimer>
#include "AppModel.h"
#include "Base/RegControllerBase.h"

class RegFBController : public RegControllerBase
{
    Q_OBJECT
private:
    explicit RegFBController(QObject *parent = nullptr);

public:
    static RegFBController* instance();

    void initRegFBController();
    EMAI_INFOR &getUserInfo();
    void setUserInfo(EMAI_INFOR userInfor);

private:
    void clearCacheFBLite();

    int currentScreen() const;
    void setCurrentScreen(const int screenID);
    bool isCurrentScreen(int screenID) const;
    int findCurrentScreen() const;
    int getGenderRandomly() const;
    void pressKeyBoard(int number);
    BIRTHDAY_STRUCT getRandomBirthday();
    void inputPassWordByKeyBoard(QString inputText);
public:
    void enterBirthDay();
private:
    static RegFBController* m_intance;

    QTimer m_checkScreenTimer;
    int m_currentScreenID;
    EMAI_INFOR m_userInfo;
signals:
    void currentScreenChange();

public slots:
    void onCurrentActivityChanged() override;
    void onCheckCurrentScreen();
    void onUpdateAction();
};

#endif // REGFBCONTROLLER_H
