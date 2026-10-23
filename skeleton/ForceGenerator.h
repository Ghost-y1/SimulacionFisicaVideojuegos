#pragma once

class Particle;

class ForceGenerator
{
public:

    virtual ~ForceGenerator() = default;

    virtual void updateForce(
        Particle* particle,
        float dt
    ) = 0;
};