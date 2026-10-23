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
    m_acceleration(0.0f, 0.0f, 0.0f),
    m_color(color),
    m_size(size),
    m_mass(mass),
    m_life(life),
    m_damping(damping),
    m_meanParticlesPerFrame(meanParticlesPerFrame),
    m_variationParticlesPerFrame(variationParticlesPerFrame),
    m_maxDistance(maxDistance)
{
    // Inicializa el generador aleatorio
    std::random_device rd;
    m_generator.seed(rd());
}


EmisorParticula::~EmisorParticula()
{
    // Libera todas las partículas
    for (Particle* p : m_particles)
    {
        delete p;
    }

    m_particles.clear();
}


// Genera una velocidad aleatoria alrededor de la media
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


// Calcula el número de partículas a emitir
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


// Crea nuevas partículas
void EmisorParticula::emit()
{
    int numberParticles =
        randomParticleCount();

    for (int i = 0; i < numberParticles; i++)
    {
        Vector3D velocity =
            randomVelocity();

        Particle* particle =
            new Particle(
                m_position,
                velocity,
                m_acceleration,
                m_size,
                m_mass,
                m_color,
                m_damping,
                m_life
            );

        m_particles.push_back(particle);

        // Asocia la partícula a los generadores
        for (ForceGenerator* generator : m_forceGenerators)
        {
            m_forceRegistry.add(
                particle,
                generator
            );
        }
    }
}


// Cambia la aceleración constante
void EmisorParticula::setAcceleration(
    const Vector3D& acceleration
)
{
    m_acceleration = acceleration;
}


// Elimina partículas muertas o demasiado lejanas
void EmisorParticula::removeDeadParticles()
{
    for (auto it = m_particles.begin();
        it != m_particles.end(); )
    {
        Particle* p = *it;

        Vector3D distance =
            p->getPosition() - m_position;

        bool outside =
            distance.magnitude() > m_maxDistance;

        if (!p->isAlive() || outside)
        {
            m_forceRegistry.remove(p);

            delete p;

            it = m_particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}


// Actualiza emisión, fuerzas e integración
void EmisorParticula::update(float dt)
{
    emit();

    m_forceRegistry.updateForces(dt);

    for (Particle* p : m_particles)
    {
        p->integrate(dt);
    }

    removeDeadParticles();
}


// Añade un generador de fuerzas
void EmisorParticula::addForceGenerator(
    ForceGenerator* generator
)
{
    m_forceGenerators.push_back(generator);
}