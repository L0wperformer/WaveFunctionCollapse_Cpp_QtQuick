import QtQuick 2.0

Item {
    width: 1000
    height: 1000

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        color: "transparent"
        border {
            color: "lightgrey"
            width: 1
        }
    }
    Rectangle {
        color: "lightgrey"
        width: parent.width //Math.sqrt(2 * (parent.width * parent.width))
        height: parent.height / 10
        anchors.centerIn: parent
        rotation: 45
    }
    Rectangle {
        color: "lightgrey"
        width: parent.width //Math.sqrt(2 * (parent.width * parent.width))
        height: parent.height / 10
        anchors.centerIn: parent
        rotation: -45
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

