#ifndef CHEMICALEQUIVALENTCONTROLLER_H
#define CHEMICALEQUIVALENTCONTROLLER_H

#include <map>
#include <QString>

class ChemicalEquivalentController
{
public:

    static const ChemicalEquivalentController& Instence();

    ChemicalEquivalentController(const ChemicalEquivalentController& other) = delete;
    ChemicalEquivalentController& operator = (const ChemicalEquivalentController& other) = delete;

    size_t FindEquivalent(const QString& formula) const;

private:

    ChemicalEquivalentController();

    const std::map<const QString, const float> chemicalEquivalents;
};

#endif // CHEMICALEQUIVALENTCONTROLLER_H
