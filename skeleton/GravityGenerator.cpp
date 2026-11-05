#include "GravityGenerator.h"
#include "Particle.h"

Vector3D GravityGenerator::calculateForce(
    const Particle& particle,
    float dt
)
{
    return m_gravity * particle.getMass();
}