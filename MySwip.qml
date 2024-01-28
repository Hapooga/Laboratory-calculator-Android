import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15

Item {
    id: swip

    function calculatePrevPage() {
        if(swiper.currentIndex === swip.thirdPageNumber)
            return swip.thirdPageNumber
        if(swiper.currentIndex === swip.firstPageNumber)
            return swip.firstPageNumber
    }

    property color colorBackGround: "#5ccccc"
    property int prevPageIndex: calculatePrevPage()
    readonly property alias count: swiper.count
    readonly property alias currentIndex: swiper.currentIndex
    readonly property int firstPageNumber: 0
    readonly property int secondPageNumber: 1
    readonly property int thirdPageNumber: 2
    readonly property int pageAmount: 3

    signal indexChanged()

    SwipeView {
        id: swiper
        currentIndex: swip.firstPageNumber
        anchors.fill: parent

        Repeater {
            id: repeater
            model: swip.pageAmount
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
        onCurrentIndexChanged: swip.indexChanged()
    }
}
