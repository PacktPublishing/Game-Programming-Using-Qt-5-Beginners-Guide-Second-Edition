import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Text {
        id: button
        text: qsTr("Play");
        anchors.centerIn: parent
    }
    Audio {
        id: music
        source: "example.ogg"
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            if (music.playbackState == Audio.StoppedState) {
                music.play();
                button.text = qsTr("Stop");
            } else {
                music.stop();
                button.text = qsTr("Play");
            }
        }
    }
}
