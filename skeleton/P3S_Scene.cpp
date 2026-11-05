#include "P3S_Scene.h"

#include <cmath>
#include <iostream>

void P3S_Scene::init()
{
    // ==================================================
    // ACTIVIDAD 1 - GRAVEDAD
    // ==================================================

    m_gravedadNormal = new GravityGenerator(
        Vector3D(0.0f, -10.0f, 0.0f)
    );

    m_gravedadReducida = new GravityGenerator(
        Vector3D(0.0f, -3.0f, 0.0f)
    );


    // Gravedad normal mediante fuerza
    m_emisorGravedadNormal = new EmisorParticula(
        Vector3D(-10.0f, 0.0f, 0.0f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        Vector4(1.0f, 0.0f, 0.0f, 1.0f),
        0.25f,
        1.0f,
        5.0f,
        2,
        1,
        0.99f,
        30.0f
    );

    m_emisorGravedadNormal->addForceGenerator(
        m_gravedadNormal
    );


    // Gravedad reducida con una masa mayor
    m_emisorGravedadReducida = new EmisorParticula(
        Vector3D(0.0f, 0.0f, 0.0f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        Vector4(0.0f, 1.0f, 0.0f, 1.0f),
        0.25f,
        5.0f,
        5.0f,
        2,
        1,
        0.99f,
        30.0f
    );

    m_emisorGravedadReducida->addForceGenerator(
        m_gravedadReducida
    );


    // Comparación con gravedad como aceleración directa
    m_emisorAceleracion = new EmisorParticula(
        Vector3D(10.0f, 0.0f, 0.0f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        Vector4(0.0f, 0.0f, 1.0f, 1.0f),
        0.25f,
        1.0f,
        5.0f,
        2,
        1,
        0.99f,
        30.0f
    );

    m_emisorAceleracion->setAcceleration(
        Vector3D(0.0f, -10.0f, 0.0f)
    );


    // ==================================================
    // ACTIVIDAD 2 - VIENTO
    // ==================================================

    m_viento = new WindGenerator(
        Vector3D(8.0f, 0.0f, 0.0f),
        1.0f,
        0.0f
    );

    m_emisorViento = new EmisorParticula(
        Vector3D(-10.0f, 0.0f, -15.0f),
        Vector3D(0.0f, 12.0f, 0.0f),
        Vector3D(1.0f, 1.0f, 1.0f),
        Vector4(1.0f, 1.0f, 0.0f, 1.0f),
        0.25f,
        1.0f,
        5.0f,
        2,
        1,
        0.99f,
        30.0f
    );

    // Gravedad + viento
    m_emisorViento->addForceGenerator(m_gravedadNormal);
    m_emisorViento->addForceGenerator(m_viento);


    // ==================================================
    // ACTIVIDAD 3 - TORBELLINO
    // ==================================================

    m_torbellino = new VortexGenerator(
        Vector3D(10.0f, 0.0f, -15.0f),
        0.8f,
        12.0f,
        1.0f
    );

    m_emisorTorbellino = new EmisorParticula(
        Vector3D(10.0f, 0.0f, -15.0f),
        Vector3D(0.0f, 8.0f, 0.0f),
        Vector3D(4.0f, 2.0f, 4.0f),
        Vector4(1.0f, 0.0f, 1.0f, 1.0f),
        0.20f,
        1.0f,
        6.0f,
        3,
        1,
        0.99f,
        25.0f
    );

    // Gravedad reducida + torbellino
    m_emisorTorbellino->addForceGenerator(m_gravedadReducida);
    m_emisorTorbellino->addForceGenerator(m_torbellino);


    // ==================================================
    // ACTIVIDAD 4 - EXPLOSION
    // ==================================================

    Vector3D explosionCenter(0.0f, 5.0f, 15.0f);

    m_explosion = new ExplosionGenerator(
        explosionCenter,
        12.0f,
        100.0f,
        1.0f
    );

    int numParticles = 12;
    float circleRadius = 6.0f;

    for (int i = 0; i < numParticles; i++)
    {
        float angle = (2.0f * 3.14159f * i) / numParticles;

        Vector3D position(
            explosionCenter.x + std::cos(angle) * circleRadius,
            explosionCenter.y,
            explosionCenter.z + std::sin(angle) * circleRadius
        );

        // Distintas masas para comparar el efecto
        float mass;

        if (i % 3 == 0)
            mass = 1.0f;
        else if (i % 3 == 1)
            mass = 3.0f;
        else
            mass = 6.0f;

        Particle* particle = new Particle(
            position,
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            0.4f,
            mass,
            Vector4(1.0f, 0.5f, 0.0f, 1.0f),
            0.99f,
            30.0f
        );

        m_particulasExplosion.push_back(particle);

        m_explosionRegistry.add(
            particle,
            m_explosion
        );
    }
}


void P3S_Scene::update(double dt)
{
    float deltaTime = (float)dt;


    // ACTIVIDAD 1

    if (m_emisorGravedadNormal)
        m_emisorGravedadNormal->update(deltaTime);

    if (m_emisorGravedadReducida)
        m_emisorGravedadReducida->update(deltaTime);

    if (m_emisorAceleracion)
        m_emisorAceleracion->update(deltaTime);


    // ACTIVIDAD 2

    if (m_emisorViento)
        m_emisorViento->update(deltaTime);


    // ACTIVIDAD 3

    if (m_emisorTorbellino)
        m_emisorTorbellino->update(deltaTime);


    // ACTIVIDAD 4

    if (m_explosionActiva)
    {
        // Avanza el tiempo de la explosión
        m_explosion->update(deltaTime);

        // Aplica la fuerza a las partículas
        m_explosionRegistry.updateForces(deltaTime);

        if (m_explosion->isFinished())
            m_explosionActiva = false;
    }

    // Las partículas siguen moviéndose
    // después de terminar la explosión
    for (Particle* p : m_particulasExplosion)
        p->integrate(deltaTime);
}


void P3S_Scene::keyPress(
    unsigned char key,
    const physx::PxTransform& camera
)
{
    // E activa la explosión
    if (key == 'e' || key == 'E')
    {
        m_explosion->reset();

        m_explosionActiva = true;

        std::cout << "Explosion activada" << std::endl;
    }
}


void P3S_Scene::cleanup()
{
    // EMISORES

    delete m_emisorGravedadNormal;
    m_emisorGravedadNormal = nullptr;

    delete m_emisorGravedadReducida;
    m_emisorGravedadReducida = nullptr;

    delete m_emisorAceleracion;
    m_emisorAceleracion = nullptr;

    delete m_emisorViento;
    m_emisorViento = nullptr;

    delete m_emisorTorbellino;
    m_emisorTorbellino = nullptr;


    // PARTICULAS EXPLOSION

    m_explosionRegistry.clear();

    for (Particle* p : m_particulasExplosion)
        delete p;

    m_particulasExplosion.clear();


    // GENERADORES

    delete m_gravedadNormal;
    m_gravedadNormal = nullptr;

    delete m_gravedadReducida;
    m_gravedadReducida = nullptr;

    delete m_viento;
    m_viento = nullptr;

    delete m_torbellino;
    m_torbellino = nullptr;

    delete m_explosion;
    m_explosion = nullptr;
}