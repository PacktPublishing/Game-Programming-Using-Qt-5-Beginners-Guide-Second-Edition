import QtQuick 2.9

Item {
    id: clock

    property color color: "lightgray"

    property int hours: currentDate.getHours()
    property int minutes: currentDate.getMinutes()
    property int seconds: currentDate.getSeconds()
    property date currentDate: new Date()
    property alias running: timer.running

    Timer {
        id: timer
        repeat: true
        interval: 500
        running: true

        onTriggered: clock.currentDate = new Date()
    }

    Rectangle {
        id: plate

        anchors.centerIn: parent
        width: Math.min(clock.width, clock.height)
        height: width
        radius: width / 2
        color: clock.color
        border.color: Qt.darker(color)
        border.width: 2

        Repeater {
            model: 12

            Item {
                id: hourContainer

                property int hour: index
                height: plate.height / 2
                transformOrigin: Item.Bottom
                rotation: index * 30
                x: plate.width / 2
                y: 0

                Rectangle {
                    width: 2
                    height: (hour % 3 == 0) ? plate.height * 0.1 : plate.height * 0.05
                    color: plate.border.color
                    antialiasing: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 4
                }
            }
        }

        Needle {
            length: plate.height * 0.3
            color: "blue"
            value: clock.hours
            granularity: 12
        }
        Needle {
            length: plate.height * 0.4
            color: "darkgreen"
            value: clock.minutes
            granularity: 60
        }
        Needle {
            width: 1
            length: plate.height * 0.45
            color: "red"
            value: clock.seconds
            granularity: 60
        }

    }
}
