import QtQuick 2.9

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
}
