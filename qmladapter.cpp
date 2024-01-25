#include "qmladapter.h"

#include "inputcontroller.h"
#include "formulaparser.h"
#include "evaluator.h"
#include "chemicalequivalentcontroller.h"

QMLAdapter::QMLAdapter(QObject *parent) : QObject(parent)
{
}

void QMLAdapter::setMolecularWeight(const QString& weight) {
    molecular_weight = weight;
    emit molecularWeightChanged();
}

QString QMLAdapter::getMolecularWeight() const {
    return molecular_weight;
}

void QMLAdapter::setEquivalent(const QString& new_equivalent) {
    equivalent = new_equivalent;
    emit equivalentCalculated();
}

QString QMLAdapter::getEquivalent() const {
    return equivalent;
}

void QMLAdapter::setResult(const QString& new_result) {
    result = new_result;
    emit resultCalculated();
}

QString QMLAdapter::getResult() const {
    return result;
}

void QMLAdapter::setError(const QString& new_error) {
    error = new_error;
    emit errorHappend();
}

QString QMLAdapter::getError() const {
    return error;
}

void QMLAdapter::cleareError() {
    error = "";
}

float QMLAdapter::calculateMolecularWeight(const QString& formula){

    QString new_error;
    float weight =  FormulaParser::ConvertToMolecularWeight(formula, new_error);

    if(!new_error.isEmpty()) {
        setError(new_error);
    }
    else {
        setMolecularWeight(QString::number(weight));
    }

    return weight;
}

void QMLAdapter::calculateLigation(
    const QString& vector_mass, const QString& vector_length,
    const QString& insert_length, const QString& molar_vector_insert_right,
    const QString& molar_vector_insert_left) {

    QString new_error = InputController::CheckLigationInput(
    vector_mass, vector_length, molar_vector_insert_right, molar_vector_insert_left, insert_length
        );

    if(new_error.isEmpty()) {

        const float mass_float = QString(vector_mass).replace(",",".").toFloat();
        const float vector_length_float = QString(vector_length).replace(",",".").toFloat();
        const float left_ratio_insertion_float = QString(molar_vector_insert_left).replace(",",".").toFloat();
        const float right_ratio_insertion_float = QString(molar_vector_insert_right).replace(",",".").toFloat();
        const float length_insertion_float = QString(insert_length).replace(",",".").toFloat();

        setResult(QString::number(Evaluator::EvaluateMassInsertion(
        mass_float, vector_length_float, left_ratio_insertion_float,
            right_ratio_insertion_float, length_insertion_float
            )));

    } else {

        setError(new_error);

    }

}


void QMLAdapter::calculateVolume(
    const QString& formula_input, const QString& molar_concentration,
    const QString& molar_weight, bool is_normal_concentration) {

    QString new_error = InputController::CheckInput(formula_input, molar_concentration, molar_weight);

    if(new_error.isEmpty()) {

        const size_t EMPTY = 1;
        size_t equivalent_result = EMPTY;
        if(is_normal_concentration) {
            equivalent_result = ChemicalEquivalentController::Instence().FindEquivalent(formula_input);
            setEquivalent(QString::number(equivalent_result));
            equivalent_result = (equivalent_result == 0 ? 1 : equivalent_result);
        }

        cleareError();
        const float weigth = calculateMolecularWeight(QString(formula_input).replace(",","."));
        new_error = getError();

        if(new_error.isEmpty()){

            const float molar_concentration_float = QString(molar_concentration).replace(",",".").toFloat();
            const float molar_weight_float = QString(molar_weight).replace(",",".").toFloat();

            setResult(QString::number(Evaluator::EvaluateVolume(weigth / equivalent_result,
                                       molar_concentration_float,
                                       molar_weight_float
                                       )));

        } else {
            setError(new_error);
        }
    } else {
        setError(new_error);
    }
}


void QMLAdapter::calculateConcentration(
    const QString& formula_input, const QString& volume,
    const QString& molar_weight, bool is_normal_concentration) {

    QString new_error = InputController::CheckInput(formula_input, volume, molar_weight);

    if(new_error.isEmpty()){

        const size_t EMPTY = 1;
        size_t equivalent_result = EMPTY;
        if(is_normal_concentration) {
            equivalent_result = ChemicalEquivalentController::Instence().FindEquivalent(formula_input);
            setEquivalent(QString::number(equivalent_result));
            equivalent_result = (equivalent_result == 0 ? 1 : equivalent_result);
        }

        cleareError();
        const float weigth = calculateMolecularWeight(QString(formula_input).replace(",","."));
        new_error = getError();

        if(new_error.isEmpty()){

            const float volume_float = QString(volume).replace(",",".").toFloat();
            const float molar_weight_float = QString(molar_weight).replace(",",".").toFloat();

            setResult(QString::number(Evaluator::EvaluateMolarConcentration(weigth / equivalent_result,
                                                                volume_float,
                                                                molar_weight_float
                                                                )));
        } else {
            setError(new_error);
        }
    } else {
        setError(new_error);
    }
}


void QMLAdapter::calculateMass(
    const QString& formula_input, const QString& volume,
    const QString& molar_concentration, bool is_normal_concentration) {

    QString new_error = InputController::CheckInput(formula_input,volume,molar_concentration);

    if(new_error.isEmpty()){

        const size_t EMPTY = 1;
        size_t equivalent_result = EMPTY;
        if(is_normal_concentration) {
            equivalent_result = ChemicalEquivalentController::Instence().FindEquivalent(formula_input);
            setEquivalent(QString::number(equivalent_result));
            equivalent_result = (equivalent_result == 0 ? 1 : equivalent_result);
        }

        cleareError();
        const float weigth = calculateMolecularWeight(QString(formula_input).replace(",","."));
        new_error = getError();

        if(new_error.isEmpty()){

            const float volume_float = QString(volume).replace(",",".").toFloat();
            const float molar_concentration_float = QString(molar_concentration).replace(",",".").toFloat();

            setResult(QString::number(Evaluator::EvaluateMass(
                weigth / equivalent_result, volume_float, molar_concentration_float
                )));

        } else {

            setError(new_error);
        }

    }else {

        setError(new_error);

    }

}


