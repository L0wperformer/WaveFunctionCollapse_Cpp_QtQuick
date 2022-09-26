import QtQuick 2.0

Item {
    property var tilesByIndex: []
    property list<Tile> tiles
    id: root



    Component.onCompleted: {
        dimensions = handler.getDimensions()
        //console.log(dimensions)
        handler.drawGrid()
    }

    //This is the Connection to the grid InitFunction
    //The GridView is initialized in the correct way
    Connections {
        target: handler
        function onGridInit() {
            for (var x = 0; x < (dimensions * dimensions); x++) {
                tilesByIndex[x] = (-1)
                let component = Qt.createComponent("Tile.qml")
                let newTile = component.createObject(root, {
                                                         "index": -1,
                                                         "height": root.height / dimensions,
                                                         "width": root.width / dimensions
                                                     })
                tiles.push(newTile)
            }
            tileGrid.rows = dimensions
            tileGrid.columns = dimensions
        }
    }
    //This is the Connection to the drawTile Function of handler
    //In the function the Tiles are drawn on the canvas
    //Function chooses what tile to draw depending on the index passt in the
    //Emitted signal
    Connections {
        target: handler
        function onDrawTile(posIndex, newTileIndex) {

            let component = Qt.createComponent("Tile.qml")
            let newTile = component.createObject(root, {
                                                     "index": newTileIndex,
                                                     "height": root.height / dimensions,
                                                     "width": root.width / dimensions
                                                 })
            tiles[posIndex] = newTile
        }
    }
    //Click anywhere to start Algorithm
    MouseArea {
        anchors.fill: parent
        onClicked: {
            this.visible = false
            handler.startCollapsing()
        }
    }

    Grid {
        id: tileGrid
        anchors.fill: parent
        children: tiles
    }
}
