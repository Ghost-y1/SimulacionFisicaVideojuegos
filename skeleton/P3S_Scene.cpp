#include "P3S_Scene.h"

#include <cmath>
#include <iostream>

void P3S_Scene::init()
{
    // GENERADORES

    m_gravity = new GravityGenerator(
        Vector3D(0.0f, -10.0f, 0.0f)
    );

    m_reducedGravity = new GravityGenerator(
        Vector3D(0.0f, -3.0f, 0.0f)
    );

    m_wind = new WindGenerator(
        Vector3D(8.0f, 0.0f, 0.0f),
        1.0f
    );

    m_vortex = new VortexGenerator(
        Vector3D(10.0f, 0.0f, -15.0f),
        0.8f,
        12.0f,
        1.0f
    );

    m_explosion = new ExplosionGenerator(
        Vector3D(0.0f, 5.0f, 15.0f),
        12.0f,
        100.0f,
        1.0f
    );


    // ACTIVIDAD 1 - GRAVEDAD NORMAL

    m_gravitySystem = new ParticleSystem();

    Particle* gravityModel = new Particle(
        Vector3D(), Vector3D(), Vector3D(),
        0.25f, 1.0f,
        Vector4(1.0f, 0.0f, 0.0f, 1.0f),
        0.99f, 5.0f, false
    );

    EmisorParticula* gravityEmitter = new EmisorParticula(
        gravityModel,
        Vector3D(-10.0f, 0.0f, 0.0f),
        Vector3D(0.2f, 0.0f, 0.2f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        DistributionType::Uniform,
        2, 1
    );

    m_gravitySystem->addEmitter(gravityEmitter);
    m_gravitySystem->addForceGenerator(m_gravity);


    // GRAVEDAD REDUCIDA + MASA DIFERENTE

    m_reducedGravitySystem = new ParticleSystem();

    Particle* reducedModel = new Particle(
        Vector3D(), Vector3D(), Vector3D(),
        0.25f, 5.0f,
        Vector4(0.0f, 1.0f, 0.0f, 1.0f),
        0.99f, 5.0f, false
    );

    EmisorParticula* reducedEmitter = new EmisorParticula(
        reducedModel,
        Vector3D(0.0f, 0.0f, 0.0f),
        Vector3D(0.2f, 0.0f, 0.2f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        DistributionType::Uniform,
        2, 1
    );

    m_reducedGravitySystem->addEmitter(reducedEmitter);
    m_reducedGravitySystem->addForceGenerator(m_reducedGravity);


    // GRAVEDAD COMO ACELERACIÓN

    m_accelerationSystem = new ParticleSystem();

    Particle* accelerationModel = new Particle(
        Vector3D(),
        Vector3D(),
        Vector3D(0.0f, -10.0f, 0.0f),
        0.25f,
        1.0f,
        Vector4(0.0f, 0.0f, 1.0f, 1.0f),
        0.99f,
        5.0f,
        false
    );

    EmisorParticula* accelerationEmitter = new EmisorParticula(
        accelerationModel,
        Vector3D(10.0f, 0.0f, 0.0f),
        Vector3D(0.2f, 0.0f, 0.2f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        DistributionType::Uniform,
        2, 1
    );

    m_accelerationSystem->addEmitter(accelerationEmitter);


    // ACTIVIDAD 2 - VIENTO

    m_windSystem = new ParticleSystem();

    Particle* windModel = new Particle(
        Vector3D(), Vector3D(), Vector3D(),
        0.25f, 1.0f,
        Vector4(1.0f, 1.0f, 0.0f, 1.0f),
        0.99f, 5.0f, false
    );

    EmisorParticula* windEmitter = new EmisorParticula(
        windModel,
        Vector3D(-10.0f, 0.0f, -15.0f),
        Vector3D(0.5f, 0.0f, 0.5f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        DistributionType::Gaussian,
        2, 1
    );

    m_windSystem->addEmitter(windEmitter);
    m_windSystem->addForceGenerator(m_gravity);
    m_windSystem->addForceGenerator(m_wind);


    // ACTIVIDAD 3 - TORBELLINO

    m_vortexSystem = new ParticleSystem();

    Particle* vortexModel = new Particle(
        Vector3D(), Vector3D(), Vector3D(),
        0.20f, 1.0f,
        Vector4(1.0f, 0.0f, 1.0f, 1.0f),
        0.99f, 6.0f, false
    );

    EmisorParticula* vortexEmitter = new EmisorParticula(
        vortexModel,
        Vector3D(10.0f, 0.0f, -15.0f),
        Vector3D(4.0f, 0.5f, 4.0f),
        Vector3D(0.0f, 8.0f, 0.0f),
        Vector3D(2.0f, 1.0f, 2.0f),
        DistributionType::Gaussian,
        3, 1
    );

    m_vortexSystem->addEmitter(vortexEmitter);
    m_vortexSystem->addForceGenerator(m_reducedGravity);
    m_vortexSystem->addForceGenerator(m_vortex);


    // ACTIVIDAD 4 - EXPLOSIÓN

    m_explosionSystem = new ParticleSystem();

    Vector3D center(0.0f, 5.0f, 15.0f);

    for (int i = 0; i < 12; i++)
    {
        float angle = (2.0f * 3.14159f * i) / 12.0f;

        Vector3D position(
            center.x + std::cos(angle) * 6.0f,
            center.y,
            center.z + std::sin(angle) * 6.0f
        );

        float mass = 1.0f;

        if (i % 3 == 1)
            mass = 3.0f;
        else if (i % 3 == 2)
            mass = 6.0f;

        Particle* particle = new Particle(
            position,
            Vector3D(),
            Vector3D(),
            0.4f,
            mass,
            Vector4(1.0f, 0.5f, 0.0f, 1.0f),
            0.99f,
            30.0f
        );

        m_explosionSystem->addParticle(particle);
    }

    // Empieza desactivada
    m_explosionSystem->addForceGenerator(
        m_explosion,
        false
    );
}

void P3S_Scene::update(double dt)
{
    float deltaTime = (float)dt;

    m_gravitySystem->update(deltaTime);
    m_reducedGravitySystem->update(deltaTime);
    m_accelerationSystem->update(deltaTime);

    m_windSystem->update(deltaTime);
    m_vortexSystem->update(deltaTime);
    m_explosionSystem->update(deltaTime);

    if (m_explosion->isFinished())
        m_explosionSystem->setForceActive(m_explosion, false);
}

void P3S_Scene::keyPress(
    unsigned char key,
    const physx::PxTransform& camera
)
{
    if (key == 'g' || key == 'G')
    {
        m_gravitySystem->toggleForce(m_gravity);
        m_windSystem->toggleForce(m_gravity);
    }

    if (key == 'r' || key == 'R')
    {
        m_reducedGravitySystem->toggleForce(m_reducedGravity);
        m_vortexSystem->toggleForce(m_reducedGravity);
    }

    if (key == 'v' || key == 'V')
    {
        m_windSystem->toggleForce(m_wind);
    }
    if (key == 't' || key == 'T')
        m_vortexSystem->toggleForce(m_vortex);

    if (key == 'e' || key == 'E')
    {
        m_explosion->reset();
        m_explosionSystem->setForceActive(m_explosion, true);

        std::cout << "Explosion activada" << std::endl;
    }
}

void P3S_Scene::cleanup()
{
    delete m_gravitySystem;
    delete m_reducedGravitySystem;
    delete m_accelerationSystem;
    delete m_windSystem;
    delete m_vortexSystem;
    delete m_explosionSystem;

    m_gravitySystem = nullptr;
    m_reducedGravitySystem = nullptr;
    m_accelerationSystem = nullptr;
    m_windSystem = nullptr;
    m_vortexSystem = nullptr;
    m_explosionSystem = nullptr;

    // Los generadores son independientes de los sistemas
    delete m_gravity;
    delete m_reducedGravity;
    delete m_wind;
    delete m_vortex;
    delete m_explosion;

    m_gravity = nullptr;
    m_reducedGravity = nullptr;
    m_wind = nullptr;
    m_vortex = nullptr;
    m_explosion = nullptr;
}