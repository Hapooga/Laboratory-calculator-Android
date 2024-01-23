#ifndef QMLADAPTER_H
#define QMLADAPTER_H

#include <QObject>
#include <QQmlEngine>

//#include <evaluator.h>

class QMLAdapter : public QObject
{
    Q_OBJECT

public:
    explicit QMLAdapter(QObject *parent = nullptr);

    Q_INVOKABLE QString getMolecularWeight() const;
    Q_INVOKABLE QString getEquivalent() const;
    Q_INVOKABLE QString getError() const;
    Q_INVOKABLE QString getResult() const;

signals:

    void molecularWeightChanged();
    void equivalentCalculated();
    void resultCalculated();
    void errorHappend();

public slots:

    void calculateLigation(
        const QString& vector_mass, const QString& vector_length,
        const QString& insert_length, const QString& molar_vector_insert_right,
        const QString& molar_vector_insert_left
        );

    void calculateVolume(
        const QString& formula_input, const QString& molar_concentration,
        const QString& molar_weight, bool is_normal_concentration = false);

    void calculateConcentration(
        const QString& formula_input, const QString& volume,
        const QString& molar_weight, bool is_normal_concentration = false);

    void calculateMass(
        const QString& formula_input, const QString& volume,
        const QString& molar_concentration, bool is_normal_concentration = false);


private:

    float calculateMolecularWeight(const QString& formula);

    void setMolecularWeight(const QString& weight);
    void setEquivalent(const QString& new_equivalent);
    void setResult(const QString& new_result);
    void setError(const QString& error);
    void cleareError();

private:

    QString molecular_weight;
    QString equivalent;
    QString error;
    QString result;
};

#endif // QMLADAPTER_H
