import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 6.2

Window {
    id: window
    visible: true
    color: "#222222"
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button_pair_tracker
        y: 66
        width: 164
        height: 24
        text: qsTr("Pair Trackers")
        anchors.horizontalCenter: parent.horizontalCenter
        flat: false
        onClicked: _gui.buttonClicked()
    }
}
