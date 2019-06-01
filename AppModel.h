#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include <AppDefines.h>
#include <AppEnums.h>

class APP_DATA : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString packageName READ packageName CONSTANT)
    Q_PROPERTY(bool checkedState READ checkedState WRITE setCheckedState NOTIFY checkedStateChanged)

public:
    explicit APP_DATA(QString packageName):
        m_packageName(packageName)
    {
        m_checkedState = false;
    }

    QString packageName(){ return m_packageName;}
    bool checkedState() { return m_checkedState;}

    void setCheckedState(bool data){
        if(m_checkedState != data){
            LOG << "[APP_DATA]" << data;
            m_checkedState = data;
            emit checkedStateChanged();
        }
    }

signals:
    void checkedStateChanged();

private:
    QString m_packageName;
    bool m_checkedState;
};

class AppModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> appDataList READ appDataList WRITE setAppDataList NOTIFY appDataListChanged)
    Q_PROPERTY(bool saveToLocal READ saveToLocal WRITE setSaveToLocal NOTIFY saveToLocalChanged)
    Q_PROPERTY(bool saveToServer READ saveToServer WRITE setSaveToServer NOTIFY saveToServerChanged)
    Q_PROPERTY(bool useKeyboard READ useKeyboard WRITE setUseKeyboard NOTIFY useKeyboardChanged)
    Q_PROPERTY(bool regFacebookOption READ regFacebookOption WRITE setRegFacebookOption NOTIFY regFacebookOptionChanged)
    Q_PROPERTY(bool recoveryEmail READ recoveryEmail WRITE setRecoveryEmail NOTIFY recoveryEmailChanged)
    Q_PROPERTY(QString nameLang READ nameLang WRITE setNameLang NOTIFY nameLangChanged)

private:
    explicit AppModel(QObject *parent = nullptr);

public:
    static AppModel *instance();


    QList<QObject *> appDataList();
    void setAppDataList(QList<QObject*> data);

    bool saveToLocal() const;
    void setSaveToLocal(bool data);

    bool saveToServer() const;
    void setSaveToServer(bool data);

    bool useKeyboard();
    void setUseKeyboard(bool data);

    bool regFacebookOption() const;
    void setRegFacebookOption(bool data);

    bool recoveryEmail() const;
    void setRecoveryEmail(bool data);

    QString nameLang() const;
    void setNameLang(QString data);
public:
    Q_INVOKABLE void startProgram(QString tokenID);
    Q_INVOKABLE void closeProgram(QString tokenID);
    Q_INVOKABLE void saveSettingConfig();

signals:
    void appDataListChanged();
    void saveToLocalChanged();
    void saveToServerChanged();
    void useKeyboardChanged();
    void signalStartProgram(QString tokenID);
    void signalCloseProgram(QString tokenID);
    void signalSaveSettingConfig();
    void regFacebookOptionChanged();
    void recoveryEmailChanged();
    void nameLangChanged();

private:
    static AppModel* m_instance;

