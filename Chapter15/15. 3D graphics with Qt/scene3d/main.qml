
import QtQuick 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Scene3D 2.0

Window {
    visible: true
    Button {
        id: button1
        text: "button1"
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }
    }
    Scene3D {
        focus: true
        anchors {
            top: button1.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            margins: 10
        }
        aspects: ["input", "logic"]
        My3DScene {}
    }
}
