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

public:
    Q_INVOKABLE void startProgram();
    Q_INVOKABLE void closeProgram();
    Q_INVOKABLE void saveSettingConfig();

signals:
    void appDataListChanged();
    void saveToLocalChanged();
    void saveToServerChanged();
    void useKeyboardChanged();
    void signalStartProgram();
    void signalCloseProgram();
    void signalSaveSettingConfig();

private:
    static AppModel* m_instance;

private:
    QList<QObject*> m_appDataList;
    bool m_saveToLocal;
    bool m_saveToServer;
    bool m_useKeyboard;

    QStringList PACKAGE_LIST = QStringList() << "com.sonyericsson.cameraextension.permission"
                                             << "com.android.defcontainer"
                                             << "com.sonymobile.coverwidget"
                                             << "com.sonymobile.cameracommon"
                                             << "com.facebook.lite"
                                             << "com.android.phone"
                                             << "com.sonyericsson.initialbootsetup"
                                             << "com.mobisystems.fileman"
                                             << "com.sonyericsson.unsupportedheadsetnotifier"
                                             << "com.sonyericsson.providers.protectedmedia"
                                             << "com.sonyericsson.facebook.proxylogin"
                                             << "com.android.bluetooth"
                                             << "com.android.providers.calendar"
                                             << "com.sonymobile.advancedwidget.entrance"
                                             << "com.sonymobile.androidapp.cameraaddon.arfun"
                                             << "com.sony.smallapp.launcher"
                                             << "com.vmware.mvp.enabled"
                                             << "com.sonyericsson.android.bootinfo"
                                             << "com.sonymobile.dlna"
                                             << "com.android.browser"
                                             << "com.sonymobile.experienceflow2"
                                             << "com.android.browser.res.overlay"
                                             << "com.android.providers.downloads.ui"
                                             << "com.sonyericsson.capabilities.res.overlay"
                                             << "com.android.documentsui"
                                             << "com.sonymobile.smallapps.clipper"
                                             << "com.android.vpndialogs"
                                             << "com.android.providers.media"
                                             << "com.sonyericsson.android.camera3d"
                                             << "com.sonymobile.backgrounddefocus"
                                             << "com.s.antivirus"
                                             << "com.sonymobile.phoneusage"
                                             << "com.sonymobile.tasks"
                                             << "com.sonymobile.simplehome"
                                             << "com.sonyericsson.music.youtubeplugin"
                                             << "com.sonymobile.podcast"
                                             << "com.google.android.setupwizard"
                                             << "com.sonyericsson.autopoweroffservice"
                                             << "com.android.settings"
                                             << "com.sonymobile.android.externalkeyboardjp"
                                             << "com.sonyericsson.mtp.extension.update"
                                             << "com.sonyericsson.soundenhancement"
                                             << "com.sonyericsson.android.camera"
                                             << "com.google.android.street"
                                             << "com.sonyericsson.trackid.res.overlay"
                                             << "com.google.android.apps.genie.geniewidget"
                                             << "com.facebook.katana"
                                             << "com.google.android.googlequicksearchbox"
                                             << "com.sonyericsson.android.omacp"
                                             << "com.sonyericsson.psm.sysmonservice"
                                             << "com.android.musicvis"
                                             << "com.android.exchange"
                                             << "com.sonyericsson.localcontacts"
                                             << "com.google.android.backuptransport"
                                             << "com.sonymobile.aptx.notifier"
                                             << "com.sonyericsson.androidapp.fbmusiclike"
                                             << "com.android.providers.telephony"
                                             << "com.sonyericsson.r2r.client"
                                             << "com.svox.pico"
                                             << "com.sonyericsson.android.servicemenu"
                                             << "com.sonyericsson.advancedwidget.photo"
                                             << "com.sonymobile.intelligent.rotation"
                                             << "com.sonymobile.smallapps.timer"
                                             << "com.google.android.apps.maps"
                                             << "com.sonyericsson.trackid"
                                             << "com.android.wallpapercropper"
                                             << "com.sonymobile.enterprise.service"
                                             << "com.android.providers.settings"
                                             << "com.sonymobile.customizationselector"
                                             << "com.sony.snei.np.android.account"
                                             << "com.sonymobile.seamlesstether"
                                             << "com.sonyericsson.startupflagservice"
                                             << "com.qualcomm.qcrilmsgtunnel"
                                             << "com.google.android.apps.docs"
                                             << "com.sonymobile.socialengine.plugins.twitter_sharefrwk"
                                             << "com.sonyericsson.androidapp.everchwallpaper"
                                             << "com.android.providers.downloads"
                                             << "com.sonymobile.storagechecker"
                                             << "com.sonymobile.camera.addon.livefromsonyxperia"
                                             << "com.sonymobile.camera.addon.permission"
                                             << "com.sonyericsson.devicemonitor"
                                             << "com.android.phasebeam"
                                             << "com.sonymobile.imageenhancer"
                                             << "com.sonymobile.googleanalyticsproxy"
                                             << "com.sonyericsson.android.locationbasedwifi"
                                             << "com.sonyericsson.wallpaperpicker"
                                             << "com.sonymobile.mx.android"
                                             << "com.sonyericsson.extras.liveware"
                                             << "com.sonyericsson.capabilities"
                                             << "com.google.android.videos"
                                             << "com.sonymobile.deviceconfigtool"
                                             << "com.sonyericsson.socialengine.plugins.picasa"
                                             << "com.sonymobile.extendedbootlock.service"
                                             << "com.sonymobile.roaming.genius"
                                             << "com.sonymobile.lifelog"
                                             << "com.sonymobile.crashmonitor.system"
                                             << "com.sonymobile.photoanalyzer"
                                             << "com.sony.nfx.app.sfrc"
                                             << "com.sonyericsson.customizedsettings"
                                             << "com.android.inputdevices"
                                             << "com.sonyericsson.android.wakeup"
                                             << "com.sonymobile.autopairing"
                                             << "com.sonymobile.simlockunlockapp"
                                             << "com.sonymobile.cameracommon.permission"
                                             << "com.sonymobile.intelligent.settings"
                                             << "com.sonyericsson.video"
                                             << "com.sonyericsson.tvlauncher"
                                             << "com.sonyericsson.idd.agent"
                                             << "com.android.stk"
                                             << "com.qualcomm.shutdownlistner"
                                             << "com.sonyericsson.providers.cnap"
                                             << "com.sonymobile.slideshow"
                                             << "com.sonymobile.smallapps.calc"
                                             << "com.google.android.configupdater"
                                             << "com.sonymobile.playanywhere"
                                             << "com.sonyericsson.r2r.client.res.overlay"
                                             << "com.sonymobile.userdatalogging"
                                             << "com.sonyericsson.lockscreen.uxpnxt"
                                             << "com.sonymobile.runtimeskinning.core"
                                             << "com.sonyericsson.tvout.mhl"
                                             << "com.sonymobile.settings.wifi.hotspot2"
                                             << "com.sonymobile.intelligent.iengine"
                                             << "android"
                                             << "com.android.providers.contacts"
                                             << "com.sonymobile.coverapp"
                                             << "com.android.externalstorage"
                                             << "com.sonymobile.anondata"
                                             << "com.sonyericsson.mtp.extension.backuprestore"
                                             << "com.sonymobile.synchub"
                                             << "com.sonymobile.prototypeprotection"
                                             << "com.sonymobile.premiumsmsupdate"
                                             << "com.android.incallui"
                                             << "com.google.android.apps.plus"
                                             << "com.android.vending"
                                             << "com.sonymobile.xperialounge.services"
                                             << "com.android.keychain"
                                             << "com.sony.smallapp.managerservice"
                                             << "com.sonyericsson.mbt.panicattack"
                                             << "com.android.wallpaper"
                                             << "com.android.providers.partnerbookmarks.res.overlay"
                                             << "com.sonymobile.webview"
                                             << "com.sonymobile.superstamina"
                                             << "com.sonyericsson.crashmonitor"
                                             << "com.sonymobile.android.externalkeyboard"
                                             << "com.google.android.apps.magazines"
                                             << "com.sonyericsson.album"
                                             << "com.sonyericsson.suquashi.soundpicker"
                                             << "com.sonyericsson.xhs"
                                             << "com.google.android.gsf"
                                             << "com.android.keyguard"
                                             << "com.sonymobile.xtp.android"
                                             << "com.sonyericsson.drmdialogs"
                                             << "com.android.shell"
                                             << "com.sony.smallapp.appframework"
                                             << "com.google.android.syncadapters.contacts"
                                             << "com.sonymobile.packagecourier"
                                             << "com.sonymobile.smallbrowser"
                                             << "com.sonymobile.mirrorlink.server11"
                                             << "com.qualcomm.timeservice"
                                             << "com.sonymobile.intelligent.gesture"
                                             << "com.sonymobile.moviecreator.rmm"
                                             << "com.android.providers.partnerbookmarks"
                                             << "com.sonymobile.faceregistration"
                                             << "com.sonyericsson.android.drm.services"
                                             << "com.sonymobile.imageprocessor.permission"
                                             << "com.sonyericsson.metadatacleanup"
                                             << "com.android.calculator2"
                                             << "com.bambuser.sociallive"
                                             << "com.sonyericsson.textinput.chinese"
                                             << "com.android.htmlviewer"
                                             << "com.sonymobile.socialengine.plugins.facebook_sharefrwk"
                                             << "com.sony.nfx.service.WirelessControllerManagerService"
                                             << "com.google.android.gsf.login"
                                             << "com.sonymobile.moviecreator"
                                             << "com.sonyericsson.advancedwidget.weather"
                                             << "com.sonymobile.protectedmedia"
                                             << "com.sonyericsson.conversations"
                                             << "com.sonyericsson.updatecenter.res.overlay"
                                             << "com.sonymobile.gpssatellitesnotification"
                                             << "com.sonyericsson.uxp"
                                             << "com.android.calendar"
                                             << "com.sonymobile.androidapp.diagnostics"
                                             << "com.dsi.ant.server"
                                             << "org.codeaurora.ims"
                                             << "com.sonyericsson.music.wikipediaplugin"
                                             << "com.sonyericsson.textinput.uxp"
                                             << "com.android.onetimeinitializer"
                                             << "com.sonyericsson.textinput.uxp.dictionaries"
                                             << "com.sonymobile.usm"
                                             << "com.sonymobile.sketch"
                                             << "com.sony.snei.vu"
                                             << "com.sonyericsson.wappush"
                                             << "com.sonymobile.headphoneselection"
                                             << "com.sonymobile.musicslideshow"
                                             << "com.android.sharedstoragebackup"
                                             << "com.sonymobile.shareapplication"
                                             << "com.sonymobile.advancedwidget.topcontacts"
                                             << "com.sonyericsson.updatecenter"
                                             << "com.sonymobile.transmitpower"
                                             << "com.sonyericsson.tetherentitlementcheck"
                                             << "com.sonymobile.camerawidget"
                                             << "com.google.android.marvin.talkback"
                                             << "com.android.certinstaller"
                                             << "com.sonyericsson.android.addoncamera.artfilter"
                                             << "com.google.android.gms"
                                             << "com.android.dreams.phototable"
                                             << "com.sonymobile.remotestorage"
                                             << "com.sonyericsson.simdetection"
                                             << "com.sonymobile.drm.ui"
                                             << "org.simalliance.openmobileapi.service"
                                             << "com.sonyericsson.thememanager"
                                             << "com.sonyericsson.mtp.extension.marlin"
                                             << "com.sonyericsson.android.smartsearch"
                                             << "com.sonyericsson.fmradio"
                                             << "com.sonymobile.providers.topcontacts"
                                             << "com.google.android.music"
                                             << "com.sonymobile.whitebalance"
                                             << "com.android.wallpaper.livepicker"
                                             << "com.sonymobile.retaildemo"
                                             << "com.sonyericsson.music"
                                             << "com.sony.smallapp.app.widget"
                                             << "com.android.packageinstaller"
                                             << "com.sonymobile.devicesecurity.service"
                                             << "com.sonymobile.taskkiller"
                                             << "com.google.android.tts"
                                             << "com.sonymobile.android.addoncamera.soundphoto"
                                             << "com.android.noisefield"
                                             << "com.sonymobile.android.addoncamera.supervideo"
                                             << "com.android.email"
                                             << "com.sonyericsson.home"
                                             << "com.android.location.fused"
                                             << "com.android.backupconfirm"
                                             << "com.android.magicsmoke"
                                             << "com.sonymobile.android.addoncamera.dual"
                                             << "com.sonyericsson.android.servicemenu.product.res.overlay.leo"
                                             << "com.sonymobile.mirrorlink.manualswitch"
                                             << "com.sonymobile.tvout.wifidisplay"
                                             << "com.sonyericsson.warrantytime"
                                             << "com.sonymobile.touchblocker"
                                             << "com.android.musicfx"
                                             << "com.sonymobile.intelligent.backlight"
                                             << "com.google.android.apps.books"
                                             << "com.sonyericsson.advancedwidget.clock"
                                             << "com.sonyericsson.android.servicemenu.product.res.overlay.shinano"
                                             << "com.android.soundrecorder"
                                             << "app.haonam.xgame"
                                             << "com.navigon.navigator_select_sony_eu"
                                             << "com.sonymobile.pobox"
                                             << "com.sonymobile.touchscreen.touchfilter"
                                             << "com.sonyericsson.mtp"
                                             << "com.sonyericsson.album.overlay"
                                             << "com.sonymobile.themes.id001"
                                             << "com.sonymobile.themes.id002"
                                             << "com.sonyericsson.androidapp.fbcalendarsync"
                                             << "com.sonymobile.themes.id003"
                                             << "com.sonymobile.themes.id004"
                                             << "com.sonymobile.bluetoothunlock.settings"
                                             << "com.sonymobile.themes.id005"
                                             << "com.sonymobile.screenrecording"
                                             << "com.sonymobile.themes.id006"
                                             << "com.google.android.partnersetup"
                                             << "com.sonyericsson.mtp.extension.factoryreset"
                                             << "com.sonymobile.mirrorlink.system"
                                             << "com.android.proxyhandler"
                                             << "com.sonyericsson.android.socialphonebook"
                                             << "com.mobisystems.office"
                                             << "com.android.wallpaper.holospiral"
                                             << "com.google.android.feedback"
                                             << "com.sonyericsson.blackthemeblueaccent"
                                             << "com.google.android.talk"
                                             << "com.android.nfc"
                                             << "com.sonyericsson.music.googlelyricsplugin"
                                             << "com.sonymobile.gmailreaderservice"
                                             << "com.android.providers.userdictionary"
                                             << "com.sonyericsson.socialengine"
                                             << "com.sonyericsson.settings.wifi"
                                             << "com.sonyericsson.tvout.mhl.product.res.overlay"
                                             << "com.android.pacprocessor"
                                             << "org.codeaurora.bluetooth"
                                             << "com.sonymobile.dualshockmanager"
                                             << "com.sonymobile.android.addoncamera.onlineremote"
                                             << "com.sonymobile.androidapp.cameraaddon.areffect"
                                             << "com.sonymobile.sonyselect"
                                             << "com.android.galaxy4"
                                             << "com.android.printspooler"
                                             << "com.sonyericsson.omadl"
                                             << "com.google.android.syncadapters.calendar"
                                             << "com.sonymobile.lockscreen.otp"
                                             << "com.qualcomm.location"
                                             << "com.android.partnerbrowsercustomizations.chromeHomepage"
                                             << "com.qualcomm.wfd.service"
                                             << "com.sonyericsson.setupwizard"
                                             << "com.sonymobile.helpapp7"
                                             << "com.sonyericsson.settings"
                                             << "com.android.dreams.basic"
                                             << "com.sonymobile.android.addoncamera.timeshift"
                                             << "com.sonyericsson.socialengine.plugins.facebook"
                                             << "com.android.apps.tag"
                                             << "com.google.android.play.games"
                                             << "com.android.systemui"
                                             << "com.sonymobile.superstamina.leo.res.overlay"
                                             << "com.sonymobile.advancedwidget.worldclock"
                                             << "com.android.smspush"
                                             << "com.google.android.gm"
                                             << "com.sonyericsson.organizer"
                                             << "com.scee.psxandroid"
                                             << "com.sonyericsson.musicvisualizer"
                                             << "com.google.android.youtube"
                                             << "com.sonymobile.callwidgetframework.permission"
                                             << "com.sonymobile.remotefileaccess"
                                             << "com.sonyericsson.credentialmanagerservice"
                                             << "com.sonyericsson.photoeditor"
                                             << "com.sonyericsson.music.youtubekaraokeplugin"
                                             << "com.android.facelock"
                                             << "com.android.chrome"
                                             << "com.realvnc.android.remote"
                                             << "com.sonymobile.androidapp.cameraaddon.infoeye"
                                             << "com.sonyericsson.usbux"
                                             << "com.sonymobile.twitter.account"
                                             << "com.sonyericsson.dtcpctrl"
                                             << "com.sonymobile.acr"
                                             << "com.sonyericsson.simcontacts"
                                             << "com.sonymobile.superstamina.res.overlay";


public slots:
};

#endif // APPMODEL_H
