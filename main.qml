import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    width: 640
    height: 480
    visible: true
    Component.onCompleted: pageLoader.source = "Canvas"

    Loader{
       id: pageLoader
       anchors.fill: parent
    }
}
