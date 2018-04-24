import QtQuick 2.9
import QtQuick.Window 2.3
import CarInfo 1.0

Window {
    visible: true
    width: backgroundImage.width
    height: backgroundImage.height

    Image {
        id: backgroundImage
        source: "qrc:/dashboard.png"



        CarInfo {
            id: carData
            visible: true
            engine.gear: 3
        }

        Item {
            id: leftContainer
            property real value: carData.engine.rpm / 1000

            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -550
            width: 400
            height: 400

            function calculatePosition(angle, radius) {
                if(radius === undefined) {
                    radius = width / 2 * 0.8;
                }
                var a = angle * Math.PI / 180;
                var px = width / 2 + radius * Math.cos(a);
                var py = width / 2 + radius * Math.sin(a);
                return Qt.point(px, py);
            }

            Repeater {
                model: 7

                Item {
                    property point pt: leftContainer.calculatePosition(120+index*35)
                    x: pt.x
                    y: pt.y
                    Label {
                        anchors.centerIn: parent
                        text: index
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 40
                text: "RPM\n[x1000]"
                horizontalAlignment: Text.AlignHCenter
                color: "#aaa"
                font.pixelSize: 16
            }

            Item {
                id: gearContainer
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 10
                anchors.verticalCenterOffset: -10

                Text {
                    id: gear
                    property int value: carData.engine.gear
                    property var gears: [
                        "R", "N", "1<sup>st</sup>", "2<sup>nd</sup>",
                        "3<sup>rd</sup>", "4<sup>th</sup>", "5<sup>th</sup>"
                    ]
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    text: gears[value + 1]
                    color: "yellow"
                    font.pixelSize: 32
                    textFormat: Text.RichText
                }
            }

            Needle {
                anchors.centerIn: parent
                length: parent.width * 0.35
                rotation: 120 + 90 + (leftContainer.value * 35)
            }

        }
        Item {
            id: middleContainer
            property int value: carData.speed
            anchors.centerIn: parent
            width: 700
            height: width

            function calculatePosition(angle, radius) {
                if(radius === undefined) {
                    radius = width / 2 * 0.8;
                }
                var a = angle * Math.PI / 180;
                var px = width / 2 + radius * Math.cos(a);
                var py = width / 2 + radius * Math.sin(a);
                return Qt.point(px, py);
            }

            Repeater {
                model: 24 / 2

                Item {
                    property point pt:
                        middleContainer.calculatePosition(120 + index * 12 * 2)
                    x: pt.x; y: pt.y
                    Label {
                        anchors.centerIn: parent
                        text: index * 20
                    }
                }
            }
            Repeater {
                model: 120 - 4

                Item {
                    property point pt: middleContainer.calculatePosition(
                        120 + index * 1.2 * 2, middleContainer.width * 0.35)
                    x: pt.x
                    y: pt.y
                    Rectangle {
                        width: 2
                        height: index % 5 ? 5 : 10
                        color: "white"
                        rotation: 90 + 120 + index * 1.2 * 2
                        anchors.centerIn: parent
                        antialiasing: true
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 40
                text: "SPEED\n[kph]"
                horizontalAlignment: Text.AlignHCenter
                color: "#aaa"
                font.pixelSize: 16
            }

            Needle {
                anchors.centerIn: parent
                length: parent.width * 0.35
                size: 4
                rotation: 210 + (middleContainer.value * 1.2)
                color: "yellow"
            }

        }
        Item {
            id: rightContainer

            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 525
            width: 400
            height: 400

            Rectangle {
                id: digitalDisplay
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter

                border.color: "white"
                border.width: 1
                radius: 10
                width: 350
                height: 300
                color: "transparent"
                Item {
                    anchors.fill: parent
                    anchors.margins: 10
                    Label {
                        id: dateLabel
                        text: Qt.formatDate(new Date)
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Grid {
                        id: topGrid
                        anchors.top: dateLabel.bottom
                        anchors.topMargin: 15
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: bottomGrid.top
                        anchors.bottomMargin: 15
                        columns: 2
                        spacing: 5
                        Label {
                            text: "Temperature:"
                            width: parent.width/2
                        }
                        Label {
                            text: "+17°C"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }
                        Label {
                            text: "Humidity:"
                            width: parent.width / 2
                        }
                        Label {
                            text: "68.4%"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }

                    }
                    Grid {
                        id: bottomGrid
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 15
                        Label {
                            text: "Distance:"
                            width: parent.width / 2
                        }
                        Label {
                            text: carData.distance+" km"
                            horizontalAlignment: Text.AlignRight
                            width: parent.width / 2 - 5
                        }
                    }
                }
            }
            Row {
                anchors.top: digitalDisplay.bottom
                anchors.topMargin: 10
                anchors.left: digitalDisplay.left
                anchors.right: digitalDisplay.right
                spacing: 10

                Label {
                    text: "ABS"
                    color: "#222"
                }
                Label {
                    text: "ESP"
                    color: "#da0"
                }
                Label {
                    text: "BRK"
                    color: "#222"
                }

                Label {
                    text: "CHECK"
                    color: "#222"
                }
            }
        }
    }
}
