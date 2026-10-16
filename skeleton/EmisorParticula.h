#pragma once

#include "Vector3D.h"
#include "Particle.h"

#include <vector>
#include <random>

class EmisorParticula
{
public:

    EmisorParticula(
        Vector3D position,
        Vector3D meanVelocity,
        Vector3D velocityDeviation,
        Vector4 color,
        float size,
        float mass,
        float life,
        int meanParticlesPerFrame,
        int variationParticlesPerFrame,
        float damping = 1.0f,
        float maxDistance = 30.0f
    );

    ~EmisorParticula();

    void update(float dt);

private:

    // Genera nuevas partículas
    void emit();

    // Elimina las muertas / fuera del área
    void removeDeadParticles();

    // Velocidad aleatoria
    Vector3D randomVelocity();

    // Número de partículas de este frame
    int randomParticleCount();


private:

    std::vector<Particle*> m_particles;

    // Posición fija del emisor
    Vector3D m_position;

    // Velocidad media
    Vector3D m_meanVelocity;

    // Desviación estándar en X, Y, Z
    Vector3D m_velocityDeviation;

    Vector4 m_color;

    float m_size;
    float m_mass;
    float m_life;
    float m_damping;

    // Partículas emitidas por frame
    int m_meanParticlesPerFrame;
    int m_variationParticlesPerFrame;

    // Espacio de acción
    float m_maxDistance;

    // Gravedad común
    Vector3D m_gravity;

    // Generador aleatorio
    std::default_random_engine m_generator;
};