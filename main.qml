import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 800
    height: 600
    property var numbers: ["0", "½", "1", "2", "3", "5", "8", "13", "20", "40", "100", "?", "coffee", "infinite"]


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

        GridView {
            id: grid
            anchors.fill: parent
            model: 14
            cellWidth: 100
            cellHeight: 150
            delegate: Card {
                id: card
                width: grid.cellWidth
                height: grid.cellHeight
                fibbonachiNumber: numbers[index]
                angle: 180
                yAxis: 1
            }
        }
    }
}
