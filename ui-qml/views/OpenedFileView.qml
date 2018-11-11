import QtQuick 2.11
import QtQuick.Controls 2.4
import CleanEditor 1.0
import "../styles"

Item {
    id: root
    property alias text: textArea.text

    signal contentChanged()

    Rectangle {
        id: lineNumberPanel
        width: 50
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }

        color: Style.lineNumberBackground

        LineNumbers {
            id: lineNumbersItem
            anchors.fill: parent
            anchors.topMargin: 8

            selectedBackgroundColor: Style.lineNumberSelectedBackgroundColor
            currentBackgroundColor: Style.lineNumberCurrentBackgroundColor
            selectedTextColor: Style.lineNumberSelectedTextColor
            currentTextColor: Style.lineNumberCurrentTextColor
            textColor: Style.lineNumberTextColor

            document: textArea.textDocument
            cursorPosition: textArea.cursorPosition
            selectionStart: textArea.selectionStart
            selectionEnd: textArea.selectionEnd
            lineHeight: 14
            offsetY: textEditor.contentY
        }
    }

    Flickable {
        id: textEditor
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: lineNumberPanel.right
            leftMargin: 4
        }
        clip: true
        contentWidth: textArea.width
        contentHeight: textArea.height
        onContentYChanged: root.update()
        boundsBehavior: Flickable.StopAtBounds

        TextArea.flickable: TextArea {
            id: textArea
            textFormat: Qt.PlainText
            background: null
            font.family: "Hack"
            font.pointSize: 12
            selectByMouse: true
            onLinkActivated: Qt.openUrlExternally(link)
            selectionColor: "#b2d7ff"
            onTextChanged: root.contentChanged()
        }

        ScrollBar.vertical: ScrollBar {}
        ScrollBar.horizontal: ScrollBar {}
    }

}
