import QtQuick 2.9
import QtQuick.Window 2.2
import OpenGlPlugin 1.0

Item {
    visible: true
    width: 640
    height: 480

    OglItem {
        anchors.fill: parent
        anchors.margins: 10

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "black"
            border.width: 2
        }
    }
}
