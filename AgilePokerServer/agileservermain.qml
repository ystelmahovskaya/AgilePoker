import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 600
    height: 400

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: textUser
            }
            TextField {
                id: textPassword
            }
            Button {
                id: addUserButton
                text: qsTr("Add user")
                onClicked: {
                    webSocketServer.addNewUser()
                }
            }
        }
        ListView {
            id: usersListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: usersModel
            delegate: Rectangle {
                RowLayout {
                    anchors.fill: parent
                    Label {
                        text: username
                    }
                }
            }
        }
    }

}
