import QtQuick 2.0

Rectangle {
    width: 1000
    height: 1000
    color: background

    Rectangle {
        anchors.centerIn: parent
        color: lineColor
        width: parent.width
        height: parent.height / 5
    }
}
