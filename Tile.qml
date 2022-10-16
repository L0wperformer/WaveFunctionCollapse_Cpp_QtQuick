import QtQuick 2.0

//Image {
//    property int index: -1
//    source: "/Tiles/Image_Index_" + index + ".png"

//}
Item {
    width: 1000
    height: 1000
    property int m_index: -1
    Loader {
        anchors.fill: parent
        source: "qmltiles/Image_Index_" + m_index + ".qml"
    }
}
