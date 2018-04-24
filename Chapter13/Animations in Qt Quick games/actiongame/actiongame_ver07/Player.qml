import QtQuick 2.9

Item {
  id: player
  
  y: parent.height
  focus: true
  
  Keys.onRightPressed: x = Math.min(x + 20, parent.width)
  Keys.onLeftPressed: x = Math.max(0, x - 20)
  Keys.onUpPressed: jump()

  function jump() { jumpAnim.start() }

  Image {
    source: "images/elephant.png"
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
  }
  Behavior on x { NumberAnimation { duration: 100 } }
  SequentialAnimation on y {
    id: jumpAnim
    running: false
    NumberAnimation { to: player.parent.height - 50; easing.type: Easing.OutQuad }
    NumberAnimation { to: player.parent.height; easing.type: Easing.InQuad }
  }
}
