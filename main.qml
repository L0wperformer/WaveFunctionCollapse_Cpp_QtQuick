import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    //    width: 1023
    //    height: 1023
    visible: true
    property int dimensions: 0
    property string lineColor: "black"
    property string background: "white"
    property string nonCollapsedBorderColor: "lightgrey"
    Component.onCompleted: {

        let widthHeight = 1000
        dimensions = handler.getDimensions()
        if (1000 % dimensions !== 0) {
            let factor = Math.floor(1000 / dimensions) + 1
            widthHeight = (factor) * dimensions
            while (factor % 5 !== 0) {
                factor++
            }
            console.log("Factor: " + factor)
        }

        this.width = widthHeight
        this.height = widthHeight
        pageLoader.source = "Canvas.qml"
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}
