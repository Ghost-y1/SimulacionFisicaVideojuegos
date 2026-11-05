#include "Particle.h"
#include "ForceGenerator.h"

#include <cmath>

Particle::Particle(
    Vector3D position,
    Vector3D velocity,
    Vector3D acceleration,
    float size,
    float mass,
    Vector4 color,
    float damping,
    float life,
    bool render
)
    : m_position(position),
    m_velocity(velocity),
    m_acceleration(acceleration),
    m_forceAccum(0.0f, 0.0f, 0.0f),
    m_color(color),
    m_size(size),
    m_mass(mass),
    m_damping(damping),
    m_age(0.0f),
    m_life(life)
{
    m_pose = physx::PxTransform(m_position.toPxVec3());

    if (render)
    {
        m_renderItem = new RenderItem(
            CreateShape(physx::PxSphereGeometry(m_size)),
            &m_pose,
            m_color
        );
    }
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
    Vector3D forceAcceleration(0.0f, 0.0f, 0.0f);

    if (m_mass > 0.0f)
        forceAcceleration = m_forceAccum * (1.0f / m_mass);

    Vector3D totalAcceleration = m_acceleration + forceAcceleration;

    m_velocity += totalAcceleration * dt;
    m_velocity = m_velocity * std::pow(m_damping, dt);
    m_position += m_velocity * dt;

    m_age += dt;

    m_pose = physx::PxTransform(m_position.toPxVec3());

    clearForces();
}

void Particle::addForce(const Vector3D& force)
{
    m_forceAccum += force;
}

void Particle::clearForces()
{
    m_forceAccum = Vector3D(0.0f, 0.0f, 0.0f);
}

void Particle::applyForceGenerator(ForceGenerator* generator, float dt)
{
    addForce(generator->calculateForce(*this, dt));
}

Particle* Particle::clone(Vector3D position, Vector3D velocity) const
{
    return new Particle(
        position,
        velocity,
        m_acceleration,
        m_size,
        m_mass,
        m_color,
        m_damping,
        m_life,
        true
    );
}

bool Particle::isAlive() const
{
    return m_age < m_life;
}

Vector3D Particle::getPosition() const
{
    return m_position;
}

Vector3D Particle::getVelocity() const
{
    return m_velocity;
}

float Particle::getMass() const
{
    return m_mass;
}

float Particle::getSize() const
{
    return m_size;
}