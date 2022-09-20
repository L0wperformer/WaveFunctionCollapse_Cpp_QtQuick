import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    width: 640
    height: 640
    visible: true
    Component.onCompleted: pageLoader.source = "Canvas.qml"
    property int dimensions: 10

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}
