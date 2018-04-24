import QtQuick 2.9
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Badge {
        id: importantBadge
        anchors.centerIn: parent
    }
    Glow {
        source: importantBadge
        anchors.fill: source
        samples: 64
        color: "red"

        SequentialAnimation on radius {
            loops: Animation.Infinite
            running: true

            NumberAnimation { from: 0; to: 30; duration: 500 }
            PauseAnimation { duration: 100 }
            NumberAnimation { from: 30; to: 0; duration: 500 }
            PauseAnimation { duration: 1000 }
        }
    }
}
