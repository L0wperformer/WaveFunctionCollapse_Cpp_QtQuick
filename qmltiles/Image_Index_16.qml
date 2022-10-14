import QtQuick 2.0

Item {
    width: 1000
    height: 1000

    Rectangle {
        anchors.centerIn: parent
        rotation: -45
        color: lineColor
        width: Math.sqrt(2 * parent.width * parent.width)
        height: parent.height / 5
    }
}
