import QtQuick 6.0
import QtQuick.Window 6.0
import QtQuick.Controls 6.0
import QtQml 6.0
import CleanEditor 1.0
import "../components"

ApplicationWindow {
    id: root

    visible: true
    width: 640
    height: 480
    title: qsTr("Clean Editor")

    header: MenuComponent {
        id: menu
        width: parent.width
    }

    FileNavigationComponent {
        id: fileNavigation
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: 200
    }

    EditorComponent {
        id: editor
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: fileNavigation.right
        }
    }
}
