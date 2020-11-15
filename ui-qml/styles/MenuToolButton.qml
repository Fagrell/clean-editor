import QtQuick 6.0
import QtQuick.Controls 6.0
import "."

ToolButton {
    id: root
    contentItem: Text {
        text: root.text
        font.family: "fontello"
        font.pointSize: Style.menuIconSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: Style.menuIconColor
    }
}


