#include "formulaparser.h"

#include <QString>
#include <string>
#include <cctype>
#include <memory>
#include <string_view>

#include "periodictable.h"


float FormulaParser::ToFloat(const std::string& element_atomic_weight) {
    return std::stof(element_atomic_weight);
}

std::string FormulaParser::GetElement(std::string_view& formula, QString& error) {

    std::string result;
    result.push_back(formula.front());
    formula.remove_prefix(1);

    if (!formula.empty()) {

        if (isdigit(result[0]) && (isdigit(formula.front()) || formula.front() == '.')) {

            while (isdigit(formula.front()) || formula.front() == '.') {

                result.push_back(formula.front());
                formula.remove_prefix(1);
                if (formula.empty()) {

                    break;
                }

                else if ((formula.front() == '.' && result.back() == '.') || (formula.front() == '.' && isdigit(result.back()))) {

                    error = "Wrong input " + QString::fromStdString(std::string(formula));
                }
            }
        }
        else if (islower(formula.front())) {

            result.push_back(formula.front());
            formula.remove_prefix(1);
        }
    }

    return result;
}

std::string_view FormulaParser::CatSubFormula(std::string_view& formula, const size_t left_pose, const size_t right_pose) {

    std::string_view sub_formula = formula.substr(left_pose, right_pose);

    formula.remove_prefix(right_pose);

    return sub_formula;
}

bool FormulaParser::IsIn(const std::string_view& formula, size_t pose) {
    return pose < formula.size();
}

std::string_view FormulaParser::GetSubFormula(std::string_view& formula) {

    size_t after_opening_bracket_pose = 0;
    size_t closing_bracket = formula.find_first_of(')');
    size_t one_more_sub_formula_bracket = formula.find_first_of('(');

    if (IsIn(formula, closing_bracket) && IsIn(formula, one_more_sub_formula_bracket)) {

        if (closing_bracket < one_more_sub_formula_bracket) {
            return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
        }

        if (closing_bracket > one_more_sub_formula_bracket) {
            closing_bracket = formula.find_last_of(')');
            return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
        }

    }

    return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
}

std::unique_ptr<Expression<float>> FormulaParser::Parse(std::string_view& formula, QString& error) {

    if (formula.empty()) {

        return Value(static_cast<float>(0));
    }
    // =========================================================================================================================
    if (formula.front() == '[' || formula.front() == ']' ||
        formula.front() == '*' || formula.front() == '-' ||
        formula.front() == '+'
        ) {

        formula.remove_prefix(1);

        return Parse(formula, error);
    }
    // =========================================================================================================================
    if (formula.front() == '(') {

        formula.remove_prefix(1);

        std::string_view sub_formula_view(GetSubFormula(formula));

        std::unique_ptr<Expression<float>> sub_formula = Parse(sub_formula_view, error);

        formula.remove_prefix(1);

        // -----------------------------------
        if (formula.empty()) {

            error = "The brackets are set incorrectly " + QString::fromStdString(std::string(formula));

        }
        // -----------------------------------

        float l_value = ToFloat(GetElement(formula, error));

        // -----------------------------------
        if (formula.empty()) {

            return Product(Value(sub_formula->Evaluate()), Value(l_value));
        }
        // -----------------------------------
        return Sum(Product(Value(sub_formula->Evaluate()), Value(l_value)), Parse(formula, error));
    }
    // =========================================================================================================================
    if (isdigit(formula.front())) {

        float l_value = ToFloat(GetElement(formula, error));
        // -----------------------------------
        if (formula.front() == '(') {

            error = "The brackets are set incorrectly " + QString::fromStdString(std::string(formula));
        }
        // -----------------------------------
        if (isupper(formula.front())) {

            return Product(Value(l_value), Parse(formula, error));
        }
        // -----------------------------------
        if (formula.empty()) {

            return Value(l_value);
        }
        // ------------------------------------
    }
    // =========================================================================================================================
    if (isupper(formula.front())) {

        float l_value = PeriodicTable::Instence().GetAtomicWeightByElement(GetElement(formula, error));

        // -----------------------------------
        if(l_value == 0){

            error = "The chemical element is incorrectly entered";

        }
        // -----------------------------------
        if (formula.empty()) {

            return Value(l_value);
        }
        // -----------------------------------
        if (isupper(formula.front())) {

            return Sum(Value(l_value), Parse(formula, error));
        }
        // -----------------------------------
        if (isdigit(formula.front())) {

            float r_value = ToFloat(GetElement(formula, error));
            // ------------------
            if (formula.empty()) {

                return Product(Value(l_value), Value(r_value));
            }
            // ------------------

            return Sum(Product(Value(l_value), Value(r_value)), Parse(formula, error));

        }
        // -----------------------------------
        if (formula.front() == '(') {

            formula.remove_prefix(1);

            std::string_view sub_formula_view(GetSubFormula(formula));

            std::unique_ptr<Expression<float>> sub_formula = Parse(sub_formula_view, error);

            formula.remove_prefix(1);

            // ------------------
            if (formula.empty()) {

                error = "The brackets are set incorrectly " + QString::fromStdString(std::string(formula));

            }
            // ------------------

            float r_value = ToFloat(GetElement(formula, error));

            // ------------------
            if (formula.empty()) {

                return Sum(Value(l_value), Product(Value(sub_formula->Evaluate()), Value(r_value)));
            }
            // ------------------
            return Sum(Sum(Value(l_value), Product(Value(sub_formula->Evaluate()), Value(r_value))), Parse(formula, error));
        }
        // -----------------------------------
        return Parse(formula, error);
    }
    // =========================================================================================================================

    error = "Wrong input " + QString::fromStdString(std::string(formula));

    return Value(static_cast<float>(0));
}

float FormulaParser::ConvertToMolecularWeight(const QString& сhemical_formula, QString& error) {

    std::string formula = сhemical_formula.toStdString();

    std::string_view formula_view(formula);

    std::unique_ptr<Expression<float>> formula_expression = Parse(formula_view, error);

    return formula_expression->Evaluate();

}
