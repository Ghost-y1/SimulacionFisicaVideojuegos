#include "P2S_Scene.h"


void P2S_Scene::init()
{
    // EMISOR 1 FUENTE

    EmisorParticula* fuente = new EmisorParticula(
        Vector3D(-7.0f, 0.0f, 0.0f),     // posición

        Vector3D(0.0f, 10.0f, 0.0f),     // velocidad media

        Vector3D(1.5f, 1.0f, 1.5f),      // desviación velocidad

        Vector4(0.0f, 0.5f, 1.0f, 1.0f), // azul

        0.20f,                            // tamaño
        1.0f,                             // masa
        4.0f,                             // vida

        2,                                // partículas/frame
        1,                                // variación

        0.99f,                            // damping
        30.0f                             // distancia máxima
    );

    m_emitters.push_back(fuente);



    // EMISOR 2 - CHORRO MANGUERA

    EmisorParticula* manguera = new EmisorParticula(
        Vector3D(0.0f, 5.0f, 0.0f),

        // principalmente hacia +X
        Vector3D(10.0f, 4.0f, 0.0f),

        // pequeña dispersión
        Vector3D(1.0f, 1.0f, 1.0f),

        Vector4(0.0f, 1.0f, 1.0f, 1.0f),

        0.15f,
        1.0f,
        3.0f,

        3,
        1,

        0.99f,
        30.0f
    );

    m_emitters.push_back(manguera);



    // EMISOR 3 CHISPAS

    EmisorParticula* chispas = new EmisorParticula(
        Vector3D(7.0f, 0.0f, 0.0f),

        // salen principalmente hacia arriba
        Vector3D(0.0f, 12.0f, 0.0f),

        // mucha dispersión
        Vector3D(5.0f, 2.0f, 5.0f),

        Vector4(1.0f, 0.5f, 0.0f, 1.0f),

        0.10f,
        1.0f,
        2.0f,

        4,
        2,

        0.98f,
        30.0f
    );

    m_emitters.push_back(chispas);
}

void P2S_Scene::update(double dt)
{
    for (EmisorParticula* emitter : m_emitters)
    {
        emitter->update((float)dt);
    }
}

void P2S_Scene::keyPress( unsigned char key, const physx::PxTransform& camera)
{
}

void P2S_Scene::cleanup()
{
    for (EmisorParticula* emitter : m_emitters)
    {
        delete emitter;
    }

    m_emitters.clear();
}