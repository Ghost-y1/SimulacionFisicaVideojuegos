#pragma once

#include "Particle.h"

struct ProjectileData
{
    float realMass;
    float realSpeed;
    float simulatedSpeed;
    float gravity;
    float size;
    float damping;
    Vector4 color;
};

class Projectile : public Particle
{
public:
    Projectile(Vector3D position, Vector3D direction, const ProjectileData& data);

    float getScaleFactor() const;
    float getRealEnergy() const;
    float getSimulatedEnergy() const;
    float getSimulatedMass() const;
    float getSimulatedGravity() const;

private:
    static float scaledMass(const ProjectileData& data);
    static float scaledGravity(const ProjectileData& data);
    Vector3D scaleForce(const Vector3D& realAcceleration) const;

    float m_realMass;
    float m_realSpeed;
    float m_simulatedSpeed;
    float m_simulatedMass;
    float m_simulatedGravity;
};