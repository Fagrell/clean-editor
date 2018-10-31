import QtQuick 2.11
import QtQuick.Window 2.4
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client Management")

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");

    ListModel {
        id: openedFilesModel
        ListElement {
            name: "Example.qml"
        }
        ListElement {
            name: "Example2.qml"
        }
        ListElement {
            name: "Example3.qml"
        }
    }

    Rectangle {
        id: openedFilesBar
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: 200
        color: "#A9A9A9"

        ButtonGroup { id: openedFileButtonGroup }

        Component {
            id: openedFilesDelegate
            Item {
                width: openedFilesBar.width; height: 40
                Button {
                    checkable: true
                    anchors.fill: parent
                    text: name
                    ButtonGroup.group: openedFileButtonGroup
                    onClicked: contentFrame.replace("qrc:/views/OpenedFileView.qml")
                }
            }
        }

        ListView {
            anchors.fill: parent
            model: openedFilesModel
            delegate: openedFilesDelegate
            focus: true
        }
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: openedFilesBar.right
        }
        initialItem: "qrc:/views/SplashView.qml"
        clip: true
    }
}
