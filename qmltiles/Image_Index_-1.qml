import QtQuick 2.0

Item {

    property bool highlighted: false
    width: 1000
    height: 1000
    anchors.fill: parent

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        color: background
//        border {
//            color: nonCollapsedBorderColor
//            width: 0.5
//        }
    }
//    Rectangle {
//        color: nonCollapsedBorderColor
//        width: parent.width //Math.sqrt(2 * (parent.width * parent.width))
//        height: parent.height / 10
//        anchors.centerIn: parent
//        rotation: 45
//    }
//    Rectangle {
//        color: "lightgrey" //nonCollapsedBorderColor
//        width: parent.width //Math.sqrt(2 * (parent.width * parent.width))
//        height: parent.height / 10
//        anchors.centerIn: parent
//        rotation: -45
//    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

