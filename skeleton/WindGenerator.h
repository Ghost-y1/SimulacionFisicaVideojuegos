#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class WindGenerator : public ForceGenerator
{
public:

    WindGenerator(
        Vector3D windVelocity,
        float k1,
        float k2 = 0.0f
    );

    void updateForce(
        Particle* particle,
        float dt
    ) override;

protected:

    // Devuelve la velocidad del viento en la posición de la partícula.
    // En este generador básico es constante.
    virtual Vector3D getWindVelocity(
        Particle* particle
    ) const;

    Vector3D m_windVelocity;

    float m_k1;
    float m_k2;
};