import QtQuick
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    visible: true
    title: qsTr("ChemicalCalculator")

    Connections {
        target: adapter

        onMolecularWeightChanged: {
            molecularWeightOutput.textInput = adapter.getMolecularWeight()
        }
        onErrorHappend: {
            errorText.text = adapter.getError()
        }
        onEquivalentCalculated: {
            equivalentInputItem.textInput = adapter.getEquivalent()
        }
        onResultCalculated: {
            if(swip.currentIndex === swip.thirdPageNumber || swip.currentIndex === swip.secondPageNumber ) {
                if (radioButtonInputItemTop.checkedState){
                    radioButtonInputItemTop.textInput = adapter.getResult()
                }
                if (radioButtonInputItemMiddle.checkedState){
                    radioButtonInputItemMiddle.textInput = adapter.getResult()
                }
                if (radioButtonInputItemBottom.checkedState) {
                    radioButtonInputItemBottom.textInput = adapter.getResult()
                }
            }
            else {
                insertDnaMassOutput.textInput = adapter.getResult()
            }
        }
    }

    QtObject {
        id: _CONSTANTA
        readonly property int topPanelHeight: Screen.desktopAvailableHeight / 20
        readonly property color colorBackGround: "#5ccccc"
        readonly property color colorPanel: "#009999"
        readonly property color pageCaptionColor: "black"
        readonly property color textButtonColor: "#4aff26"
        readonly property color topPanelColor: "white"
        readonly property int pageCaptionTextHeight: 24
        readonly property int captionTextHeight: 18
        readonly property int buttonBottomMargin: 20
        readonly property int leftMargin: 20
        readonly property int buttonHeight: Screen.desktopAvailableHeight / 10
        readonly property int buttonRadius: 10
        readonly property int textFieldHeight: 35
        readonly property int textFieldWidth: 160
        readonly property int textFieldBorderWidth: 2
        readonly property int textWidth: 150
    }


    // 1. Переключение свайпом вместо меню
    // 2. TODO: Реализовать клавиатуру без лишних символов с крупными кнопками

    MySwip {
        id: swip
        anchors.fill: parent
    }

    MyTopPanel {
        id: topPanel
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; }
        height: parent.height / 20
        width: parent.width
    }

    MyPageCaption {
        id: pageCaption
        anchors { top: topPanel.bottom; horizontalCenter: topPanel.horizontalCenter; }
        width: topPanel.width
        height: topPanel.height
        text:   swip.currentIndex === swip.firstPageNumber ?  "Calculation of ligation" :
                swip.currentIndex === swip.secondPageNumber ?  "Molar concentration" : "Normal concentration"
    }


    function maxTextLenthChemicalFormula(){
        return Math.max(inputFormula.textWidth, molecularWeightOutput.textWidth)
    }

    MyInputItem {
        id: inputFormula
        textCaption: "Chemical formula"
        leftMarginInput: maxTextLenthChemicalFormula() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: pageCaption.horizontalCenter; top: pageCaption.bottom; topMargin: 30 }
        visibleState: swip.currentIndex !== swip.firstPageNumber
        inputValidator: RegularExpressionValidator {
            regularExpression:
                /[A-Za-z0-9\[\]()+-.,*]+/
        }
    }



    MyInputItem {
        id: molecularWeightOutput
        textCaption: "Molecular weight"
        leftMarginInput: maxTextLenthChemicalFormula() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: inputFormula.horizontalCenter; top: inputFormula.bottom; topMargin: 10}
        visibleState: swip.currentIndex !== swip.firstPageNumber
        readOnlyState: true
    }


    MyRadioButtonInputItem {
        id: radioButtonInputItemTop
        anchors { left: parent.left; top: molecularWeightOutput.bottom; topMargin: 10}
        width: Math.min(parent.width / 2, 180)
        height: radioButtonInputItemTop.textFieldHeight * 2
        visibleState: swip.currentIndex !== swip.firstPageNumber
        textButton: qsTr("Volume, L")
        checkedState: true
        onClicked: {
            radioButtonInputItemMiddle.checkedState = false
            radioButtonInputItemBottom.checkedState = false
        }
        methodHints: Qt.ImhDigitsOnly
    }

    MyRadioButtonInputItem {
        id: radioButtonInputItemMiddle
        anchors { left: parent.left; top: radioButtonInputItemTop.bottom; topMargin: 10}
        width: Math.min(parent.width / 2, 180)
        height: radioButtonInputItemMiddle.textFieldHeight * 2
        visibleState: swip.currentIndex !== swip.firstPageNumber
        textButton: swip.currentIndex === swip.secondPageNumber ?
                        qsTr("Molar concentration, mol/L")
                      : qsTr("Equivalent concentration, eq/L")
        onClicked: {
            radioButtonInputItemTop.checkedState = false
            radioButtonInputItemBottom.checkedState =  false

        }
        methodHints: Qt.ImhDigitsOnly
    }

    MyRadioButtonInputItem {
        id: radioButtonInputItemBottom
        anchors { left: parent.left; top: radioButtonInputItemMiddle.bottom; topMargin: 10}
        width: Math.min(parent.width / 2, 180)
        height: radioButtonInputItemBottom.textFieldHeight * 2
        visibleState: swip.currentIndex !== swip.firstPageNumber
        textButton: qsTr("Weight, g")
        onClicked: {
            radioButtonInputItemMiddle.checkedState = false
            radioButtonInputItemTop.checkedState = false
        }
        methodHints: Qt.ImhDigitsOnly
    }




    MyInputItemVertical {
        id: equivalentInputItem
        width: parent.width / 2
        height: equivalentInputItem.textFieldHeight * 2
        anchors { left: radioButtonInputItemTop.right; top: radioButtonInputItemTop.top;}
        visibleState: swip.currentIndex === swip.thirdPageNumber
    }



    function maxTextLenthThirdPage(){
        return Math.max(Math.max(Math.max(Math.max(vectorDnaMassInput.textWidth, vectorDnaLengthInput.textWidth),
                        insertDnaLengthInput.textWidth), molarVectorInsertRatioLeftInput.textWidth), insertDnaMassOutput.textWidth)
    }

    MyInputItem {
        id: vectorDnaMassInput
        textCaption: "Vector DNA mass, ng."
        leftMarginInput: maxTextLenthThirdPage() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: pageCaption.horizontalCenter; top: pageCaption.bottom; topMargin: 60 }
        visibleState: swip.currentIndex === swip.firstPageNumber
        methodHints: Qt.ImhDigitsOnly
    }

    MyInputItem {
        id: vectorDnaLengthInput
        textCaption: "Vector DNA length, bp"
        leftMarginInput: maxTextLenthThirdPage() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: vectorDnaMassInput.horizontalCenter; top: vectorDnaMassInput.bottom; topMargin: 10 }
        visibleState: swip.currentIndex === swip.firstPageNumber
        methodHints: Qt.ImhDigitsOnly
    }

    MyInputItem {
        id: insertDnaLengthInput
        textCaption: "Insert DNA length, bp"
        leftMarginInput: maxTextLenthThirdPage() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: vectorDnaLengthInput.horizontalCenter; top: vectorDnaLengthInput.bottom; topMargin: 10 }
        visibleState: swip.currentIndex === swip.firstPageNumber
        methodHints: Qt.ImhDigitsOnly
    }

    ////////////////////////////////////
    MyInputItem {
        id: molarVectorInsertRatioLeftInput
        textCaption: "Molar vector:insert ratio"
        leftMarginInput: maxTextLenthThirdPage() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - defaultMarginText, 50)
        anchors { horizontalCenter: insertDnaLengthInput.horizontalCenter;
            top: insertDnaLengthInput.bottom; topMargin: 10 }
        visibleState: swip.currentIndex === swip.firstPageNumber
        methodHints: Qt.ImhDigitsOnly
    }

    MyInputItem {
        id: molarVectorInsertRatioRigthInput
        textCaption: ":"
        leftMarginText: molarVectorInsertRatioLeftInput.textWidth +
            molarVectorInsertRatioLeftInput.textFieldWidth + defaultMarginText * 3
        leftMarginInput: leftMarginText + defaultMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - defaultMarginText, 50)
        anchors { verticalCenter: molarVectorInsertRatioLeftInput.verticalCenter;
            left: molarVectorInsertRatioLeftInput.rigth;}
        visibleState: swip.currentIndex === swip.firstPageNumber
        methodHints: Qt.ImhDigitsOnly
    }
    ////////////////////////

    MyInputItem {
        id: insertDnaMassOutput
        textCaption: "Insert DNA  mass, ng."
        leftMarginInput: maxTextLenthThirdPage() + leftMarginText * 2
        textFieldWidth: Math.min(parent.width - leftMarginInput - leftMarginText, 160)
        anchors { horizontalCenter: molarVectorInsertRatioLeftInput.horizontalCenter; top: molarVectorInsertRatioLeftInput.bottom; topMargin: 10 }
        visibleState: swip.currentIndex === swip.firstPageNumber
        readOnlyState: true
    }

    ///////////////////////////////////////////////////////////////////
    // Buttons
    Button {
        id: calculateButton

        anchors.bottom: bottomErrorPanel.top
        anchors.left: parent.left

        anchors.leftMargin: (parent.width / 2 / 10) / 2
        anchors.bottomMargin: _CONSTANTA.buttonBottomMargin

        width: parent.width / 2 - (parent.width / 2 / 10)
        height: _CONSTANTA.buttonHeight

        text: qsTr("Calculate")
        contentItem: Text {
            text: parent.text
            font.pointSize: 25
            opacity: enabled ? 1.0 : 0.3
            color: parent.down ? "#21be2b" : "#4aff26"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            anchors.fill: parent
            opacity: enabled ? 1 : 0.3
            color: "#0c6460"
            //border.color: control.down ? "#21be2b" : "#4aff26"
            border.width: 1
            radius: _CONSTANTA.buttonRadius
        }

        onClicked: {
            if(swip.currentIndex === swip.thirdPageNumber || swip.currentIndex === swip.secondPageNumber) {
                if (radioButtonInputItemTop.checkedState){
                    adapter.calculateVolume(
                                inputFormula.textInput, radioButtonInputItemMiddle.textInput,
                                radioButtonInputItemBottom.textInput, swip.currentIndex === swip.thirdPageNumber);
                }
                if (radioButtonInputItemMiddle.checkedState){
                    adapter.calculateConcentration(
                                inputFormula.textInput, radioButtonInputItemTop.textInput,
                                radioButtonInputItemBottom.textInput, swip.currentIndex === swip.thirdPageNumber);
                }
                if (radioButtonInputItemBottom.checkedState) {
                    adapter.calculateMass(
                                inputFormula.textInput, radioButtonInputItemTop.textInput,
                                radioButtonInputItemMiddle.textInput, swip.currentIndex === swip.thirdPageNumber);
                }
            }
            if(swip.currentIndex === swip.firstPageNumber){
                adapter.calculateLigation(
                            vectorDnaMassInput.textInput, vectorDnaLengthInput.textInput,
                            insertDnaLengthInput.textInput, molarVectorInsertRatioRigthInput.textInput,
                            molarVectorInsertRatioLeftInput.textInput)
            }

        }
    }

    Button {
        id: cleareButton

        anchors.bottom: bottomErrorPanel.top
        anchors.right: parent.right

        anchors.rightMargin: (parent.width / 2 / 10) / 2
        anchors.bottomMargin: _CONSTANTA.buttonBottomMargin

        width: parent.width / 2 - (parent.width / 2 / 10)
        height: _CONSTANTA.buttonHeight

        text: qsTr("Clear")
        contentItem: Text {
            text: parent.text
            font.pointSize: 25
            opacity: enabled ? 1.0 : 0.3
            color: parent.down ? "#21be2b" : "#4aff26"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            anchors.fill: parent
            opacity: enabled ? 1 : 0.3
            color: "#0c6460"
            //border.color: control.down ? "#21be2b" : "#4aff26"
            border.width: 1
            radius: _CONSTANTA.buttonRadius
        }

        onClicked: {
            // TODO:
            if (swip.currentIndex === swip.firstPageNumber)
                cleareFirstPage()
            else if (swip.currentIndex === swip.secondPageNumber)
                cleareSecondPage()
            else
                cleareThirdPage()
        }
    }

    ///////////////////////////////////////////////////////////////////

    Rectangle {
        id: bottomErrorPanel
        anchors.bottom: whiteBottomPanel.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: _CONSTANTA.topPanelHeight
        color: _CONSTANTA.colorPanel

        Text {
            id: errorText
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            font.pointSize: _CONSTANTA.captionTextHeight
            elide: Text.ElideNone
            Timer {
                interval: 5000; running: errorText !== ""; repeat: true
                onTriggered: errorText.text = ""
            }
        }
    }

    Rectangle {
        id: whiteBottomPanel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: _CONSTANTA.topPanelHeight
        color: "white"
    }

    PageIndicator {
        id: indicator

        count: swip.count
        currentIndex: swip.currentIndex

        anchors.bottom: swip.bottom
        anchors.horizontalCenter: swip.horizontalCenter
    }


    function clearTextById(id) {
        id.textInput = ""
    }

    function cleareFirstPage() {
        clearTextById(vectorDnaMassInput)
        clearTextById(vectorDnaLengthInput)
        clearTextById(insertDnaLengthInput)
        clearTextById(molarVectorInsertRatioLeftInput)
        clearTextById(molarVectorInsertRatioRigthInput)
        clearTextById(insertDnaMassOutput)
    }

    function cleareSecondPage() {
        clearTextById(inputFormula)
        clearTextById(molecularWeightOutput)
        clearTextById(radioButtonInputItemTop)
        clearTextById(radioButtonInputItemMiddle)
        clearTextById(radioButtonInputItemBottom)
    }

    function cleareThirdPage() {
        cleareSecondPage()
        clearTextById(equivalentInputItem)
    }
}


