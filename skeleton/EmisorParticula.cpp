#include "EmisorParticula.h"

EmisorParticula::EmisorParticula(
    Particle* model,
    Vector3D position,
    Vector3D positionDeviation,
    Vector3D meanVelocity,
    Vector3D velocityDeviation,
    DistributionType distribution,
    int meanParticlesPerFrame,
    int variationParticlesPerFrame
)
    : m_model(model),
    m_position(position),
    m_positionDeviation(positionDeviation),
    m_meanVelocity(meanVelocity),
    m_velocityDeviation(velocityDeviation),
    m_distribution(distribution),
    m_meanParticlesPerFrame(meanParticlesPerFrame),
    m_variationParticlesPerFrame(variationParticlesPerFrame)
{
    std::random_device rd;
    m_generator.seed(rd());
}

EmisorParticula::~EmisorParticula()
{
    delete m_model;
    m_model = nullptr;
}

Vector3D EmisorParticula::randomPosition()
{
    if (m_distribution == DistributionType::Uniform)
    {
        std::uniform_real_distribution<float> x(-m_positionDeviation.x, m_positionDeviation.x);
        std::uniform_real_distribution<float> y(-m_positionDeviation.y, m_positionDeviation.y);
        std::uniform_real_distribution<float> z(-m_positionDeviation.z, m_positionDeviation.z);

        return m_position + Vector3D(
            x(m_generator),
            y(m_generator),
            z(m_generator)
        );
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (m_positionDeviation.x > 0.0f)
    {
        std::normal_distribution<float> distribution(0.0f, m_positionDeviation.x);
        x = distribution(m_generator);
    }

    if (m_positionDeviation.y > 0.0f)
    {
        std::normal_distribution<float> distribution(0.0f, m_positionDeviation.y);
        y = distribution(m_generator);
    }

    if (m_positionDeviation.z > 0.0f)
    {
        std::normal_distribution<float> distribution(0.0f, m_positionDeviation.z);
        z = distribution(m_generator);
    }

    return m_position + Vector3D(x, y, z);
}

Vector3D EmisorParticula::randomVelocity()
{
    float x = m_meanVelocity.x;
    float y = m_meanVelocity.y;
    float z = m_meanVelocity.z;

    if (m_velocityDeviation.x > 0.0f)
    {
        std::normal_distribution<float> distribution(
            m_meanVelocity.x,
            m_velocityDeviation.x
        );

        x = distribution(m_generator);
    }

    if (m_velocityDeviation.y > 0.0f)
    {
        std::normal_distribution<float> distribution(
            m_meanVelocity.y,
            m_velocityDeviation.y
        );

        y = distribution(m_generator);
    }

    if (m_velocityDeviation.z > 0.0f)
    {
        std::normal_distribution<float> distribution(
            m_meanVelocity.z,
            m_velocityDeviation.z
        );

        z = distribution(m_generator);
    }

    return Vector3D(x, y, z);
}

int EmisorParticula::randomParticleCount()
{
    std::uniform_int_distribution<int> distribution(
        -m_variationParticlesPerFrame,
        m_variationParticlesPerFrame
    );

    int number =
        m_meanParticlesPerFrame + distribution(m_generator);

    if (number < 0)
        number = 0;

    return number;
}

std::vector<Particle*> EmisorParticula::emit()
{
    std::vector<Particle*> particles;

    int number = randomParticleCount();

    for (int i = 0; i < number; i++)
    {
        Particle* particle = m_model->clone(
            randomPosition(),
            randomVelocity()
        );

        particles.push_back(particle);
    }

    return particles;
}