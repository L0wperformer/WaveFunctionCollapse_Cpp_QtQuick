import QtQuick 2.0

Item {
     property bool highlighted: true
    width: 1000
    height: 1000


    Rectangle {
        anchors.centerIn: parent
        color: highlighted ? "red" : lineColor
        width: parent.width
        height: parent.height / 5
    }
}
