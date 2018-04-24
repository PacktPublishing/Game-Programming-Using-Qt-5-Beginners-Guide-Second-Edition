import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: circle
        width: 60; height: width
        radius: width/2
        color: "red"

        MouseArea {
            anchors.fill: parent
            drag.target: circle
        }
    }
}
