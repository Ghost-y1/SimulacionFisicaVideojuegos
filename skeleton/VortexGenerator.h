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

    Vector3D calculateForce(
        const Particle& particle,
        float dt
    ) override;

protected:
    Vector3D getWindVelocity(
        const Particle& particle
    ) const override;

private:
    Vector3D m_center;

    float m_strength;
    float m_radius;
};