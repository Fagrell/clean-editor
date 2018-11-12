import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import CleanEditor 1.0

Item {
    id: root
    signal fileSelected(DocumentHandler document)

    Rectangle {
        id: openedFilesBar
        anchors.fill: parent
        color: "#161161"

        ButtonGroup {
            id: openedFileButtonGroup
        }

        Component {
            id: openedFilesDelegate

            Item {
                width: openedFilesBar.width
                height: 25

                Button {
                    id: button
                    checkable: true
                    anchors.fill: parent
                    text: document.fileName + (document.contentUpdated ? "*" : "")
                    ButtonGroup.group: openedFileButtonGroup
                    onClicked: root.fileSelected(document)
                    background: Rectangle {
                       color: {
                           if (button.checked) {
                               return "#223D6B";
                           }
                           if (button.hovered) {
                               return "#1d195e";
                           }

                           return "#161161";
                       }
                       border.width: 0
                       radius: 0
                    }
                    contentItem: Text {
                        text: button.text
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                    }
                }
            }
        }

        ListView {
            anchors.fill: parent
            model: documentsModel
            delegate: openedFilesDelegate
            focus: true
        }
    }

}
