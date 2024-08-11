

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import TestingLook

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#ffffff"

    Row {
        id: row
        x: 0
        y: 0
        width: 1920
        height: 1080
        opacity: 1
        anchors.left: parent.left
        anchors.right: parent.right
        transformOrigin: Item.Center
        layer.enabled: false
        activeFocusOnTab: false
        z: 0

        Column {
            id: column
            width: 200
            height: 400
            transformOrigin: Item.TopRight
            layer.mipmap: false
            layer.wrapMode: ShaderEffectSource.ClampToEdge
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
