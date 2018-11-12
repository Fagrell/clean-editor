import QtQuick 2.11
import QtQuick.Window 2.4
import QtQuick.Controls 2.4
import QtQml 2.11
import CleanEditor 1.0
import "../components"

ApplicationWindow {
    id: root

    property DocumentHandler currentDocument

    visible: true
    width: 640
    height: 480
    title: qsTr("Clean Editor")

    header: MenuComponent {
        id: menu
        width: parent.width
    }

    function setCurrentDocument(document) {
        root.currentDocument = null
        menu.title = document.fileName
        editor.text = document.textContent
        root.currentDocument = document
    }

    FileNavigationComponent {
        id: fileNavigation

        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: 200
        onFileSelected: root.setCurrentDocument(document)
    }

    EditorComponent {
        id: editor
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: fileNavigation.right
        }

        onContentChanged: {
            if (root.currentDocument) {
                root.currentDocument.textContent = editor.text
            }
        }
    }
}
