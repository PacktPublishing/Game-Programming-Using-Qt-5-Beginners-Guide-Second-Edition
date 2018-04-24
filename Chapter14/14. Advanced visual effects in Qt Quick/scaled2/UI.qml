import QtQuick 2.0

Rectangle {
    width: 300
    height: 300

    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightsteelblue" }
        GradientStop { position: 1.0; color: "blue" }
    }
}
