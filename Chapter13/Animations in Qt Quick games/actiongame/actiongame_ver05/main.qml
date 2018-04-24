import QtQuick 2.9

Image {
    id: root
    property int dayLength: 60000 // 1 minute
    source: "images/sky.png"

    Item {
        id: sun
        x: 140
        y: root.height - 170
        Rectangle {
            id: sunVisual
            width: 40
            height: width
            radius: width / 2
            color: "yellow"
            anchors.centerIn: parent

            SequentialAnimation on color {
                    ColorAnimation {
                        from: "red"
                        to: "yellow"
                        duration: 0.2 * dayLength / 2
                    }
                    PauseAnimation { duration: 2 * 0.8 * dayLength / 2 }
                    ColorAnimation {
                        to: "red"
                        duration: 0.2 * dayLength / 2
                    }
                    running: true
                }
        }
    }
    Image {
        source: "images/trees.png"
        x: -200
        anchors.bottom: parent.bottom
    }
    Image {
        source: "images/grass.png"
        anchors.bottom: parent.bottom
    }

    NumberAnimation {
            target: sun
            property: "x"
            from: 0
            to: root.width
            duration: dayLength
            running: true
    }
    SequentialAnimation {
        running: true
        NumberAnimation {
            target: sun
            property: "y"
            from: root.height + sunVisual.height
            to: root.height - 270
            duration: dayLength / 2
            easing.type: Easing.OutCubic
        }
        NumberAnimation {
            target: sun
            property: "y"
            to: root.height + sunVisual.height
            duration: dayLength / 2
            easing.type: Easing.InCubic
        }
    }
}
