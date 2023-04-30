import QtQuick 2.0

Item {
     property bool highlighted: true
    id: root

    //    width: 1000
    //    height: 1000
    rotation: -180

    Rectangle {
        id: upright
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
        Rectangle {

            anchors.left: parent.right
            rotation: -45
            transformOrigin: Item.Left

            color: highlighted ? "red" : lineColor
            width: Math.sqrt(root.width * root.width / 2)
            height: root.height / 5
        }
    }
}
