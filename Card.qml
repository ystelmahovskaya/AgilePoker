import QtQuick 2.0

Item {
    id: root
    property string fibbonachiNumber: ""

    property bool flipped: false
    property bool isSelected: false
    property int xAxis: 0
    property int yAxis: 0
    property int angle: 0
    signal selected()

    function showCard() {
        flipped = false
    }

    Flipable {
        anchors.centerIn: parent
        width: root.width - 4
        height: root.height - 4
        front: Rectangle {
            color: "white"
            border.color: "black"
            border.width: 2
            radius: 5
            anchors.fill: parent
            Text {
                text: fibbonachiNumber
                anchors.centerIn: parent
                color: "black"
                font.bold: true
                font.pixelSize: root.height/3
            }
        }
        back: Image {
            source: "back.png"
            anchors.fill: parent
        }

        state: "spina"

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                if (!isSelected) {
                    root.flipped = !root.flipped
                    root.selected()
                }
            }
        }

        transform: Rotation {
            id: rotation
            origin.x: root.width / 2; origin.y: root.height / 2
            axis.x: root.xAxis; axis.y: root.yAxis; axis.z: 0
        }

        states: State {
            name: "spina"; when: root.flipped
            PropertyChanges { target: rotation; angle: root.angle }
        }

        transitions: Transition {
            ParallelAnimation {
                NumberAnimation { target: rotation; properties: "angle"; duration: 600 }
                SequentialAnimation {
                    NumberAnimation { target: root; property: "scale"; to: 0.75; duration: 300 }
                    NumberAnimation { target: root; property: "scale"; to: 1.0; duration: 300 }
                }
            }
        }
    }
}
