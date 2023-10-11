import QtQuick 2.0

//Image {
//    property int index: -1
//    source: "/Tiles/Image_Index_" + index + ".png"

//}
Item {
    //width: 1000
    //height: 1000
    id: root
    property int m_index: -1
    property bool m_highlighted: false
    onM_indexChanged: {
        loader.setSource("qmltiles/Image_Index_" + m_index + ".qml", {
                             "highlighted": m_highlighted
                         })
    }

    Loader {
        id: loader
        source: "qmltiles/Image_Index_" + m_index + ".qml"
        anchors.fill: parent
    }
}
