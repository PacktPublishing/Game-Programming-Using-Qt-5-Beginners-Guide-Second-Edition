import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        id: layout
        anchors.fill: parent
    }
    function addCircles(circleComponent) {
        ["red", "yellow", "green"].forEach(function(color) {
            var circle = circleComponent.createObject(layout);
            circle.color = color;
            circle.Layout.alignment = Qt.AlignCenter;
        });
    }
    Component.onCompleted: {
        var circleComponent = Qt.createComponent("Circle.qml");
        if(circleComponent.status === Component.Ready) {
            addCircles(circleComponent);
        } else {
            circleComponent.statusChanged.connect(function() {
                if(circleComponent.status === Component.Ready) {
                    addCircles(circleComponent);
                }
            });
        }
    }
}
