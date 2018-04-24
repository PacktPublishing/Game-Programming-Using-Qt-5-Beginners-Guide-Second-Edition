import QtQuick 2.9

Item {
    property int diameter: 20
    property alias color: rect.color
    property alias border: rect.border

    implicitWidth: diameter
    implicitHeight: diameter

    Rectangle {
        id: rect
        width: radius
        height: radius
        radius: diameter / 2
        anchors.centerIn: parent
    }
}
