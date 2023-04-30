import QtQuick 2.0

Item {
     property bool highlighted: true
    width: 1000
    height: 1000

    rotation: -180

    Rectangle {
        anchors.centerIn: parent
        color: highlighted ? "red" : lineColor
        rotation: 90
        width: parent.width
        height: parent.height / 5
    }
    Rectangle{
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        color: highlighted ? "red" : lineColor
        width: parent.width / 2
        height: parent.height / 5


    }
}
