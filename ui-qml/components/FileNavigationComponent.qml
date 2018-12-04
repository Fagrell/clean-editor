import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import CleanEditor 1.0
import "../styles"

Item {
    id: root
    signal fileSelected(DocumentHandler document)

    Rectangle {
        id: openedFilesBar
        anchors.fill: parent
        color: Style.fileNavigationBackgroundColor

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
                               return Style.fileNavigationSelectedColor
                           }
                           if (button.hovered) {
                               return Style.fileNavigationHoveredColor
                           }

                           return Style.fileNavigationBackgroundColor
                       }
                       border.width: 0
                       radius: 0
                    }
                    contentItem: Text {
                        text: button.text
                        verticalAlignment: Text.AlignVCenter
                        color: Style.fileNavigationTextColor
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
