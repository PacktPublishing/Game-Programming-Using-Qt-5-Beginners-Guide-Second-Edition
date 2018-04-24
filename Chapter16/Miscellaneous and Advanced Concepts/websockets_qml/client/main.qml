import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebSockets 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client")

    WebSocket {
        id: socket
        url: "ws://localhost:8080"
        active: true
        onStatusChanged: {
            console.log("Client status changed: ", status);
            if(status == WebSocket.Open) {
                sendTextMessage("Hello!");
            }
        }
        onTextMessageReceived: {
            console.log("Client received message: ", message);
        }
    }
}
