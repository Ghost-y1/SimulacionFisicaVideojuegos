#pragma once

#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
    GravityGenerator(Vector3D gravity)
        : m_gravity(gravity)
    {
    }

    Vector3D calculateForce(
        const Particle& particle,
        float dt
    ) override;

private:
    Vector3D m_gravity;
};