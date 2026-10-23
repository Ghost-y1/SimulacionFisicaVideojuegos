#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ForceGenerator.h"
#include "ParticleForceRegistry.h"

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

    // Actualiza el sistema de partículas
    void update(float dt);

    // Añade un generador de fuerzas al emisor
    void addForceGenerator(ForceGenerator* generator);

    // Establece una aceleración constante
    void setAcceleration(const Vector3D& acceleration);

private:

    // Genera nuevas partículas
    void emit();

    // Elimina partículas muertas o fuera del área
    void removeDeadParticles();

    // Genera una velocidad aleatoria
    Vector3D randomVelocity();

    // Calcula cuántas partículas se generan este frame
    int randomParticleCount();


    std::vector<Particle*> m_particles;

    Vector3D m_position;

    // Velocidad media de salida
    Vector3D m_meanVelocity;

    // Variación de velocidad
    Vector3D m_velocityDeviation;

    Vector4 m_color;

    float m_size;
    float m_mass;
    float m_life;
    float m_damping;

    int m_meanParticlesPerFrame;
    int m_variationParticlesPerFrame;

    float m_maxDistance;

    // Aceleración constante de las partículas
    Vector3D m_acceleration;

    // Generador de números aleatorios
    std::default_random_engine m_generator;

    // Generadores de fuerza asociados
    std::vector<ForceGenerator*> m_forceGenerators;

    // Registro partícula-generador
    ParticleForceRegistry m_forceRegistry;
};