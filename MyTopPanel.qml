import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15

Item {
    id: topPanel

    property color colorPanel: "white"
    property string imageSource: "../img/iconApp.png"
    property string caption: "Lab Calculator"
    property int pageCaptionTextHeight: 24

    Rectangle {
        id: backGroundPanel
        anchors.fill: parent

        color: topPanel.colorPanel
        Image {
            id: imageIcon
            anchors.verticalCenter: parent.verticalCenter
            width:  parent.height
            height: parent.height
            source: topPanel.imageSource
        }
        Text {
            id: appName
            anchors.verticalCenter: imageIcon.verticalCenter
            anchors.left: imageIcon.right
            text: topPanel.caption
            font.pointSize: topPanel.pageCaptionTextHeight
        }
    }
}
