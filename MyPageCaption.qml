import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Item {
    id: pageCaption

    property color colorPanel: "#009999"
    property color textColor: "black"
    property int textSize: 24
    property string text: ""

    Rectangle {
        anchors.fill: parent
        color: pageCaption.colorPanel

        Text {
            id: pageCaptionText
            anchors.verticalCenter: parent.verticalCenter
            color: pageCaption.textColor
            font.pointSize: pageCaption.textSize
            text: pageCaption.text
        }
    }

}
