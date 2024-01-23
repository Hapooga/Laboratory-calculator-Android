#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <string>
#include <string_view>
#include <memory>
#include <QString>

#include "expressionTree.h"

class FormulaParser
{
public:

    FormulaParser() = delete;

    static float ConvertToMolecularWeight(const QString& chemical_formula, QString& error);

private:

    static std::unique_ptr<Expression<float>> Parse(std::string_view& formula, QString& error);

    static std::string GetElement(std::string_view& formula, QString& error);

    static std::string_view GetSubFormula(std::string_view& formula);

    static bool IsIn(const std::string_view& formula, size_t pose);

    static std::string_view CatSubFormula(std::string_view& formula, const size_t left_pose, const size_t right_pose);

    static float ToFloat(const std::string& element_atomic_weight);

};

#endif // FORMULAPARSER_H
