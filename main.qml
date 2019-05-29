import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    id: root
    visible: true
    width: 480
    height: 640
    title: qsTr("Auto register")
    color:  "#fbfbfb"

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

    Text{
        anchors.verticalCenter: deviceName.verticalCenter
        anchors.right: deviceName.left
        anchors.rightMargin: 10
        width: contentWidth
        horizontalAlignment: Text.AlignRight
        text: "Device Name"
    }

    CheckBox{
        id: saveToLocal
        width: 20
        height: 20
        anchors.left: deviceName.left
        anchors.top: deviceName.bottom
        anchors.topMargin: 10
        indicator.width: 20
        indicator.height: 20
        indicator.anchors.centerIn: indicator.parent
        checkState: AppModel.saveToLocal? Qt.Checked : Qt.Unchecked
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

    CheckBox{
        id: saveToServer
        width: 20
        height: 20
        anchors.left: deviceName.left
        anchors.top: saveToLocal.bottom
        anchors.topMargin: 10
        indicator.width: 20
        indicator.height: 20
        indicator.anchors.centerIn: indicator.parent
        checkState: AppModel.saveToServer? Qt.Checked : Qt.Unchecked
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

    CheckBox{
        id: useKeyboard
        width: 20
        height: 20
        anchors.left: deviceName.left
        anchors.top: saveToServer.bottom
        anchors.topMargin: 10
        indicator.width: 20
        indicator.height: 20
        indicator.anchors.centerIn: indicator.parent
        checkState: AppModel.useKeyboard? Qt.Checked : Qt.Unchecked
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
            AppModel.saveSettingConfig()
            AppModel.startProgram()
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
        text: "Start"
        onReleased: {
            AppModel.closeProgram()
        }
    }
}



