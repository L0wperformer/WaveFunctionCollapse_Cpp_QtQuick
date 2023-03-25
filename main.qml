import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    //        width: 1023
    //        height: 1023
    visible: true
    property int dimensionsWidth: 0
    property int dimensionsHeight: 0

    property string lineColor: "black"
    property string background: "white"
    property string nonCollapsedBorderColor: "lightgrey"
    Component.onCompleted: {
        let widthHeight = 1920
        dimensionsWidth = handler.getDimensionsWidth()
        dimensionsHeight = handler.getDimensionsHeight()

        if (widthHeight % dimensionsWidth !== 0) {
            let factor = Math.floor(widthHeight / dimensionsWidth) + 1
            widthHeight = (factor) * dimensionsWidth
            while (factor % 5 !== 0) {
                factor++
            }
            console.log("Factor: " + factor)
        }
        this.width = widthHeight
        this.height = widthHeight * (dimensionsHeight / dimensionsWidth)
        //        let factor = 0
        //        dimensionsWidth = handler.getDimensionsWidth()
        //        dimensionsHeight = handler.getDimensionsHeight()
        //        if (1000 % dimensionsWidth !== 0) {
        //            let factor = Math.floor(1000 / dimensionsWidth) + 1
        //            //widthHeight = (factor) * dimensionsWidth
        //            while (factor % 5 !== 0) {
        //                factor++
        //            }
        //            console.log("Factor: " + factor)
        //        }

        //        //        this.width = handler.getDimensionsWidth() * factor
        //        //        this.height = handler.getDimensionsHeight() * factor
        pageLoader.source = "Canvas.qml"
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}
