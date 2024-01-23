#include "inputcontroller.h"

#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

bool InputController::InputHasCorrectChars(const QString& input_formula, const QString& correct_chars) {

    QRegularExpression rx(correct_chars);

    auto match = rx.match(input_formula);

    if (match.hasMatch()) {

        return false;
    }

    return true;
}

bool InputController::EquivalentIsUnsignedInt(const QString& input_equivalent) {

    if (input_equivalent.toInt() < 0 || !input_equivalent.toInt()) {

        return false;
    }

    return true;
}

QString InputController::CheckFormula(const QString& formula){

    if(!InputHasCorrectChars(formula,"[^\\*\\.A-Za-z0-9()\[\\]+,-]")){

        return "The formula contains incorrect values";

    }

    return "";

}

QString InputController::CheckFormulaForHydrate(const QString& formula){

    if(InputHasCorrectChars(formula,"[^H2O]+$")) {

        return "Hydrates are not calculated";

    }

    return "";

}

QString InputController::CheckDBInput(const QString& acid_limit_input, const QString& equivalent_limit){


    if (acid_limit_input.isEmpty()) {

        return "Empty acid residue field";

    } else if (!InputHasCorrectChars(acid_limit_input, "[^A-Za-z0-9]")){ // \w

        return "The acid residue contains incorrect values";

    }

    if (equivalent_limit.isEmpty()) {

        return "Empty equivalent field";

    } else if (!EquivalentIsUnsignedInt(equivalent_limit)) {

        return "Incorrect equivalent value";

    }

    return "";

}

QString InputController::CheckFloatInput(const QString& float_input){

    if(float_input.isEmpty()){

        return "An empty input field";

    }

    else if((!InputHasCorrectChars(float_input, "[^\\.0-9,]") ||
              (float_input.contains(".")  && float_input.contains(",")) ||
              (float_input.count('.') > 1 || float_input.count(',') > 1)) ||
             (float_input == "."         || float_input == "," ||
              float_input == ",."         || float_input == ".,")
             ){

        return "Check the entered values for invalid characters";
    }

    return "";

}

QString InputController::CheckInput(const QString& formula_input, const QString& float_input1, const QString& float_input2){

    QString error = CheckFormula(formula_input);

    if(error.isEmpty()){

        error = CheckFloatInput(float_input1);

    }

    else if(error.isEmpty()){

        error = CheckFloatInput(float_input2);

    }

    return error;

}

QString InputController::CheckNormalConcentrationInput(const QString& formula_input, const QString& float_input1, const QString& float_input2){

    QString error = CheckFormulaForHydrate(formula_input);

    if(error.isEmpty()){

        error = CheckFormula(formula_input);

    }

    if(error.isEmpty()){

        error = CheckFloatInput(float_input1);

    }

    else if(error.isEmpty()){

        error = CheckFloatInput(float_input2);

    }

    return error;
}

QString InputController::CheckLigationInput(
    const QString& float_input1,
    const QString& float_input2,
    const QString& float_input3,
    const QString& float_input4,
    const QString& float_input5
    ){

    QString error = CheckFloatInput(float_input1);

    if(error.isEmpty()){

        error = CheckFloatInput(float_input2);

    }

    else if(error.isEmpty()){

        error = CheckFloatInput(float_input3);

    }

    else if(error.isEmpty()){

        error = CheckFloatInput(float_input4);

    }

    else if(error.isEmpty()){

        error = CheckFloatInput(float_input5);

    }

    return error;
}
