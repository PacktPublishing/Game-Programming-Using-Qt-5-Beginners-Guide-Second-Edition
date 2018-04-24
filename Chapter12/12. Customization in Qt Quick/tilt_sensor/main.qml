import QtQuick 2.9
import QtQuick.Window 2.2
import QtSensors 5.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Text {
        anchors.centerIn: parent
        text: {
            if (!tiltSensor.reading) {
                return "No data";
            }
            var x = tiltSensor.reading.xRotation;
            var y = tiltSensor.reading.yRotation;
            return "X: " + Math.round(x) +
                   " Y: " + Math.round(y)
        }
    }
    TiltSensor {
        id: tiltSensor
        active: true
        onReadingChanged: {
            // process new reading
        }
    }
}
