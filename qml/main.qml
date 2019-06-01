import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import "unit"

Window {
    id: root
    visible: true
    width: 480
    height: 640
    title: qsTr("Auto register")
    color:  "#fbfbfb"

    /* ----------------- Properties ----------------- */

    property var languageModel: ["Vietnamese"]

    /* ----------------- Function ----------------- */

    function getCurrentNameLang(){
        for(var i =0 ; i < languageModel.length; i++){
            if(languageModel[i] === AppModel.nameLang){
                return i
            }
        }
        return 0
    }

    TextField{
        id: deviceId
        width: parent.width * 3 /5
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    Text{
        anchors.verticalCenter: deviceId.verticalCenter
        anchors.right: deviceId.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Device ID"
    }

    TextField{
        id: deviceName
        width: deviceId.width
        height: deviceId.height
        anchors.horizontalCenter: deviceId.horizontalCenter
        anchors.top: deviceId.bottom
        anchors.topMargin: 10
        color: "black"
    }

    ComboBox {
        currentIndex: getCurrentNameLang()
        width: deviceId.width
        height: deviceId.height
        anchors.horizontalCenter: deviceId.horizontalCenter
        anchors.top: deviceId.bottom
        anchors.topMargin: 10
        model: languageModel
        onCurrentIndexChanged: AppModel.nameLang = languageModel[currentIndex]

    }

    Text{
        anchors.verticalCenter: deviceName.verticalCenter
        anchors.right: deviceName.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Name"
    }

    CheckBoxItem {
        id: saveToLocal
        width: 20
        height: 20
        anchors.top: deviceName.bottom
        anchors.topMargin: 10
        anchors.right: deviceName.horizontalCenter
        isChecked: AppModel.saveToLocal
        onCheckStateChanged: {
            if(checkState == Qt.Checked){
                AppModel.saveToLocal = true
            }else{
                AppModel.saveToLocal = false
            }
        }
    }

    Text{
        anchors.verticalCenter: saveToLocal.verticalCenter
        anchors.right: saveToLocal.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Save Local"
    }

    CheckBoxItem{
        id: saveToServer
        width: 20
        height: 20
        anchors.top: deviceName.bottom
        anchors.topMargin: 10
        anchors.right: deviceName.right
        isChecked: AppModel.saveToServer
        onCheckStateChanged: {
            if(checkState == Qt.Checked){
                AppModel.saveToServer = true
            }else{
                AppModel.saveToServer = false
            }
        }
    }

    Text{
        anchors.verticalCenter: saveToServer.verticalCenter
        anchors.right: saveToServer.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Save Sever"
    }

    TextField{
        id: tokenFieldId
        width: deviceId.width
        height: deviceId.height
        anchors.horizontalCenter: deviceId.horizontalCenter
        anchors.top: saveToLocal.bottom
        anchors.topMargin: 10
        color: "black"
    }

    Text{
        anchors.verticalCenter: tokenFieldId.verticalCenter
        anchors.right: deviceId.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Token"
    }

    CheckBoxItem {
        id: regFacebookOption
        width: 20
        height: 20
        anchors.left: tokenFieldId.left
        anchors.top: tokenFieldId.bottom
        anchors.topMargin: 10
        isChecked: AppModel.regFacebookOption
        onCheckStateChanged: {
            if(checkState == Qt.Checked){
                AppModel.regFacebookOption = true
            }else{
                AppModel.regFacebookOption = false
            }
        }
    }

    Text{
        anchors.verticalCenter: regFacebookOption.verticalCenter
        anchors.right: regFacebookOption.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Reg Facebook"
    }

    CheckBoxItem {
        id: recoveryEmail
        enabled: AppModel.regFacebookOption
        width: 20
        height: 20
        anchors.left: regFacebookOption.left
        anchors.top: regFacebookOption.bottom
        anchors.topMargin: 10
        isChecked: AppModel.recoveryEmail
        onCheckStateChanged: {
            if(checkState == Qt.Checked){
                AppModel.recoveryEmail = true
            }else{
                AppModel.recoveryEmail = false
            }
        }
    }

    Text{
        anchors.verticalCenter: recoveryEmail.verticalCenter
        anchors.right: recoveryEmail.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Recover Email"
    }

    CheckBoxItem{
        id: useKeyboard
        enabled: AppModel.regFacebookOption
        width: 20
        height: 20
        anchors.left: deviceName.left
        anchors.top: recoveryEmail.bottom
        anchors.topMargin: 10
        isChecked: AppModel.useKeyboard
        onCheckStateChanged: {
            if(checkState == Qt.Checked){
                AppModel.useKeyboard = true
            }else{
                AppModel.useKeyboard = false
            }
        }
    }

    Text{
        anchors.verticalCenter: useKeyboard.verticalCenter
        anchors.right: useKeyboard.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Use KeyBoard"
    }

    Rectangle{
        id: wipeDataArea
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: useKeyboard.bottom
        anchors.topMargin: 10
        anchors.bottom: startBtn.top
        anchors.bottomMargin: 10
        border.width: 1
        border.color: "black"
        clip: true

        ListView{
            model: AppModel.appDataList
            boundsBehavior: Flickable.StopAtBounds
            width: parent.width
            height: parent.height - 2
            anchors.centerIn: parent
            clip: true
            delegate: Item {
                id: dlg
                anchors.left: parent.left
                width: parent.width
                height: 30
                CheckBox{
                    id: checkbox
                    width: parent.height
                    height: parent.height
                    indicator.width: 20
                    indicator.height: 20
                    checkState: modelData.checkedState? Qt.Checked : Qt.Unchecked
                    onCheckStateChanged: {
                        if(checkState == Qt.Checked){
                            modelData.checkedState = true
                        }else{
                            modelData.checkedState = false
                        }
                    }
                }

                Text{
                    anchors.verticalCenter: checkbox.verticalCenter
                    anchors.left: checkbox.right
                    text: modelData.packageName
                }
            }
        }
    }


    Button{
        id: startBtn
        width: 100
        height: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: closeBtn.left
        anchors.rightMargin: 20
        text: "Start"
        onReleased: {
            enableAre.visible = true
            root.showMinimized()
            AppModel.saveSettingConfig()
            AppModel.startProgram(tokenFieldId.text)
        }
    }

    Rectangle{
        id: enableAre
        visible: false
        anchors.fill: parent
        color: "grey"
        opacity: 0.1
        MouseArea{
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }

    Button{
        id: closeBtn
        width: 100
        height: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: "Close"
        onReleased: {
            AppModel.closeProgram(tokenFieldId.text)
        }
    }
}



