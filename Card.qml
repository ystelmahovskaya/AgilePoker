import QtQuick 2.0

Item {
    id: root
    property string fibbonachiNumber: ""

    property bool flipped: true
    property int xAxis: 0
    property int yAxis: 0
    property int angle: 0

    Flipable {
        anchors.centerIn: parent
        width: root.width - 4
        height: root.height - 4
        front: Rectangle {
            color: "green"
            border.color: "black"
            border.width: 2
            radius: 5
            anchors.fill: parent
            Text {
                text: fibbonachiNumber
                anchors.centerIn: parent
                color: "black"
                font.bold: true
                font.pixelSize: 32
            }
        }
        back: Image {
            source: "back.png"
            anchors.fill: parent
        }

        state: "spina"

        MouseArea { anchors.fill: parent; onClicked: root.flipped = !root.flipped }

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
