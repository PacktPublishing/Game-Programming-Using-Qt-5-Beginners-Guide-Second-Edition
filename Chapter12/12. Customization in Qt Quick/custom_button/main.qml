import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button
        anchors.centerIn: parent

        onClicked: console.log("Clicked!")

        onPressedChanged: {
          console.log("The button is currently " +
                      (pressed ? "" : "not ") + "pressed")
        }
    }
}
