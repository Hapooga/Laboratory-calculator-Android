#ifndef CHEMICALEQUIVALENTCONTROLLER_H
#define CHEMICALEQUIVALENTCONTROLLER_H

#include <vector>
#include <QString>

class ChemicalEquivalentController
{
public:

    static const ChemicalEquivalentController& Instence();

    //ChemicalEquivalentController(const ChemicalEquivalentController& other) = delete;

    size_t FindEquivalent(const QString& formula) const;

private:

    struct ResultVariant {
        QString _equivalent_variant;
        float _equivalent_value;
        size_t _molecules;
    };

    ChemicalEquivalentController();
    //ChemicalEquivalentController& operator = (const ChemicalEquivalentController& other);

    std::vector<std::pair<QString, float>> chemicalEquivalents;
};

#endif // CHEMICALEQUIVALENTCONTROLLER_H
