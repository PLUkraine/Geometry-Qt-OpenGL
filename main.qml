import QtQuick 2.9
import QtQuick.Window 2.2
import OpenGlPlugin 1.0

Item {
    visible: true
    width: 640
    height: 480

    OglItem {
        id: ogl
        anchors.fill: parent
        anchors.margins: 10

        Timer {
            id: updateOgl

            interval: 1000/30
            running: true
            repeat: true
            onTriggered: {
                ogl.renderOgl();
            }
        }

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: "black"
//            border.width: 2
//        }
    }
}
