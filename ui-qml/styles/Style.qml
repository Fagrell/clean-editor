pragma Singleton
import QtQuick 6.0

QtObject {
    id: style

    //General used by many properties
    property color mainBlueColor: "#161161"

    //LineNumbers properties
    property color lineNumberBackground: "#d3d3d3"
    property color lineNumberSelectedBackgroundColor: "#b2d7ff"
    property alias lineNumberCurrentBackgroundColor: style.mainBlueColor
    property alias lineNumberSelectedTextColor: style.mainBlueColor
    property color lineNumberCurrentTextColor: "white"
    property alias lineNumberTextColor: style.mainBlueColor

    //Editor properties
    property font editorFont: Qt.font({family: "Hack", pointSize: 12})
    property alias edtitorSelectionColor: style.lineNumberSelectedBackgroundColor

    //Menu properties
    property int menuIconSize: 14
    property alias menuIconColor: style.mainBlueColor
    property alias menuTitleColor: style.mainBlueColor
    property font menuTitleFont: Qt.font({bold: true, pointSize: 16})

    //FileNavigation properties
    property alias fileNavigationBackgroundColor: style.mainBlueColor
    property color fileNavigationSelectedColor: "#223D6B"
    property color fileNavigationHoveredColor: "#1d195e"
    property color fileNavigationTextColor: "white"
}
