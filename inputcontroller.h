#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QString>

class InputController
{
public:
    InputController() = delete;

    // [^A-Za-z0-9] acid limit chars filter
    // [^\\*\\.A-Za-z0-9()\[\\]+,-] formula for parsing chars filter
    // [*0-9H2O$] hydrate filter

    static bool InputHasCorrectChars(const QString& input_formula, const QString& correct_chars);

    static bool EquivalentIsUnsignedInt(const QString& input_equivalent);

    static QString CheckDBInput(const QString& acid_limit_input, const QString& equivalent_limit);

    static QString CheckFormula(const QString& formula);

    static QString CheckingFormulaForOxide(const QString& formula);

    static QString CheckFloatInput(const QString& float_input);

    static QString CheckInput(const QString& formula_input, const QString& float_input1, const QString& float_input2);

    static QString CheckFormulaForHydrate(const QString& formula);

    static QString CheckLigationInput(
        const QString& float_input1,
        const QString& float_input2,
        const QString& float_input3,
        const QString& float_input4,
        const QString& float_input5
        );

    static QString CheckNormalConcentrationInput(const QString& formula_input, const QString& float_input1, const QString& float_input2);
};

#endif // INPUTCONTROLLER_H
