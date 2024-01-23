#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#include <map>
#include <string>

class PeriodicTable
{
public:

    static const PeriodicTable& Instence();

    PeriodicTable(const PeriodicTable& other) = delete;
    PeriodicTable& operator = (const PeriodicTable& other) = delete;

    float GetAtomicWeightByElement(const std::string& element) const;

private:

    PeriodicTable();

    const std::map<const std::string, const float> periodicTable;
};

#endif // PERIODICTABLE_H
