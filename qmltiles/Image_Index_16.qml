import QtQuick 2.0

Item {
     property bool highlighted: true
    width: 1000
    height: 1000
    //rotation: 90

    //    Rectangle {
    //        anchors.centerIn: parent
    //        rotation: 45
    //        color: highlighted ? lineColor: "red"
    //        width: Math.sqrt(2 * parent.width * parent.width)
    //        height: parent.height / 5
    //    }
    Rectangle {
        transformOrigin: Item.Right
        anchors.right: parent.right
        y: -parent.height / 10
        rotation: -45
        color: highlighted ? "red" : lineColor
        width: Math.sqrt(2 * parent.width * parent.width)
        height: parent.height / 5
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/

