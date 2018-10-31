import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Item {
    id: root
    signal fileSelected(string name, string path)

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
        anchors.fill: parent
        color: "#A9A9A9"

        ButtonGroup {
            id: openedFileButtonGroup
        }

        Component {
            id: openedFilesDelegate
            Item {
                width: openedFilesBar.width
                height: 40

                Button {
                    id: button
                    checkable: true
                    anchors.fill: parent
                    text: name
                    ButtonGroup.group: openedFileButtonGroup
                    onClicked: root.fileSelected(name, name)
                    background: Rectangle {
                       color: button.checked ? "#696969" : "#C0C0C0"
                       border.width: 0
                       radius: 0
                   }
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

}
