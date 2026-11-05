#pragma once

#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
    ExplosionGenerator(
        Vector3D center,
        float radius,
        float strength,
        float tau
    );

    Vector3D calculateForce(
        const Particle& particle,
        float dt
    ) override;

    void update(float dt) override;

    void reset();

    bool isFinished() const;

private:
    Vector3D m_center;

    float m_radius;
    float m_strength;
    float m_tau;
    float m_time;
};