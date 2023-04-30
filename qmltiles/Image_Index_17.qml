import QtQuick 2.0

Item {
    property bool highlighted: true
    width: 1000
    height: 1000

    id: root

    Rectangle {

        transformOrigin: Item.Right
        anchors.right: parent.right
        y: -parent.height / 10

        rotation: -45
        color: highlighted ? "red" : lineColor
        width: (parent.width / 1.5)
        height: parent.height / 5
    }
    Rectangle {
        transformOrigin: Item.Center
        color: background
        width: root.width / 2
        height: root.width / 2
        anchors.centerIn: root
        border.color: highlighted ? "red" : lineColor
        border.width: root.width / 20
        radius: root.width
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

