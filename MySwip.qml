import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Item {
    id: swip

    property color colorBackGround: "#5ccccc"
    readonly property int count: swiper.count
    readonly property int currentIndex: swiper.currentIndex
    readonly property int firstPageNumber: 0
    readonly property int secondPageNumber: 1
    readonly property int thirdPageNumber: 2

    SwipeView {
        id: swiper
        currentIndex: swip.firstPageNumber
        anchors.fill: parent

        Repeater {
            id: repeater
            model: 3
            Item {
                Rectangle {
                    anchors.fill: parent
                    color: swip.colorBackGround
                    MouseArea {
                        anchors.fill: parent
                        onClicked: forceActiveFocus()
                    }
                }
            }
        }
    }
}
