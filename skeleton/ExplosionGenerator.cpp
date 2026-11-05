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


// Calcula la fuerza radial de la explosión
void ExplosionGenerator::updateForce(
    Particle* particle,
    float dt
)
{
    Vector3D direction =
        particle->getPosition() - m_center;

    float distance =
        direction.magnitude();


    // Fuera del radio no actúa la explosión
    if (distance >= m_radius)
        return;


    // Evitamos división por cero
    if (distance < 0.001f)
        return;


    // La explosión pierde fuerza con el tiempo
    float decay =
        std::exp(-m_time / m_tau);


    // Fuerza:
    // F = K / r² * dirección * e^(-t/tau)
    Vector3D force =
        direction *
        (
            (m_strength / (distance * distance))
            * decay
            );


    particle->addForce(force);
}


// Avanza el tiempo de la explosión
void ExplosionGenerator::update(float dt)
{
    m_time += dt;
}


// Reinicia la explosión
void ExplosionGenerator::reset()
{
    m_time = 0.0f;
}


// A partir de 4*tau se considera prácticamente extinguida
bool ExplosionGenerator::isFinished() const
{
    return m_time >= 4.0f * m_tau;
}