import QtQuick 2.11
import QtQuick.Window 2.4
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client Management")

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");

    FilesNavigationView {
        id: openedFilesBar
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: 200
        onFileSelected: {
            contentFrame.replace("qrc:/views/OpenedFileView.qml")
        }
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: openedFilesBar.right
        }
        initialItem: "qrc:/views/SplashView.qml"
        clip: true
    }
}
