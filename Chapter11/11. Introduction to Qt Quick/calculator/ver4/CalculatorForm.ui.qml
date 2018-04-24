import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 400
    height: 400
    property alias operationFactorial: operationFactorial
    property alias reset: reset
    property alias result: result
    property alias argument2: argument2
    property alias operationMultiply: operationMultiply
    property alias operationAdd: operationAdd
    property alias argument1: argument1

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        TextField {
            id: argument1
            text: qsTr("0")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RadioButton {
                id: operationAdd
                text: qsTr("+")
                checked: true
            }

            RadioButton {
                id: operationMultiply
                text: qsTr("×")
            }

            RadioButton {
                id: operationFactorial
                text: qsTr("!")
            }
        }

        TextField {
            id: argument2
            text: qsTr("0")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Label {
            id: equalSign
            text: qsTr("=")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Label {
            id: result
            text: argument1.text + argument2.text
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: reset
            text: qsTr("Reset")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
    states: [
        State {
            name: "single_argument"

            PropertyChanges {
                target: argument2
                opacity: 0
            }
        }
    ]
}
