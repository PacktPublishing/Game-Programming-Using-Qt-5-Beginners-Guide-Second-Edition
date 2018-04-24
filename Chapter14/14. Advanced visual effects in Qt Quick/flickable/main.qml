import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Flickable {
        id: uiFlickable
        anchors.centerIn: parent
        contentWidth: ui.width
        contentHeight: ui.height

        width: parent.width >= contentWidth ?
               contentWidth : parent.width
        height: parent.height >= contentHeight ?
                contentHeight : parent.height

        UI {
            id: ui
        }
    }
}
