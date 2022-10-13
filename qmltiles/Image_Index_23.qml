import QtQuick 2.0

Rectangle {
    width: 1000
    height: 1000
    color: background
    clip: true
    id: root

    rotation: 180
    Rectangle {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        color: lineColor
        width: parent.width / 2
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
