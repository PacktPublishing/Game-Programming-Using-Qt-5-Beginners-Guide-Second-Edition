import QtQuick 2.9

Rectangle {
    id: view

    width: 600
    height: 380

    ParallaxScene {
        id: scene
        width: 1500
        height: 380
        anchors.bottom: parent.bottom
        currentPos: player.x

        ParallaxLayer {
            factor: 7.5
            width: sky.width; height: sky.height
            anchors.bottom: parent.bottom

            Image {
                id: sky
                property int dayLength: 60000 // 1 minute
                source: "images/sky.png"
                Item {
                    id: sun
                    x: 140
                    y: sky.height - 170
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
                                duration: 0.2 * sky.dayLength / 2
                            }
                            PauseAnimation { duration: 2 * 0.8 * sky.dayLength / 2 }
                            ColorAnimation {
                                to: "red"
                                duration: 0.2 * sky.dayLength / 2
                            }
                            running: true
                        }
                    }
                    SequentialAnimation on scale {
                        NumberAnimation {
                            from: 1.6; to: 0.8
                            duration: sky.dayLength / 2
                            easing.type: Easing.OutCubic
                        }
                        NumberAnimation {
                            from: 0.8; to: 1.6
                            duration: sky.dayLength / 2
                            easing.type: Easing.InCubic
                        }
                    }
                }
            }

            NumberAnimation {
                target: sun
                property: "x"
                from: 0
                to: sky.width
                duration: sky.dayLength
                running: true
            }
            SequentialAnimation {
                running: true
                NumberAnimation {
                    target: sun
                    property: "y"
                    from: sky.height + sunVisual.height
                    to: sky.height - 270
                    duration: sky.dayLength / 2
                    easing.type: Easing.OutCubic
                }
                NumberAnimation {
                    target: sun
                    property: "y"
                    to: sky.height + sunVisual.height
                    duration: sky.dayLength / 2
                    easing.type: Easing.InCubic
                }
            }
        }
        ParallaxLayer {
            factor: 2.5
            width: trees.width; height: trees.height
            anchors.bottom: parent.bottom
            Image { id: trees; source: "images/trees.png" }
        }
        ParallaxLayer {
            factor: 0
            width: grass.width; height: grass.height
            anchors.bottom: parent.bottom
            Image { id: grass; source: "images/grass.png" }

        }

        Player {
            id: player
            x: 40
        }

        Component {
            id: coinGenerator
            Coin {}
        }

        Timer {
            id: coinTimer
            interval: 1000
            repeat: true
            running: true

            onTriggered: {
                var cx = Math.floor(Math.random() * scene.width)
                var cy = Math.floor(Math.random() * scene.height / 3) + scene.height / 2
                coinGenerator.createObject(scene, { x: cx, y: cy});
            }
        }
    }
}

