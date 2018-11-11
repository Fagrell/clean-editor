pragma Singleton
import QtQuick 2.0

QtObject {
    id: style

    //LineNumbers properties
    property color lineNumberBackground: "#D3D3D3"
    property color lineNumberSelectedBackgroundColor: "#b2d7ff"
    property color lineNumberCurrentBackgroundColor: "#161161"
    property color lineNumberSelectedTextColor: "#161161"
    property color lineNumberCurrentTextColor: "white"
    property color lineNumberTextColor: "#161161"

    //Editor properties
    property font editorFont: Qt.font({family: "Hack", pointSize: 12})
    property alias edtitorSelectionColor: style.lineNumberSelectedBackgroundColor


}
