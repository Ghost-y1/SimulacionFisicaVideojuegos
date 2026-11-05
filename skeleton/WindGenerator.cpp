#include "WindGenerator.h"
#include "Particle.h"

WindGenerator::WindGenerator(
    Vector3D windVelocity,
    float k1,
    float k2
)
    : m_windVelocity(windVelocity),
    m_k1(k1),
    m_k2(k2)
{
}

Vector3D WindGenerator::getWindVelocity(
    const Particle& particle
) const
{
    return m_windVelocity;
}

Vector3D WindGenerator::calculateForce(
    const Particle& particle,
    float dt
)
{
    Vector3D relativeVelocity =
        getWindVelocity(particle) - particle.getVelocity();

    Vector3D force = relativeVelocity * m_k1;

    if (m_k2 != 0.0f)
    {
        force += relativeVelocity *
            (m_k2 * relativeVelocity.magnitude());
    }

    return force;
}