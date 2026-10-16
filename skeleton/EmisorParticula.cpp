#include "EmisorParticula.h"

#include <algorithm>
#include <cmath>
#include <random>


EmisorParticula::EmisorParticula(
    Vector3D position,
    Vector3D meanVelocity,
    Vector3D velocityDeviation,
    Vector4 color,
    float size,
    float mass,
    float life,
    int meanParticlesPerFrame,
    int variationParticlesPerFrame,
    float damping,
    float maxDistance
)
    : m_position(position),
    m_meanVelocity(meanVelocity),
    m_velocityDeviation(velocityDeviation),
    m_color(color),
    m_size(size),
    m_mass(mass),
    m_life(life),
    m_meanParticlesPerFrame(meanParticlesPerFrame),
    m_variationParticlesPerFrame(variationParticlesPerFrame),
    m_damping(damping),
    m_maxDistance(maxDistance),
    m_gravity(0.0f, -10.0f, 0.0f)
{
    std::random_device rd;
    m_generator.seed(rd());
}


EmisorParticula::~EmisorParticula()
{
    for (Particle* p : m_particles)
    {
        delete p;
    }

    m_particles.clear();
}

Vector3D EmisorParticula::randomVelocity()
{
    std::normal_distribution<float> distributionX(
        m_meanVelocity.x,
        m_velocityDeviation.x
    );

    std::normal_distribution<float> distributionY(
        m_meanVelocity.y,
        m_velocityDeviation.y
    );

    std::normal_distribution<float> distributionZ(
        m_meanVelocity.z,
        m_velocityDeviation.z
    );

    return Vector3D(
        distributionX(m_generator),
        distributionY(m_generator),
        distributionZ(m_generator)
    );
}

int EmisorParticula::randomParticleCount()
{
    std::uniform_int_distribution<int> distribution(
        -m_variationParticlesPerFrame,
        m_variationParticlesPerFrame
    );

    int number =
        m_meanParticlesPerFrame +
        distribution(m_generator);

    if (number < 0)
        number = 0;

    return number;
}

void EmisorParticula::emit()
{
    int numberParticles = randomParticleCount();

    for (int i = 0; i < numberParticles; i++)
    {
        Vector3D velocity = randomVelocity();

        Particle* particle = new Particle(
            m_position,
            velocity,
            m_gravity,
            m_size,
            m_mass,
            m_color,
            m_damping,
            m_life
        );

        m_particles.push_back(particle);
    }
}

void EmisorParticula::removeDeadParticles()
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        Particle* p = *it;

        Vector3D distance =
            p->getPosition() - m_position;

        bool outside =
            distance.magnitude() > m_maxDistance;

        if (!p->isAlive() || outside)
        {
            delete p;

            it = m_particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EmisorParticula::update(float dt)
{
    //Generar partículas
    emit();

    // Actualizar las existentes
    for (Particle* p : m_particles)
    {
        p->integrate(dt);
    }

    // Eliminar las muertas
    removeDeadParticles();
}