import QtQuick 2.9

Item {
    id: player

    y: parent.height
    focus: true

    property bool walking: flags.rightPressed || flags.leftPressed
    readonly property bool jumping: jumpAnim.running
    property bool facingLeft: false

    QtObject {
        id: flags
        readonly property int speed: 100

        property bool rightPressed: false
        property bool leftPressed: false
        property bool upPressed: false

        onUpPressedChanged: {
            if (upPressed && !jumping) { jumpAnim.start() }
        }
        onRightPressedChanged: {
            recalculateDurations();
            if (rightPressed) { facingLeft = false }
        }

        onLeftPressedChanged: {
            recalculateDurations()
            if (leftPressed && !rightPressed) {
                facingLeft = true
            }
        }
    }
    Keys.onRightPressed: {
        if(event.isAutoRepeat) return;
        flags.rightPressed = true
    }
    Keys.onLeftPressed: {
        if(event.isAutoRepeat) return;
        flags.leftPressed = true
    }
    Keys.onUpPressed: {
        if(event.isAutoRepeat) return;
        flags.upPressed = true
    }
    Keys.onReleased: {
        if(event.isAutoRepeat) {
            return;
        }
        if (event.key === Qt.Key_Right) {
            flags.rightPressed = false;
        }
        if (event.key === Qt.Key_Left)  {
            flags.leftPressed = false;
        }
        if (event.key === Qt.Key_Up)    {
            flags.upPressed = false;
        }
    }

    function recalculateDurations() {
        xAnimRight.duration = (xAnimRight.to - x)*1000/flags.speed
        xAnimLeft.duration  = (x - xAnimLeft.to)*1000/flags.speed
    }
    NumberAnimation on x {
        id: xAnimRight
        running: !facingLeft && walking
        to: parent.width
    }
    NumberAnimation on x {
        id: xAnimLeft
        running: facingLeft && walking
        to: 0
    }

    SpriteSequence {
        id: sprite
        width: 80
        height: jumping ? 70 : 52
        interpolate: false
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        running: true

        Sprite {
            name: "still"
            source: "images/sprite.png"
            frameCount: 1
            frameWidth: 80; frameHeight: 52
            frameDuration: 100
            to: {"still": 1, "walking": 0, "jumping": 0}
        }
        Sprite {
            name: "walking"
            source: "images/sprite.png"
            frameX: 560; frameY: 0
            frameCount: 7
            frameWidth: 80; frameHeight: 52
            frameRate: 20
            to: {"walking": 1, "still": 0, "jumping": 0}
        }
        Sprite {
            name: "jumping"
            source: "images/sprite.png"
            frameX: 480; frameY: 52
            frameCount: 11
            frameWidth: 80; frameHeight: 70
            frameDuration: 50
            to: { "still" : 0, "walking": 0, "jumping": 1 }
        }

        transform: Scale {
            origin.x: sprite.width / 2
            xScale: player.facingLeft ? -1 : 1
        }
    }
    onWalkingChanged: {
        if(jumping) return
        if (walking) sprite.jumpTo("walking")
        else sprite.jumpTo("still")
    }

    SequentialAnimation on y {
        id: jumpAnim
        running: false
        loops: Animation.Infinite
        ScriptAction { script: sprite.jumpTo("jumping") }
        NumberAnimation {
            to: player.parent.height - 50; easing.type: Easing.OutQuad
            duration: 275
        }
        NumberAnimation {
            to: player.parent.height; easing.type: Easing.InQuad
            duration: 275
        }
        ScriptAction {
            script: if(!flags.upPressed) {
                        sprite.jumpTo(player.walking ? "walking" : "still");
                        jumpAnim.stop()
                    }
        }
    }
}
