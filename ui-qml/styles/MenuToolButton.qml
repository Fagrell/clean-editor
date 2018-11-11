import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
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

        layer.enabled: true
        layer.effect: DropShadow {
            verticalOffset: 0
            color: "black"
            radius: 2
            samples: 2
        }
    }
}


