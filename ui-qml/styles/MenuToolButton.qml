import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

ToolButton {
    id: root
    contentItem: Text {
        text: root.text
        font.family: "fontello"
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"

        layer.enabled: true
        layer.effect: DropShadow {
            verticalOffset: 0
            color: "black"
            radius: 2
            samples: 2
        }
    }
}


