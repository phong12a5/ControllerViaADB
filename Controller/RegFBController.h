#ifndef REGFBCONTROLLER_H
#define REGFBCONTROLLER_H

#include <QObject>
#include "AppDefines.h"
#include "AppEnums.h"
#include "Processing/ADBCommand.h"
#include "Processing/ImageProcessing.h"
#include <QTimer>

class RegFBController : public QObject
{
    Q_OBJECT
private:
    explicit RegFBController(QObject *parent = nullptr);

public:
    static RegFBController* instance();

    void initRegFBController();
    EMAI_INFOR &getUserInfo();
    void setUserInfo(EMAI_INFOR userInfor);
    void saveAccInforToOutput();

private:
    void clearCacheFBLite();

    int currentScreen() const;
    void setCurrentScreen(const int screenID);
    bool isCurrentScreen(int screenID) const;
    int findCurrentScreen() const;
    int getGenderRandomly() const;
private:
    static RegFBController* m_intance;

    QTimer m_checkScreenTimer;
    int m_currentScreenID;
    EMAI_INFOR m_userInfo;
signals:
    void currentScreenChange();

public slots:
    void onCurrentActivityChanged();
    void onCheckCurrentScreen();
    void onUpdateAction();
};

#endif // REGFBCONTROLLER_H
