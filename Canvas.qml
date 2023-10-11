import QtQuick 2.0

Item {
    property var tilesByIndex: handler.tileMap
    property var highlightTheseTiles: []

    //property list<Tile> tiles
    id: root
    Connections{
        target: handler
        function onTilesToHighlightChanged(theseTiles){
        highlightTheseTiles = theseTiles;
        }
    }

    Component.onCompleted: {
        //        dimensionsWidth = handler.getDimensionsWidth()
        //        dimensionsHeight = handler.getDimensionsHeight()
        console.log("Item completed")
    }
    //    Connections {
    //        target: handler
    //        function onSendTilesToBeHighlightedToQml(list) {
    //            console.log(list)
    //            highlightTheseTiles = list
    //        }
    //    }

    //This is the Connection to the grid InitFunction
    //The GridView is initialized in the correct way
    //If i need this code again:
    //let component = Qt.createComponent("Tile.qml")
    //            //"qmltiles/Image_Index_" + newTileIndex + ".qml")
    //            let newTile = component.createObject(root, {
    //                                                     "index": newTileIndex,
    //                                                     "height": root.height / dimensions,
    //                                                     "width": root.width / dimensions
    //                                                 })
    anchors.fill: parent
    //Click anywhere to start Algorithm
    Rectangle {
        id: gridBackground
        anchors.fill: parent
        color: background
        GridView {
            id: tileGrid
            anchors.fill: parent
            cellWidth: tileWidthHeightInPixel//root.width / dimensionsWidth
            cellHeight: tileWidthHeightInPixel//root.height / dimensionsHeight
            clip: true

            model: tilesByIndex.length
            delegate: Tile {
                width: tileWidthHeightInPixel//root.width / dimensionsWidth
                height: tileWidthHeightInPixel//root.height / dimensionsHeight
                m_index: tilesByIndex[index]
                m_highlighted: highlightTheseTiles.indexOf(index) !== -1
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                this.visible = false
                switchColor.visible = true
                highlightTheseTiles = handler.getTilesToHighlight()
                handler.startCollapsing()
            }
        }

        MouseArea {
            id: switchColor
            visible: false
            anchors.fill: parent
            onClicked: {
                if (background === "black") {
                    background = "white"
                    lineColor = "black"
                } else {
                    background = "black"
                    lineColor = "#BADEAFFE"
                }
            }
        }
    }
}
