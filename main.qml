import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    width: 1000
    height: 1000
    visible: true
    Component.onCompleted: pageLoader.source = pageLoader.source = "Canvas.qml"
    property int dimensions: 0
    property string lineColor: "black"
    property string background: "white"
    property string nonCollapsedBorderColor: "lightgrey"

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}
