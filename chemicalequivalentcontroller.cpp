#include "chemicalequivalentcontroller.h"

ChemicalEquivalentController::ChemicalEquivalentController() :
    chemicalEquivalents
    ( {
        { "OH"  ,  1 },  { "HCOO"  ,  1 },
        { "F"   ,  1 },  { "CH3COO",  1 },
        { "Cl"  ,  1 },  { "C2O4"  ,  2 },
        { "Br"  ,  1 },  { "H2PO4" ,  1 },
        { "I"   ,  1 },  { "HPO4"  ,  2 },
        { "S"   ,  2 },  { "HCO3"  ,  1 },
        { "CN"  ,  1 },
        { "NO2" ,  1 },
        { "NO3" ,  1 },
        { "PO4" ,  3 },
        { "AsO4",  3 },
        { "SO3" ,  2 },
        { "SO4" ,  2 },
        { "CO3" ,  2 },
        { "SiO3",  2 },
        { "CrO4",  2 },
        { "Cr2O7", 2 },
        { "MnO4",  1 },
        { "ClO" ,  1 },
        { "ClO2",  1 },
        { "ClO3",  1 },
        { "ClO4",  1 },
    } )
{
}

const ChemicalEquivalentController& ChemicalEquivalentController::Instence() {
    static const ChemicalEquivalentController table;
    return table;
}


size_t ChemicalEquivalentController::FindEquivalent(const QString& formula) const {

    size_t molecules = 0;

    size_t max_tail_after_taple = 2;

    auto equivalent_it = chemicalEquivalents.find(formula);

    if((formula.back().isDigit() && formula[formula.size() - max_tail_after_taple] == ')') ||
        equivalent_it->first != formula.back()) {

        molecules = formula.back().digitValue();
    }

    return (molecules > 1) ? equivalent_it->second * molecules : equivalent_it->second;
}
