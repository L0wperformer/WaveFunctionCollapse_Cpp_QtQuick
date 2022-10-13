import QtQuick 2.0

Rectangle {
    width: 1000
    height: 1000
    color: background
    clip: true
    id: root

    Rectangle {

        transformOrigin: Item.Right
        anchors.right: parent.right
        y: -parent.height / 10

        rotation: -45
        color: lineColor
        width: parent.width / 1.5
        height: parent.height / 5
        clip: true
    }
    Rectangle {
        transformOrigin: Item.Center
        color: background
        width: root.width / 2
        height: root.width / 2
        anchors.centerIn: root
        border.color: lineColor
        border.width: root.width / 20
        radius: root.width
    }
}
