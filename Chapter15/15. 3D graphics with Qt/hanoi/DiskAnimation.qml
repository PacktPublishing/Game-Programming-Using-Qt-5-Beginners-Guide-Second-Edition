import QtQuick 2.10

SequentialAnimation {
    id: rootAnimation
    property variant target: null
    property vector3d rod1Pos
    property vector3d rod2Pos
    property int startY
    property int finalY

    property int maxY: 12

    Vector3dAnimation {
        target: rootAnimation.target
        property: "pos"
        to: Qt.vector3d(rod1Pos.x, maxY, rod1Pos.z)
        duration: 30 * (maxY - startY)

    }
    Vector3dAnimation {
        target: rootAnimation.target
        property: "pos"
        to: Qt.vector3d(rod2Pos.x, maxY, rod2Pos.z)
        duration: 400
    }
    Vector3dAnimation {
        target: rootAnimation.target
        property: "pos"
        to: Qt.vector3d(rod2Pos.x, finalY, rod2Pos.z)
        duration: 30 * (maxY - finalY)
    }
}

