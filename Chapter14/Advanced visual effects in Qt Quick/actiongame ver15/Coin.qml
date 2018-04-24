import QtQuick 2.9
import QtQuick.Particles 2.0

Item {
    id: coin

    Rectangle {
        id: coinVisual
        color: "yellow"
        border.color: Qt.darker(color)
        border.width: 2
        width: 30; height: width
        radius: width / 2
        anchors.centerIn: parent

        transform: Rotation {
            origin.x: coinVisual.width / 2
            origin.y: coinVisual.height / 2
            axis { x:0; y:1; z:0 }

            NumberAnimation on angle {
                from: 0; to: 360
                loops: Animation.Infinite
                duration: 1000
                running: true
            }
        }
        Text {
            color: coinVisual.border.color
            anchors.centerIn: parent
            text: "1"
        }
    }

    Emitter {
        id: emitter
        system: coinParticles
        emitRate: 0
        lifeSpan: 1500
        lifeSpanVariation: 100
        velocity: AngleDirection {
            angleVariation: 180
            magnitude: 10
        }
        acceleration: AngleDirection {
            angle: 270
            magnitude: 30
        }
    }

    SequentialAnimation {
        id: hitAnim
        running: false
        NumberAnimation {
            target: coin
            property: "opacity"
            from: 1; to: 0
            duration: 250
        }
        ScriptAction {
            script:coin.destroy()
        }
    }
    function hit() {
        emitter.burst(50)
        hitAnim.start()
    }
}
