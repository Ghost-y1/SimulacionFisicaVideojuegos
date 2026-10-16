#include "Particle.h"
#include <cmath>


Particle::Particle(
    Vector3D position,
    Vector3D velocity,
    Vector3D acceleration,
    float size,
    float mass,
    Vector4 color,
    float damping,
    float life
)
    : m_position(position),
    m_velocity(velocity),
    m_acceleration(acceleration),
    m_size(size),
    m_mass(mass),
    m_color(color),
    m_damping(damping),
    m_age(0.0f),
    m_life(life)
{
    m_pose = physx::PxTransform(m_position.toPxVec3());

    m_renderItem = new RenderItem(
        CreateShape(physx::PxSphereGeometry(m_size)),
        &m_pose,
        m_color
    );
}


Particle::~Particle()
{
    if (m_renderItem)
    {
        m_renderItem->release();
        m_renderItem = nullptr;
    }
}


void Particle::integrate(float dt)
{
    // Euler semi-implícito
    m_velocity += m_acceleration * dt;

    // Damping
    m_velocity = m_velocity * std::pow(m_damping, dt);

    // Posición
    m_position += m_velocity * dt;

    // Aumentar edad
    m_age += dt;

    // Actualizar render
    m_pose = physx::PxTransform(m_position.toPxVec3());
}


bool Particle::isAlive() const
{
    return m_age < m_life;
}


Vector3D Particle::getPosition() const
{
    return m_position;
}