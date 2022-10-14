import QtQuick 2.0

Item {
    width: 1000
    height: 1000

    Rectangle {
        anchors.centerIn: parent
        color: lineColor
        width: parent.width
        height: parent.height / 5
    }
    Rectangle {
        anchors.centerIn: parent
        rotation: 90
        color: lineColor
        width: parent.width
        height: parent.height / 5
    }
}