private:
    QList<QObject*> m_appDataList;
    bool m_saveToLocal;
    bool m_saveToServer;
    bool m_useKeyboard;
    bool m_regFacebookOption;
    bool m_recoveryEmail;
    QString m_nameLang;

    QStringList PACKAGE_LIST = QStringList() << "app.haonam.xgame"
            << "com.android.apps.tag"
            << "com.android.backupconfirm"
            << "com.android.bluetooth"
            << "com.android.browser"
            << "com.android.browser.res.overlay"
            << "com.android.calculator2"
            << "com.android.calendar"
            << "com.android.certinstaller"
            << "com.android.chrome"
            << "com.android.defcontainer"
            << "com.android.documentsui"
            << "com.android.dreams.basic"
            << "com.android.dreams.phototable"
            << "com.android.email"
            << "com.android.exchange"
            << "com.android.externalstorage"
            << "com.android.facelock"
            << "com.android.galaxy4"
            << "com.android.htmlviewer"
            << "com.android.incallui"
            << "com.android.inputdevices"
            << "com.android.keychain"
            << "com.android.keyguard"
            << "com.android.location.fused"
            << "com.android.magicsmoke"
            << "com.android.musicfx"
            << "com.android.musicvis"
            << "com.android.nfc"
            << "com.android.noisefield"
            << "com.android.onetimeinitializer"
            << "com.android.packageinstaller"
            << "com.android.pacprocessor"
            << "com.android.partnerbrowsercustomizations.chromeHomepage"
            << "com.android.phasebeam"
            << "com.android.phone"
            << "com.android.printspooler"
            << "com.android.providers.calendar"
            << "com.android.providers.contacts"
            << "com.android.providers.downloads"
            << "com.android.providers.downloads.ui"
            << "com.android.providers.media"
            << "com.android.providers.partnerbookmarks"
            << "com.android.providers.partnerbookmarks.res.overlay"
            << "com.android.providers.settings"
            << "com.android.providers.telephony"
            << "com.android.providers.userdictionary"
            << "com.android.proxyhandler"
            << "com.android.settings"
            << "com.android.sharedstoragebackup"
            << "com.android.shell"
            << "com.android.smspush"
            << "com.android.soundrecorder"
            << "com.android.stk"
            << "com.android.systemui"
            << "com.android.vending"
            << "com.android.vpndialogs"
            << "com.android.wallpaper"
            << "com.android.wallpaper.holospiral"
            << "com.android.wallpaper.livepicker"
            << "com.android.wallpapercropper"
            << "com.bambuser.sociallive"
            << "com.dsi.ant.server"
            << "com.facebook.katana"
            << "com.facebook.lite"
            << "com.google.android.apps.books"
            << "com.google.android.apps.docs"
            << "com.google.android.apps.genie.geniewidget"
            << "com.google.android.apps.magazines"
            << "com.google.android.apps.maps"
            << "com.google.android.apps.plus"
            << "com.google.android.backuptransport"
            << "com.google.android.configupdater"
            << "com.google.android.feedback"
            << "com.google.android.gm"
            << "com.google.android.gms"
            << "com.google.android.googlequicksearchbox"
            << "com.google.android.gsf"
            << "com.google.android.gsf.login"
            << "com.google.android.marvin.talkback"
            << "com.google.android.music"
            << "com.google.android.partnersetup"
            << "com.google.android.play.games"
            << "com.google.android.setupwizard"
            << "com.google.android.street"
            << "com.google.android.syncadapters.calendar"
            << "com.google.android.syncadapters.contacts"
            << "com.google.android.talk"
            << "com.google.android.tts"
            << "com.google.android.videos"
            << "com.google.android.youtube"
            << "com.mobisystems.fileman"
            << "com.mobisystems.office"
            << "com.navigon.navigator_select_sony_eu"
            << "com.qualcomm.location"
            << "com.qualcomm.qcrilmsgtunnel"
            << "com.qualcomm.shutdownlistner"
            << "com.qualcomm.timeservice"
            << "com.qualcomm.wfd.service"
            << "com.realvnc.android.remote"
            << "com.s.antivirus"
            << "com.scee.psxandroid"
            << "com.sony.nfx.app.sfrc"
            << "com.sony.nfx.service.WirelessControllerManagerService"
            << "com.sony.smallapp.app.widget"
            << "com.sony.smallapp.appframework"
            << "com.sony.smallapp.launcher"
            << "com.sony.smallapp.managerservice"
            << "com.sony.snei.np.android.account"
            << "com.sony.snei.vu"
            << "com.sonyericsson.advancedwidget.clock"
            << "com.sonyericsson.advancedwidget.photo"
            << "com.sonyericsson.advancedwidget.weather"
            << "com.sonyericsson.album"
            << "com.sonyericsson.album.overlay"
            << "com.sonyericsson.android.addoncamera.artfilter"
            << "com.sonyericsson.android.bootinfo"
            << "com.sonyericsson.android.camera"
            << "com.sonyericsson.android.camera3d"
            << "com.sonyericsson.android.drm.services"
            << "com.sonyericsson.android.locationbasedwifi"
            << "com.sonyericsson.android.omacp"
            << "com.sonyericsson.android.servicemenu"
            << "com.sonyericsson.android.servicemenu.product.res.overlay.leo"
            << "com.sonyericsson.android.servicemenu.product.res.overlay.shinano"
            << "com.sonyericsson.android.smartsearch"
            << "com.sonyericsson.android.socialphonebook"
            << "com.sonyericsson.android.wakeup"
            << "com.sonyericsson.androidapp.everchwallpaper"
            << "com.sonyericsson.androidapp.fbcalendarsync"
            << "com.sonyericsson.androidapp.fbmusiclike"
            << "com.sonyericsson.autopoweroffservice"
            << "com.sonyericsson.blackthemeblueaccent"
            << "com.sonyericsson.cameraextension.permission"
            << "com.sonyericsson.capabilities"
            << "com.sonyericsson.capabilities.res.overlay"
            << "com.sonyericsson.conversations"
            << "com.sonyericsson.crashmonitor"
            << "com.sonyericsson.credentialmanagerservice"
            << "com.sonyericsson.customizedsettings"
            << "com.sonyericsson.devicemonitor"
            << "com.sonyericsson.drmdialogs"
            << "com.sonyericsson.dtcpctrl"
            << "com.sonyericsson.extras.liveware"
            << "com.sonyericsson.facebook.proxylogin"
            << "com.sonyericsson.fmradio"
            << "com.sonyericsson.home"
            << "com.sonyericsson.idd.agent"
            << "com.sonyericsson.initialbootsetup"
            << "com.sonyericsson.localcontacts"
            << "com.sonyericsson.lockscreen.uxpnxt"
            << "com.sonyericsson.mbt.panicattack"
            << "com.sonyericsson.metadatacleanup"
            << "com.sonyericsson.mtp"
            << "com.sonyericsson.mtp.extension.backuprestore"
            << "com.sonyericsson.mtp.extension.factoryreset"
            << "com.sonyericsson.mtp.extension.marlin"
            << "com.sonyericsson.mtp.extension.update"
            << "com.sonyericsson.music"
            << "com.sonyericsson.music.googlelyricsplugin"
            << "com.sonyericsson.music.wikipediaplugin"
            << "com.sonyericsson.music.youtubekaraokeplugin"
            << "com.sonyericsson.music.youtubeplugin"
            << "com.sonyericsson.musicvisualizer"
            << "com.sonyericsson.omadl"
            << "com.sonyericsson.organizer"
            << "com.sonyericsson.photoeditor"
            << "com.sonyericsson.providers.cnap"
            << "com.sonyericsson.providers.protectedmedia"
            << "com.sonyericsson.psm.sysmonservice"
            << "com.sonyericsson.r2r.client"
            << "com.sonyericsson.r2r.client.res.overlay"
            << "com.sonyericsson.settings"
            << "com.sonyericsson.settings.wifi"
            << "com.sonyericsson.setupwizard"
            << "com.sonyericsson.simcontacts"
            << "com.sonyericsson.simdetection"
            << "com.sonyericsson.socialengine"
            << "com.sonyericsson.socialengine.plugins.facebook"
            << "com.sonyericsson.socialengine.plugins.picasa"
            << "com.sonyericsson.soundenhancement"
            << "com.sonyericsson.startupflagservice"
            << "com.sonyericsson.suquashi.soundpicker"
            << "com.sonyericsson.tetherentitlementcheck"
            << "com.sonyericsson.textinput.chinese"
            << "com.sonyericsson.textinput.uxp"
            << "com.sonyericsson.textinput.uxp.dictionaries"
            << "com.sonyericsson.thememanager"
            << "com.sonyericsson.trackid"
            << "com.sonyericsson.trackid.res.overlay"
            << "com.sonyericsson.tvlauncher"
            << "com.sonyericsson.tvout.mhl"
            << "com.sonyericsson.tvout.mhl.product.res.overlay"
            << "com.sonyericsson.unsupportedheadsetnotifier"
            << "com.sonyericsson.updatecenter"
            << "com.sonyericsson.updatecenter.res.overlay"
            << "com.sonyericsson.usbux"
            << "com.sonyericsson.uxp"
            << "com.sonyericsson.video"
            << "com.sonyericsson.wallpaperpicker"
            << "com.sonyericsson.wappush"
            << "com.sonyericsson.warrantytime"
            << "com.sonyericsson.xhs"
            << "com.sonymobile.acr"
            << "com.sonymobile.advancedwidget.entrance"
            << "com.sonymobile.advancedwidget.topcontacts"
            << "com.sonymobile.advancedwidget.worldclock"
            << "com.sonymobile.android.addoncamera.dual"
            << "com.sonymobile.android.addoncamera.onlineremote"
            << "com.sonymobile.android.addoncamera.soundphoto"
            << "com.sonymobile.android.addoncamera.supervideo"
            << "com.sonymobile.android.addoncamera.timeshift"
            << "com.sonymobile.android.externalkeyboard"
            << "com.sonymobile.android.externalkeyboardjp"
            << "com.sonymobile.androidapp.cameraaddon.areffect"
            << "com.sonymobile.androidapp.cameraaddon.arfun"
            << "com.sonymobile.androidapp.cameraaddon.infoeye"
            << "com.sonymobile.androidapp.diagnostics"
            << "com.sonymobile.anondata"
            << "com.sonymobile.aptx.notifier"
            << "com.sonymobile.autopairing"
            << "com.sonymobile.backgrounddefocus"
            << "com.sonymobile.bluetoothunlock.settings"
            << "com.sonymobile.callwidgetframework.permission"
            << "com.sonymobile.camera.addon.livefromsonyxperia"
            << "com.sonymobile.camera.addon.permission"
            << "com.sonymobile.cameracommon"
            << "com.sonymobile.cameracommon.permission"
            << "com.sonymobile.camerawidget"
            << "com.sonymobile.coverapp"
            << "com.sonymobile.coverwidget"
            << "com.sonymobile.crashmonitor.system"
            << "com.sonymobile.customizationselector"
            << "com.sonymobile.deviceconfigtool"
            << "com.sonymobile.devicesecurity.service"
            << "com.sonymobile.dlna"
            << "com.sonymobile.drm.ui"
            << "com.sonymobile.dualshockmanager"
            << "com.sonymobile.enterprise.service"
            << "com.sonymobile.experienceflow2"
            << "com.sonymobile.extendedbootlock.service"
            << "com.sonymobile.faceregistration"
            << "com.sonymobile.gmailreaderservice"
            << "com.sonymobile.googleanalyticsproxy"
            << "com.sonymobile.gpssatellitesnotification"
            << "com.sonymobile.headphoneselection"
            << "com.sonymobile.helpapp7"
            << "com.sonymobile.imageenhancer"
            << "com.sonymobile.imageprocessor.permission"
            << "com.sonymobile.intelligent.backlight"
            << "com.sonymobile.intelligent.gesture"
            << "com.sonymobile.intelligent.iengine"
            << "com.sonymobile.intelligent.rotation"
            << "com.sonymobile.intelligent.settings"
            << "com.sonymobile.lifelog"
            << "com.sonymobile.lockscreen.otp"
            << "com.sonymobile.mirrorlink.manualswitch"
            << "com.sonymobile.mirrorlink.server11"
            << "com.sonymobile.mirrorlink.system"
            << "com.sonymobile.moviecreator"
            << "com.sonymobile.moviecreator.rmm"
            << "com.sonymobile.musicslideshow"
            << "com.sonymobile.mx.android"
            << "com.sonymobile.packagecourier"
            << "com.sonymobile.phoneusage"
            << "com.sonymobile.photoanalyzer"
            << "com.sonymobile.playanywhere"
            << "com.sonymobile.pobox"
            << "com.sonymobile.podcast"
            << "com.sonymobile.premiumsmsupdate"
            << "com.sonymobile.protectedmedia"
            << "com.sonymobile.prototypeprotection"
            << "com.sonymobile.providers.topcontacts"
            << "com.sonymobile.remotefileaccess"
            << "com.sonymobile.remotestorage"
            << "com.sonymobile.retaildemo"
            << "com.sonymobile.roaming.genius"
            << "com.sonymobile.runtimeskinning.core"
            << "com.sonymobile.screenrecording"
            << "com.sonymobile.seamlesstether"
            << "com.sonymobile.settings.wifi.hotspot2"
            << "com.sonymobile.shareapplication"
            << "com.sonymobile.simlockunlockapp"
            << "com.sonymobile.simplehome"
            << "com.sonymobile.sketch"
            << "com.sonymobile.slideshow"
            << "com.sonymobile.smallapps.calc"
            << "com.sonymobile.smallapps.clipper"
            << "com.sonymobile.smallapps.timer"
            << "com.sonymobile.smallbrowser"
            << "com.sonymobile.socialengine.plugins.facebook_sharefrwk"
            << "com.sonymobile.socialengine.plugins.twitter_sharefrwk"
            << "com.sonymobile.sonyselect"
            << "com.sonymobile.storagechecker"
            << "com.sonymobile.superstamina"
            << "com.sonymobile.superstamina.leo.res.overlay"
            << "com.sonymobile.superstamina.res.overlay"
            << "com.sonymobile.synchub"
            << "com.sonymobile.taskkiller"
            << "com.sonymobile.tasks"
            << "com.sonymobile.themes.id001"
            << "com.sonymobile.themes.id002"
            << "com.sonymobile.themes.id003"
            << "com.sonymobile.themes.id004"
            << "com.sonymobile.themes.id005"
            << "com.sonymobile.themes.id006"
            << "com.sonymobile.touchblocker"
            << "com.sonymobile.touchscreen.touchfilter"
            << "com.sonymobile.transmitpower"
            << "com.sonymobile.tvout.wifidisplay"
            << "com.sonymobile.twitter.account"
            << "com.sonymobile.userdatalogging"
            << "com.sonymobile.usm"
            << "com.sonymobile.webview"
            << "com.sonymobile.whitebalance"
            << "com.sonymobile.xperialounge.services"
            << "com.sonymobile.xtp.android"
            << "com.svox.pico"
            << "com.vmware.mvp.enabled"
            << "org.codeaurora.bluetooth"
            << "org.codeaurora.ims"
            << "org.simalliance.openmobileapi.service";


public slots:
};

#endif // APPMODEL_H
