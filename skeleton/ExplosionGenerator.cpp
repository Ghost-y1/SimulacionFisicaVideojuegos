#include "ExplosionGenerator.h"
#include "Particle.h"

#include <cmath>

ExplosionGenerator::ExplosionGenerator(
    Vector3D center,
    float radius,
    float strength,
    float tau
)
    : m_center(center),
    m_radius(radius),
    m_strength(strength),
    m_tau(tau),
    m_time(0.0f)
{
}

Vector3D ExplosionGenerator::calculateForce(
    const Particle& particle,
    float dt
)
{
    Vector3D direction = particle.getPosition() - m_center;

    float distance = direction.magnitude();

    if (distance >= m_radius || distance < 0.001f)
        return Vector3D(0.0f, 0.0f, 0.0f);

    float decay = std::exp(-m_time / m_tau);

    return direction *
        ((m_strength / (distance * distance)) * decay);
}

void ExplosionGenerator::update(float dt)
{
    m_time += dt;
}

void ExplosionGenerator::reset()
{
    m_time = 0.0f;
}

bool ExplosionGenerator::isFinished() const
{
    return m_time >= 4.0f * m_tau;
}