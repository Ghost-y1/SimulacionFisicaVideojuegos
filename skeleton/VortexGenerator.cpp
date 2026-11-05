#include "VortexGenerator.h"
#include "Particle.h"

VortexGenerator::VortexGenerator(
    Vector3D center,
    float strength,
    float radius,
    float k1
)
    : WindGenerator(Vector3D(0.0f, 0.0f, 0.0f), k1, 0.0f),
    m_center(center),
    m_strength(strength),
    m_radius(radius)
{
}

Vector3D VortexGenerator::getWindVelocity(
    const Particle& particle
) const
{
    Vector3D relative = particle.getPosition() - m_center;

    Vector3D tangential(
        -relative.z,
        0.0f,
        relative.x
    );

    return tangential * m_strength;
}

Vector3D VortexGenerator::calculateForce(
    const Particle& particle,
    float dt
)
{
    Vector3D relative = particle.getPosition() - m_center;

    if (relative.magnitude() > m_radius)
        return Vector3D(0.0f, 0.0f, 0.0f);

    Vector3D windVelocity = getWindVelocity(particle);
    Vector3D relativeVelocity = windVelocity - particle.getVelocity();

    return relativeVelocity * m_k1;
}