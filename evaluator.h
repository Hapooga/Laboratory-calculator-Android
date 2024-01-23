#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator
{
public:
    Evaluator() = delete;

    static float EvaluateMolarConcentration(const float molecular_weigth, const float volume_l, const float mass);

    static float EvaluateVolume(const float molecular_weigth, const float molar_concentration, const float mass);

    static float EvaluateMass(const float molecular_weigth, const float volume_l, const float molar_concentration);

    static float EvaluateMassInsertion(
        const float vector_mass,
        const float vector_lenght,
        const float ratio_l,
        const float ratio_r,
        const float lenght_insertion
        );
};

#endif // EVALUATOR_H
