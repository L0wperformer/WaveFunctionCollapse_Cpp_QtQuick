import QtQuick 2.0

Item {
    property var tilesByIndex: handler.tileMap
    //property list<Tile> tiles
    id: root
    onTilesByIndexChanged: {

    }

    Component.onCompleted: {
        dimensions = handler.getDimensions()
        console.log("Item completed")
    }

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
            cellWidth: root.width / dimensions
            cellHeight: root.height / dimensions
            clip: true

            model: tilesByIndex.length
            delegate: Tile {
                width: root.width / dimensions
                height: root.height / dimensions
                m_index: tilesByIndex[index]
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                this.visible = false
                switchColor.visible = true
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
