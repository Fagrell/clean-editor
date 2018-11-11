import QtQuick 2.11
import QtQuick.Window 2.4
import QtQuick.Controls 2.4
import QtQml 2.11
import CleanEditor 1.0

ApplicationWindow {
    id: root

    property DocumentHandler currentDocument

    visible: true
    width: 640
    height: 480
    title: qsTr("Clean Editor")

    header: MenuView {
        id: menu
        width: parent.width
    }

    function setCurrentDocument(document) {
        root.currentDocument = null
        menu.title = document.fileName
        openedFileEditor.text = document.textContent
        root.currentDocument = document
    }

    FilesNavigationView {
        id: openedFilesBar

        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: 200
        onFileSelected: root.setCurrentDocument(document)
    }


    OpenedFileView {
        id: openedFileEditor
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: openedFilesBar.right
        }

        onContentChanged: {
            if (root.currentDocument) {
                root.currentDocument.textContent = openedFileEditor.text
            }
        }
    }
}
