import QtQuick 2.0

Item {

    width: 1000
    height: 1000
    property bool highlighted: true
    rotation: -90

    Rectangle {
        anchors.centerIn: parent
        color: highlighted ? "red" : lineColor
        rotation: 90
        width: parent.width
        height: parent.height / 5
    }
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        color: highlighted ? "red" : lineColor
        width: parent.width / 2
        height: parent.height / 5
    }
}
