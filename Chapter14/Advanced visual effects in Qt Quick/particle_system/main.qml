import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Particles 2.0

Window {
    visible: true
    width: 360
    height: 360
    title: qsTr("Particle system")

    ParticleSystem {
        id: particleSystem
        anchors.fill: parent
        Emitter {
            anchors.centerIn: parent
            width: 50; height: 50
            emitRate: 50

            velocity: AngleDirection {
                angleVariation: 45
                angle: 180
                magnitude: 200
            }
        }
        ImageParticle {
            source: "star_white.png"
            colorVariation: 1
        }
    }
}
