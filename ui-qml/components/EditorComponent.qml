import QtQuick 6.0
import QtQuick.Controls 6.0
import CleanEditor 1.0
import "../styles"

Item {
    id: root
    property alias text: textArea.text

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
            font: Style.editorFont

            document: textArea.textDocument
            cursorPosition: textArea.cursorPosition
            selectionStart: textArea.selectionStart
            selectionEnd: textArea.selectionEnd
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
        onContentYChanged: lineNumbersItem.update()
        boundsBehavior: Flickable.StopAtBounds

        TextArea.flickable: TextArea {
            id: textArea
            textFormat: Qt.PlainText
            background: null
            font: Style.editorFont
            selectByMouse: true
            onLinkActivated: Qt.openUrlExternally(link)
            selectionColor: Style.edtitorSelectionColor

            Component.onCompleted: {
                editorModel.document = textArea.textDocument
            }
        }

        ScrollBar.vertical: ScrollBar {}
        ScrollBar.horizontal: ScrollBar {}
    }
}
