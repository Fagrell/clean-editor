import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0
import "../styles"

ToolBar {

    property alias title: menuTitle.text

    leftPadding: 8
    Material.elevation: 4

    RowLayout {
        id: fileRow
        anchors.fill: parent

        MenuToolButton {
            id: openButton
            text: "\uF115" // icon-folder-open-empty
            focusPolicy: Qt.TabFocus
            onClicked: openDialog.open()
        }
        MenuToolButton {
            id: saveButton
            text: "\uE800" // icon-floppy
            focusPolicy: Qt.TabFocus
            onClicked: saveDialog.open()
        }
        Text {
            id: menuTitle
            text: menuModel.title
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
            color: Style.menuTitleColor
            font: Style.menuTitleFont
        }
    }

    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["*"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: mainController.menuController.openFileClicked(file)
    }

    FileDialog {
        id: saveDialog
        fileMode: FileDialog.SaveFile
        nameFilters: openDialog.nameFilters
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: mainController.menuController.saveAsFileClicked(file);
    }

    Shortcut {
        id: openShortcut
        sequence: StandardKey.Open
        onActivated: openDialog.open()
    }

    Shortcut {
        id: saveAsShortcut
        sequence: StandardKey.SaveAs
        onActivated: saveDialog.open()
    }

    Shortcut {
        id: saveShortcut
        sequence: StandardKey.Save
        onActivated: menuModel.isNewFile ? saveDialog.open() : mainController.menuController.saveFileClicked();
    }

    Shortcut {
        id: newShortcut
        sequence: StandardKey.New
        onActivated: mainController.menuController.newFileClicked();
    }
}
