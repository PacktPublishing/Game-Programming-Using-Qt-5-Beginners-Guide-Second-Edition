import QtQuick 2.9
import QtQuick.Window 2.2
import QtWebSockets 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Server")


    WebSocketServer {
        id: socketServer
        listen: true
        port: 8080
        onClientConnected: {
            webSocket.onTextMessageReceived.connect(function(message) {
                console.log("Server received message: ", message);
                webSocket.sendTextMessage("Server says 'Hello!'");
            });
        }
    }
}
