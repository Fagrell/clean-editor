import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0
import "../styles" as Styles

ToolBar {

    property alias title: menuTitle.text

    leftPadding: 8
    Material.elevation: 4

    RowLayout {
        id: fileRow
        anchors.fill: parent

        Styles.MenuToolButton {
            id: openButton
            text: "\uF115" // icon-folder-open-empty
            focusPolicy: Qt.TabFocus
            onClicked: openDialog.open()
        }
        Styles.MenuToolButton {
            id: saveButton
            text: "\uE800" // icon-floppy
            focusPolicy: Qt.TabFocus
            onClicked: saveDialog.open()
        }
        Text {
            id: menuTitle
            text: "Title"
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
            color: "#161161"
            font.bold: true
            font.pointSize: 16
        }
    }

    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["*"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: documentsModel.openFile(file)
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
