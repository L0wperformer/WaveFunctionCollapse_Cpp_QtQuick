import QtQuick 2.0

Item {
    property bool highlighted: true

    width: 1000
    height: 1000


    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        color: highlighted ? "red" : lineColor
        width: parent.width / 5
        height: parent.height / 2 + parent.height / 10
    }
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        color: highlighted ? "red" : lineColor
        width: parent.width / 2
        height: parent.height / 5
    }
}
