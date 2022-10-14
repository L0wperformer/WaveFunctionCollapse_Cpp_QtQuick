import QtQuick 2.0

Item {
    width: 1000
    height: 1000

    rotation: 90

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        color: lineColor
        width: parent.width / 5
        height: parent.height / 2 + parent.height / 10
    }
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        color: lineColor
        width: parent.width / 2
        height: parent.height / 5
    }
}
