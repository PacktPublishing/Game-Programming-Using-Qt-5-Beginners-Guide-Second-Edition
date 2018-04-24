import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image {
        id: image
        anchors.centerIn: parent
        source: "qrc:/wilanow.jpg"
    }

    PinchArea {
        anchors.fill: parent
        pinch {
            target: image
            minimumScale: 0.2
            maximumScale: 2.0
            minimumRotation: -90
            maximumRotation: 90
        }
    }
}
