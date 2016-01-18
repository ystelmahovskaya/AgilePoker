import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import Qt.WebSockets 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600
    property var numbers: ["0", "½", "1", "2", "3", "5", "8", "13", "20", "40", "100", "?", "\u2615", "\u221E"]

    property int selectedIndex: -1

    onSelectedIndexChanged: {
        grid.model = 1
    }

    WebSocket {
        id: webSocket
        active: false
        //url: "ws://127.0.0.1:2345"
        onStatusChanged: {
            if (status === WebSocket.Open) {
                console.log("Connected to server!!")
                sendTextMessage("Hello server")
            }
        }
    }

    Connections {
        target: searchServer
        onFoundServer: {
            webSocket.url = "ws://" + serverAddress + ":2345"
            webSocket.active = true
            console.log("found server at", serverAddress)
        }
    }

    Component.onCompleted: {
        searchServer.startSearch(2345);
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#00008b";
            }
            GradientStop {
                position: 0.23;
                color: "#4242c6";
            }
            GradientStop {
                position: 0.50;
                color: "#0000ff";
            }
            GradientStop {
                position: 1.00;
                color: "#808080";
            }
        }

//        Button {
//            anchors.top: parent.top
//            text: "Show!"
//            onClicked: {
//                grid.currentItem.showCard()
//            }
//        }

        GridView {
            id: grid
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            model: 14
            cellWidth: 100
            cellHeight: 150
            onCountChanged: {
                if (count == 1 && selectedIndex >= 0 && selectedIndex < numbers.length && currentItem != null) {
                    //console.log("currentitem", currentItem, selectedIndex, root.numbers[selectedIndex])
                    currentItem.fibbonachiNumber = root.numbers[selectedIndex]
                    currentItem.flipped = true
                    currentItem.isSelected = true
                    cellWidth = 200
                    cellHeight = 300
                    width = cellWidth
                    height = cellHeight
                }
            }

            delegate: Card {
                id: card
                width: grid.cellWidth
                height: grid.cellHeight
                fibbonachiNumber: numbers[index]
                angle: 180
                yAxis: 1
                onSelected: {
                    selectedIndex = index
                }
            }
        }
    }
}
