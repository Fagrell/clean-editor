import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import Qt.labs.platform 1.0

ToolBar {

    leftPadding: 8
    Material.elevation: 4

    Flow {
        id: flow
        width: parent.width

        Row {
            id: fileRow
            ToolButton {
                id: openButton
                text: "\uF115" // icon-folder-open-empty
                font.family: "fontello"
                font.pointSize: 20
                focusPolicy: Qt.TabFocus
                onClicked: openDialog.open()
            }
            ToolButton {
                id: saveButton
                text: "\uE800" // icon-floppy
                font.family: "fontello"
                font.pointSize: 20
                focusPolicy: Qt.TabFocus
                onClicked: saveDialog.open()
            }
        }
    }

    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["*"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: document.load(file)
    }

    FileDialog {
        id: saveDialog
        fileMode: FileDialog.SaveFile
        nameFilters: openDialog.nameFilters
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    }

    MenuBar {
        Menu {
            title: qsTr("&File")

            MenuItem {
                text: qsTr("&Open")
                onTriggered: openDialog.open()
            }
            MenuItem {
                text: qsTr("&Save As...")
                onTriggered: saveDialog.open()
            }
            MenuItem {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("&Edit")

            MenuItem {
                text: qsTr("&Copy")
            }
            MenuItem {
                text: qsTr("Cu&t")
            }
            MenuItem {
                text: qsTr("&Paste")
            }
        }
    }
}
