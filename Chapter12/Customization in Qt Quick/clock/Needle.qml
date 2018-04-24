import QtQuick 2.9

Rectangle {
    id: root

    property int value: 0
    property int granularity: 60
    property alias length: root.height

    width: 2
    height: parent.height / 2
    radius: width / 2
    antialiasing: true
    anchors.bottom: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    transformOrigin: Item.Bottom
    rotation: 360 / granularity * (value % granularity)
}
