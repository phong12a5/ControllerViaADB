import QtQuick 2.0
import QtQuick.Controls 2.0

CheckBox {
    id: root
    width: 20
    height: 20

    /* ----------------- Properties ----------------- */

    property bool isChecked: false

    indicator.width: width
    indicator.height: height
    indicator.anchors.centerIn: indicator.parent
    checkState: isChecked ? Qt.Checked : Qt.Unchecked
}
