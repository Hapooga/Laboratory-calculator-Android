import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Item {
    id: inputItem

    width: parent.width
    height: textFieldHeight

    property color textColor: "black"
    property string textCaption: "Chemical formula"
    property alias methodHints: input.inputMethodHints
    property alias textInput: input.text
    property bool visibleState: true
    property bool readOnlyState: false
    property int leftMarginText: defaultMarginText
    property int textHeigth: 20
    readonly property int defaultMarginText: 10
    readonly property int textWidth: caption.width
    property int textFieldWidth: 160
    property int textFieldHeight: 35
    property int leftMarginInput: inputItem.leftMarginText + caption.width + inputItem.leftMarginText
    property RegularExpressionValidator inputValidator: RegularExpressionValidator { regularExpression: /[0-9.,]+/ }
    property string valueBuffer1: ""
    property string valueBuffer2: ""

        Text {
            id: caption
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: inputItem.leftMarginText }
            color: inputItem.textColor
            font.pointSize: inputItem.textHeigth
            text: inputItem.textCaption
            visible: inputItem.visibleState
        }

        TextField {
            id: input
            anchors {
                left: parent.left
                leftMargin: inputItem.leftMarginInput
                verticalCenter: parent.verticalCenter
            }
            width: inputItem.textFieldWidth
            height: inputItem.textFieldHeight
            visible: inputItem.visibleState
            readOnly: inputItem.readOnlyState
            validator: inputItem.inputValidator

            background: Rectangle {
                border.color: "black"
                border.width: 2
                radius: 10
            }
            //TODO
            Keys.onReturnPressed: calculate()
            Keys.onTabPressed: calculate()
        }
   // }
}
