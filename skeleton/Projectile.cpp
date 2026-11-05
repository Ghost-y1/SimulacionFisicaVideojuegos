#include "Projectile.h"

float Projectile::scaledMass(const ProjectileData& data)
{
    float factor = data.simulatedSpeed / data.realSpeed;
    return data.realMass / (factor * factor);
}

float Projectile::scaledGravity(const ProjectileData& data)
{
    float factor = data.simulatedSpeed / data.realSpeed;
    return data.gravity * factor * factor;
}

Projectile::Projectile(Vector3D position, Vector3D direction, const ProjectileData& data)
    : Particle(
        position,
        direction* data.simulatedSpeed,
        Vector3D(0.0f, -scaledGravity(data), 0.0f),
        data.size,
        scaledMass(data),
        data.color,
        data.damping,
        30.0f
    ),
    m_realMass(data.realMass),
    m_realSpeed(data.realSpeed),
    m_simulatedSpeed(data.simulatedSpeed),
    m_simulatedMass(scaledMass(data)),
    m_simulatedGravity(scaledGravity(data))
{
}

float Projectile::getScaleFactor() const
{
    return m_simulatedSpeed / m_realSpeed;
}

float Projectile::getRealEnergy() const
{
    return 0.5f * m_realMass * m_realSpeed * m_realSpeed;
}

float Projectile::getSimulatedEnergy() const
{
    return 0.5f * m_simulatedMass * m_simulatedSpeed * m_simulatedSpeed;
}

float Projectile::getSimulatedMass() const
{
    return m_simulatedMass;
}

float Projectile::getSimulatedGravity() const
{
    return m_simulatedGravity;
}

Vector3D Projectile::scaleForce(const Vector3D& realAcceleration) const
{
    float factor = getScaleFactor();
    Vector3D simulatedAcceleration = realAcceleration * (factor * factor);

    return simulatedAcceleration * m_simulatedMass;
}