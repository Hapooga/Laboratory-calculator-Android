import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Item {
    id: radioButtonInputItem

    property alias checkedState: radioButton.checked
    property bool visibleState: true
    property alias textInput: inputButton.text
    property alias methodHints: inputButton.inputMethodHints
    property int textFieldHeight: 35
    property int textFieldWidth: 80
    property int leftMargin: 10
    property int textSize: 20
    property string textButton: ""
    property RegularExpressionValidator inputValidator: RegularExpressionValidator { regularExpression: /[0-9.,]+/ }
    signal clicked()

    RadioButton {
        id: radioButton
        anchors {
            top: parent.top
            topMargin: -radioButtonInputItem.textFieldHeight / 2
            left: parent.left
            leftMargin: radioButtonInputItem.leftMargin
        }
        text: radioButtonInputItem.textButton
        font.pointSize: radioButtonInputItem.textSize
        visible: radioButtonInputItem.visibleState

        onClicked: {
            inputButton.text = ""
            radioButtonInputItem.clicked()
        }
    }

    TextField {
        id: inputButton
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width - 20
        height: radioButtonInputItem.textFieldHeight
        visible: radioButtonInputItem.visibleState

        validator: radioButtonInputItem.inputValidator
        text: radioButtonInputItem.textInput
        background: Rectangle {
            border.color: "black"
            border.width: 2
            radius: 10
        }
        readOnly: radioButton.checked

        //TODO
        Keys.onReturnPressed: calculate()
        Keys.onTabPressed: calculate()
    }
}
