import QtQuick 2.4
import QtQuick.Controls 2.2

Item {
    id: item1
    width: 400
    height: 400

    TextField {
        id: argument1
        x: 91
        text: qsTr("0")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
    }

    TextField {
        id: argument2
        x: 111
        text: qsTr("0")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: operationAdd.bottom
        anchors.topMargin: 20
    }

    RadioButton {
        id: operationAdd
        x: 52
        text: qsTr("+")
        anchors.top: argument1.bottom
        anchors.topMargin: 20
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 10
        checked: true
    }

    RadioButton {
        id: operationMultiply
        text: qsTr("×")
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: 10
        anchors.top: argument1.bottom
        anchors.topMargin: 20
    }

    Button {
        id: reset
        x: 141
        text: qsTr("Reset")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: result.bottom
        anchors.topMargin: 20
    }

    Label {
        id: equalSign
        x: 170
        text: qsTr("=")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: argument2.bottom
        anchors.topMargin: 20
    }

    Label {
        id: result
        x: 170
        text: qsTr("Label")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: equalSign.bottom
        anchors.topMargin: 20
    }
}
