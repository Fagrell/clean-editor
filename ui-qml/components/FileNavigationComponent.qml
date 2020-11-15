import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Controls.Material 6.0
import CleanEditor 1.0
import "../styles"

Item {
    id: root

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
                    checked: (index === listView.currentIndex) ? true : false
                    checkable: true
                    anchors.fill: parent
                    text: filename + (fileNeedsSaving ? "*" : "")
                    ButtonGroup.group: openedFileButtonGroup
                    onClicked: mainController.fileNavigationController.fileOpenedClicked(fileId)
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

        ScrollView {
            id: scrollView
            anchors.fill: parent

            ListView {
                id: listView
                anchors.fill: parent
                model: documentsModel
                delegate: openedFilesDelegate
                focus: true
                highlightFollowsCurrentItem: true
                currentIndex: fileNavigationModel.selectedIndex
            }
        }
    }
}
