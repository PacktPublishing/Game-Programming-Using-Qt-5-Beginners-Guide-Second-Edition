import QtQuick 2.9
import QtQuick.Window 2.2
import QtPositioning 5.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Text {
        anchors.centerIn: parent
        text: {
            var pos = positionSource.position;
            var coordinate = pos.coordinate;
            return "latitude: " + coordinate.latitude +
              "\nlongitude: " + coordinate.longitude;
        }
    }   
    PositionSource {
        id: positionSource
        active: true
    }
}
