#pragma once

#include "Vector3D.h"

class Particle;

class ForceGenerator
{
public:
    virtual ~ForceGenerator() = default;

    virtual Vector3D calculateForce(const Particle& particle, float dt) = 0;

    virtual void update(float dt) {}
};