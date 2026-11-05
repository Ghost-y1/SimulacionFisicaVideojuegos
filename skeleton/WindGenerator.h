#pragma once

#include "ForceGenerator.h"

class WindGenerator : public ForceGenerator
{
public:
    WindGenerator(
        Vector3D windVelocity,
        float k1,
        float k2 = 0.0f
    );

    Vector3D calculateForce(
        const Particle& particle,
        float dt
    ) override;

protected:
    virtual Vector3D getWindVelocity(
        const Particle& particle
    ) const;

    Vector3D m_windVelocity;

    float m_k1;
    float m_k2;
};