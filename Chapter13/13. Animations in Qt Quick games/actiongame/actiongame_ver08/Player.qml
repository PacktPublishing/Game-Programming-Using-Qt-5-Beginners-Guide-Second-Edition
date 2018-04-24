import QtQuick 2.9

Item {
  id: player

  y: parent.height
  focus: true

  QtObject {
      id: flags
      readonly property int speed: 100
      property bool rightPressed: false
      property bool leftPressed: false
      property bool upPressed: false

      onRightPressedChanged: recalculateDurations()
      onLeftPressedChanged: recalculateDurations()
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
        if(event.isAutoRepeat) return
        if (event.key === Qt.Key_Right) { flags.rightPressed = false }
        if (event.key === Qt.Key_Left)  { flags.leftPressed = false }
        if (event.key === Qt.Key_Up)    { flags.upPressed = false }
    }

    function recalculateDurations() {
      xAnimRight.duration = (xAnimRight.to - x)*1000/flags.speed
      xAnimLeft.duration  = (x - xAnimLeft.to)*1000/flags.speed
    }
    NumberAnimation on x {
      id: xAnimRight
      running: flags.rightPressed
      to: parent.width
    }
    NumberAnimation on x {
      id: xAnimLeft
      running: flags.leftPressed && !flags.rightPressed
      to: 0
    }

  Image {
    source: "images/elephant.png"
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
  }
  Behavior on x { NumberAnimation { duration: 100 } }
  SequentialAnimation on y {
    id: jumpAnim
    running: flags.upPressed
    loops: Animation.Infinite
    alwaysRunToEnd: true
    NumberAnimation { to: player.parent.height - 50; easing.type: Easing.OutQuad }
    NumberAnimation { to: player.parent.height; easing.type: Easing.InQuad }
  }
}
