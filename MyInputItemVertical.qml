import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Item {
    id: inputItem

    property color textColor: "black"
    property string textCaption: "Equivalent"
    property alias textInput: input.text
    property alias methodHints: input.inputMethodHints
    property bool visibleState: true
    property bool readOnlyState: true
    property int leftMarginText: 10
    property int textHeigth: 20
    property int textFieldWidth: 80
    property int textFieldHeight: 35
    property int leftMarginInput: 10
    property RegularExpressionValidator inputValidator: RegularExpressionValidator { regularExpression: /[0-9.,]+/ }


        Text {
            id: caption
            anchors { left: parent.left; top: parent.top; topMargin: -4; leftMargin: inputItem.leftMarginText }
            color: inputItem.textColor
            font.pointSize: inputItem.textHeigth
            text: inputItem.textCaption
            visible: inputItem.visibleState
        }

        TextField {
            id: input
            anchors {
                left: caption.left
                bottom: parent.bottom
            }
            width: inputItem.textFieldWidth
            height: inputItem.textFieldHeight
            visible: inputItem.visibleState
            readOnly: inputItem.readOnlyState
            validator: inputItem.inputValidator
            text: inputItem.textInput

            background: Rectangle {
                border.color: "black"
                border.width: 2
                radius: 10
            }
        }

}
