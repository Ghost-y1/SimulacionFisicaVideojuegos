#pragma once

#include "WindGenerator.h"

class VortexGenerator : public WindGenerator
{
public:

    VortexGenerator(
        Vector3D center,
        float strength,
        float radius,
        float k1
    );

protected:

    // Calcula la velocidad del viento
    // en función de la posición de la partícula
    Vector3D getWindVelocity(
        Particle* particle
    ) const override;

private:

    // Centro del torbellino
    Vector3D m_center;

    // Intensidad del torbellino
    float m_strength;

    // Radio de acción
    float m_radius;
};