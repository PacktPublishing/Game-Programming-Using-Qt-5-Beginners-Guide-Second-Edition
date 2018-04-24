import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextField {
        id: textField
        text: "Edit me"
        anchors {
            top: parent.top
            left: parent.left
        }
    }
    Label {
        text: {
            var x = textField.text;
            return "(" + x + ")";
        }
        anchors {
            top: textField.bottom
            topMargin: 20
            left: parent.left
        }
    }
}
