#pragma once

#include "Particle.h"

#include <random>
#include <vector>

enum class DistributionType
{
    Uniform,
    Gaussian
};

class EmisorParticula
{
public:
    EmisorParticula(
        Particle* model,
        Vector3D position,
        Vector3D positionDeviation,
        Vector3D meanVelocity,
        Vector3D velocityDeviation,
        DistributionType distribution,
        int meanParticlesPerFrame,
        int variationParticlesPerFrame
    );

    ~EmisorParticula();

    // Devuelve las nuevas partículas creadas este frame
    std::vector<Particle*> emit();

private:
    Vector3D randomPosition();
    Vector3D randomVelocity();

    int randomParticleCount();

    // Partícula usada como modelo
    Particle* m_model;

    Vector3D m_position;
    Vector3D m_positionDeviation;

    Vector3D m_meanVelocity;
    Vector3D m_velocityDeviation;

    DistributionType m_distribution;

    int m_meanParticlesPerFrame;
    int m_variationParticlesPerFrame;

    std::default_random_engine m_generator;
};