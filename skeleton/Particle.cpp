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
    m_forceAccum(0.0f, 0.0f, 0.0f),
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
    // Aceleración producida por las fuerzas
    Vector3D forceAcceleration(0.0f, 0.0f, 0.0f);

    if (m_mass > 0.0f)
    {
        forceAcceleration = m_forceAccum * (1.0f / m_mass);
    }

    // sumamos aceleración constante + aceleración causada por fuerzas
    Vector3D totalAcceleration = m_acceleration + forceAcceleration;


    // Euler semiimplícito
    m_velocity += totalAcceleration * dt;

    m_velocity = m_velocity * std::pow(m_damping, dt);

    m_position += m_velocity * dt;

    // vida de la particula
    m_age += dt;

    // movemos la particula
    m_pose = physx::PxTransform(m_position.toPxVec3());

    // las fuerzas solo pertenecen a este frame
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


bool Particle::isAlive() const
{
    return m_age < m_life;
}