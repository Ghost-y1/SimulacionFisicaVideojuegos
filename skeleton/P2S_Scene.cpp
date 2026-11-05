#include "P2S_Scene.h"

void P2S_Scene::init()
{
    m_system = new ParticleSystem();

    m_gravity = new GravityGenerator(
        Vector3D(0.0f, -10.0f, 0.0f)
    );

    // Modelo azul
    Particle* waterModel = new Particle(
        Vector3D(),
        Vector3D(),
        Vector3D(),
        0.15f,
        1.0f,
        Vector4(0.0f, 0.5f, 1.0f, 1.0f),
        0.99f,
        5.0f,
        false
    );

    // Modelo amarillo
    Particle* sparkModel = new Particle(
        Vector3D(),
        Vector3D(),
        Vector3D(),
        0.10f,
        0.5f,
        Vector4(1.0f, 0.6f, 0.0f, 1.0f),
        0.98f,
        3.0f,
        false
    );

    // Modelo de niebla
    Particle* fogModel = new Particle(
        Vector3D(),
        Vector3D(),
        Vector3D(0.0f, 0.5f, 0.0f),
        0.20f,
        0.2f,
        Vector4(0.7f, 0.7f, 0.7f, 0.5f),
        1.0f,
        8.0f,
        false
    );

    // Distribución uniforme
    m_uniformEmitter = new EmisorParticula(
        waterModel,
        Vector3D(-8.0f, 0.0f, 0.0f),
        Vector3D(0.5f, 0.0f, 0.5f),
        Vector3D(0.0f, 10.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        DistributionType::Uniform,
        2,
        1
    );

    // Distribución gaussiana
    m_gaussianEmitter = new EmisorParticula(
        sparkModel,
        Vector3D(0.0f, 0.0f, 0.0f),
        Vector3D(1.0f, 0.2f, 1.0f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(4.0f, 2.0f, 4.0f),
        DistributionType::Gaussian,
        3,
        1
    );

    // Niebla
    m_fogEmitter = new EmisorParticula(
        fogModel,
        Vector3D(8.0f, 2.0f, 0.0f),
        Vector3D(5.0f, 1.0f, 5.0f),
        Vector3D(0.0f, 0.2f, 0.0f),
        Vector3D(0.2f, 0.2f, 0.2f),
        DistributionType::Uniform,
        2,
        1
    );

    m_system->addEmitter(m_uniformEmitter);
    m_system->addEmitter(m_gaussianEmitter);
    m_system->addEmitter(m_fogEmitter);

    m_system->addForceGenerator(m_gravity);
}

void P2S_Scene::update(double dt)
{
    m_system->update((float)dt);
}

void P2S_Scene::keyPress(
    unsigned char key,
    const physx::PxTransform& camera
)
{
}

void P2S_Scene::cleanup()
{
    delete m_system;
    m_system = nullptr;

    delete m_gravity;
    m_gravity = nullptr;

    // Los emisores los destruye ParticleSystem
    m_uniformEmitter = nullptr;
    m_gaussianEmitter = nullptr;
    m_fogEmitter = nullptr;
}