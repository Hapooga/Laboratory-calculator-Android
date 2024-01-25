#include "chemicalequivalentcontroller.h"

#include <map>

// "ZnCl2",
// "KHCO3",
// "Al2(CO3)3",
// "Al(HCO3)3",
// "(MgOH)2SO4"

ChemicalEquivalentController::ChemicalEquivalentController() :
    chemicalEquivalents
    ( {
        { "F"   ,  1 },
        { "I"   ,  1 },
        { "S"   ,  2 },
        { "Br"  ,  1 },
        { "OH"  ,  1 },
        { "Cl"  ,  1 },
        { "CN"  ,  1 },
        { "NO2" ,  1 },
        { "NO3" ,  1 },
        { "PO4" ,  3 },
        { "SO3" ,  2 },
        { "SO4" ,  2 },
        { "CO3" ,  2 },
        { "ClO" ,  1 },
        { "AsO4",  3 },
        { "SiO3",  2 },
        { "CrO4",  2 },
        { "MnO4",  1 },
        { "ClO2",  1 },
        { "ClO3",  1 },
        { "ClO4",  1 },
        { "HCOO",  1 },
        { "C2O4",  2 },
        { "HPO4",  2 },
        { "HCO3",  1 },
        { "H2PO4", 1 },
        { "Cr2O7", 2 },
        { "CH3COO", 1 },
    } )
{
}

const ChemicalEquivalentController& ChemicalEquivalentController::Instence() {
    static const ChemicalEquivalentController table;
    return table;
}


size_t ChemicalEquivalentController::FindEquivalent(const QString& formula) const {

    const size_t MAX_TAIL_AFTER_TAPLE = 2;
    const size_t DIGIT_SIZE = 1;
    const size_t DEFAULT_MOLECULS = 1;

    std::map<size_t, ResultVariant> buffer;
    QString substring_buffer;
    for(const auto& [equivalent_variant, value] : chemicalEquivalents) {

        if(formula.back().isDigit() && formula[formula.size() - MAX_TAIL_AFTER_TAPLE] == ')'){
            substring_buffer = formula.mid(formula.size() - equivalent_variant.size() - MAX_TAIL_AFTER_TAPLE, equivalent_variant.size());
            if(substring_buffer == equivalent_variant) {
                buffer[equivalent_variant.size()] =
                    ResultVariant{equivalent_variant, value, size_t(formula.back().digitValue())};
            }
        } else {
            substring_buffer = formula.mid(formula.size() - equivalent_variant.size() - DIGIT_SIZE,equivalent_variant.size());
            if(substring_buffer == equivalent_variant) {
                buffer[equivalent_variant.size()] =
                    ResultVariant{equivalent_variant, value, size_t(formula.back().digitValue())};
            }
            substring_buffer = formula.mid(formula.size() - equivalent_variant.size(), equivalent_variant.size());
            if(substring_buffer == equivalent_variant) {
                buffer[equivalent_variant.size()] =
                    ResultVariant{equivalent_variant, value, DEFAULT_MOLECULS};
            }
        }
    }

    return buffer.empty() ? 1 : buffer.rbegin()->second._equivalent_value * buffer.rbegin()->second._molecules;
}
