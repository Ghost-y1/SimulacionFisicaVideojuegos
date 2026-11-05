#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class ExplosionGenerator : public ForceGenerator
{
public:

    ExplosionGenerator(
        Vector3D center,
        float radius,
        float strength,
        float tau
    );

    // Aplica la fuerza de explosión a una partícula
    void updateForce(
        Particle* particle,
        float dt
    ) override;

    // Actualiza el tiempo de la explosión
    void update(float dt);

    // Reinicia la explosión
    void reset();

    // Indica si la explosión ya se ha disipado
    bool isFinished() const;

private:

    Vector3D m_center;

    float m_radius;
    float m_strength;
    float m_tau;

    float m_time;
};