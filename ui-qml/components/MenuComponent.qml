import QtQuick 6.0
import QtQuick.Layouts 6.0
import QtQuick.Controls 6.0
import QtQuick.Controls.Material 6.0
import Qt.labs.platform 1.1
import "../styles"

ToolBar {

    property alias title: menuTitle.text

    leftPadding: 8
    Material.elevation: 4

    RowLayout {
        id: fileRow
        anchors.fill: parent
        MenuToolButton {
            id: newButton
            text: "\uE800" // icon-doc-text-inv-1
            focusPolicy: Qt.TabFocus
            onClicked: mainController.menuController.newFileClicked();
        }

        MenuToolButton {
            id: openButton
            text: "\uE802" // icon-folder
            focusPolicy: Qt.TabFocus
            onClicked: openDialog.open()
        }
        MenuToolButton {
            id: saveButton
            text: "\uE801" // icon-floppy
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
