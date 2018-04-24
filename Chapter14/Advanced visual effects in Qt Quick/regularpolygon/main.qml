import QtQuick 2.9
import QtQuick.Window 2.3
import RegularPolygon 1.0
import QtQuick.Controls 1.2

Window {
    width: 600
    height: 600
    visible: true

    Rectangle {
        anchors.fill: parent

        RegularPolygon {
            id: poly
            anchors {
                fill: parent
                bottomMargin: 20
            }
            vertices: slider.value
            color: "blue"
        }
        Row {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            spacing: 5

            Repeater {
                model: ["red", "blue", "green"]

                Rectangle {
                    width: 20
                    height: width
                    color: modelData
                    MouseArea {
                        anchors.fill: parent
                        onClicked: poly.color = color
                    }
                }
            }

            Slider {
                id: slider
                minimumValue: 3
                maximumValue: 100
                width: 100
                value: 6
            }

        }

    }
}
