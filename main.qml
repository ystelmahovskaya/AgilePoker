import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 800
    height: 600
    property var numbers: ["0", "½", "1", "2", "3", "5", "8", "13", "20", "40", "100", "?", "coffee", "infinite"]

    GridView {
        id: grid
        anchors.fill: parent
        model: 14
        cellWidth: 100
        cellHeight: 150
        delegate: Card {
            id: card
            width: grid.cellWidth; height: grid.cellHeight
            fibbonachiNumber: numbers[index]
            angle: 180
            yAxis: 1
        }
    }
}
