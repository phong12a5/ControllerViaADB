#include "ADBCommand.h"

QString ADBCommand::screenShot(QString fileName, QString path)
{
//    LOG << "[ADBCommand]" << "Path: " << path  << " --- FileName: " << fileName;
    QProcess proc;
    proc.start(QString("adb shell screencap -p %1screen.png").arg(IMAGE_FOLDER));
    proc.waitForFinished(-1);
    proc.start(QString("adb pull %1screen.png %2").arg(IMAGE_FOLDER).arg(path));
    proc.waitForFinished(-1);
    return path + "/" + fileName;
}

void ADBCommand::swipeScreen(QPoint sourcePoint, QPoint desPoint)
{
    LOG << "[ADBCommand]" << "Swiping from " << sourcePoint << " to" << desPoint;
    QProcess proc;
    proc.start(QString("adb shell input swipe %1 %2 %3 %4")\
               .arg(sourcePoint.x())\
               .arg(sourcePoint.y())\
               .arg(desPoint.x())\
               .arg(desPoint.y()));
    proc.waitForFinished(-1);
    return;
}

bool ADBCommand::requestShowApp(QString packageName, QString activity)
{
    LOG << "[ADBCommand]" << "packageName: " << packageName << " --- activity: " << activity;
    QProcess proc;
    proc.start(QString("adb shell am start -n %1/%2").arg(packageName).arg(activity));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::goHomeScreen()
{
    LOG << "[ADBCommand]";
    QProcess proc;
    proc.start(QString("adb shell input keyevent KEYCODE_HOME"));
    proc.waitForFinished(-1);
    delay(100);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

void ADBCommand::pressBack()
{
    LOG << "[ADBCommand]";
    QProcess proc;
    proc.start(QString("adb shell input keyevent KEYCODE_BACK"));
    proc.waitForFinished(-1);
}

bool ADBCommand::requestShowAppDirectly(QString activity)
{
    LOG << "[ADBCommand]" << "acivity: " << activity;
    QProcess proc;
    proc.start(QString("adb shell am start -a %1").arg(activity));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::enterText(QString text)
{
    LOG << "[ADBCommand]" << "Entering text: " << text;
    QProcess proc;
//    for(int i = 0; i < text.length(); i++){
//        proc.start(QString("adb shell input text %1").arg(text.at(i)));
//        delay(10);
//        proc.waitForFinished(-1);
//    }
    proc.start(QString("adb shell input text %1").arg(text));
    proc.waitForFinished(-1);

    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::pressTap()
{
    LOG << "[ADBCommand]" << "Pressing Tap Key ...";
    QProcess proc;
    proc.start(QString("adb shell input keyevent KEYCODE_TAB"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::rebootDevice()
{
    LOG << "[ADBCommand]";
    QProcess proc;
    proc.start(QString("adb shell reboot"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        return true;
    }
}

bool ADBCommand::checkConnection()
{
    QProcess proc;
    proc.start(QString("adb devices"));
    proc.waitForFinished(-1);
    if(proc.readAllStandardError() != ""){
        LOG << "[ADBCommand]" << "ERROR: " << proc.readAllStandardError();
        return false;
    }else {
        QString output = proc.readAllStandardOutput();
        LOG << "output: " << output;
        output.remove("List of devices attached");
        output.remove("device");
        output.remove("\r");
        output.remove("\n");
        output.remove("\t");
        output.remove(" ");
        delay(200);
        if(output != ""){
            return true;
        }else {
            LOG << "[ADBCommand]" << "There is no device is connected!";
            return false;
        }
    }
}

bool ADBCommand::customCommand(QString cmd)
{
    LOG << "[ADBCommand]" << "Cmd: " << cmd;
    bool retVal = true;
    return retVal;
}

QString ADBCommand::currentActivity()
{
    QString retVal = "";
    if(checkConnection()){
        QProcess proc;

        proc.start(" adb shell dumpsys input_method | grep mScreenOn");
        proc.waitForFinished(-1);

        if(QString(proc.readAllStandardOutput()).contains("mScreenOn=false")){
            wakeUpScreen();
        }

        proc.start("adb shell dumpsys window windows | grep -E 'mCurrentFocus'");
        proc.waitForFinished(-1);
        QStringList output = QString(proc.readAllStandardOutput()).split(' ');
        if(output.length() > 4){
            retVal = output.at(4).simplified().remove('}');
        }
    }else{
        retVal = UNKNOW_SCREEN;
    }
    delay(200);
    return retVal;
}

void ADBCommand::killSpecificApp(QString packageName)
{
    LOG << "[ADBCommand]" << "Killing " << packageName;
    QProcess proc;
    proc.start(QString("adb shell am force-stop %1").arg(packageName));
    proc.waitForFinished(-1);
    delay(100);
    return;
}

bool ADBCommand::isOnScreen(QString iconPath)
{
    QString screenImgPath = ADBCommand::screenShot();
    QPoint point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    if(!point.isNull()){
        return true;
    }else{
        screenImgPath = ADBCommand::screenShot();
        point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
        if(!point.isNull()){
            return true;
        }else{
            return false;
        }
    }
}

QPoint ADBCommand::findAnImageOnScreen(QString iconPath)
{
    QString screenImgPath = ADBCommand::screenShot();
    QPoint point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    if(point.isNull()){
        screenImgPath = ADBCommand::screenShot();
        point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    }
    return  point;
}

void ADBCommand::tapScreen(QPoint point, bool noDelay)
{
    LOG << "[ADBCommand]" << "Tapping at [" << point.x() << "," << point.y() << "]";
    QProcess proc;
    proc.start(QString("adb shell input tap %1 %2").arg(point.x()).arg(point.y()));
    proc.waitForFinished(-1);
    if(!noDelay)
        delay(100);
    return;
}

bool ADBCommand::findAndClick(QString iconPath)
{
    LOG << "[ADBCommand]" << iconPath;
    QString screenImgPath = ADBCommand::screenShot();
    QPoint point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
    if(!point.isNull()){
        ADBCommand::tapScreen(point);
        return true;
    }else{
        screenImgPath = ADBCommand::screenShot();
        point = ImageProcessing::findImageOnImage(QDir::currentPath() + iconPath,screenImgPath);
        if(!point.isNull()){
            ADBCommand::tapScreen(point);
            return true;
        }else{
            return false;
        }
    }
}

void ADBCommand::wakeUpScreen()
{
        LOG << "[ADBCommand]";
        QProcess proc;
        proc.start("adb shell input keyevent KEYCODE_POWER");
        proc.waitForFinished(-1);
        delay(100);
}

void ADBCommand::clearCacheOfPackage(QString packagName)
{
    LOG << "[ADBCommand]" << packagName;
    QProcess proc;
    proc.start(QString("adb shell pm clear %1").arg(packagName));
    proc.waitForFinished(-1);
    LOG << proc.readAllStandardOutput();
}
