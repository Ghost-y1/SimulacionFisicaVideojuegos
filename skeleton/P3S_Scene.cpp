#include "P3S_Scene.h"

#include <iostream>
#include <cmath>


void P3S_Scene::init()
{
    // ACTIVIDAD 1 - GRAVEDAD

    m_gravedadNormal = new GravityGenerator(Vector3D(0.0f, -10.0f, 0.0f));


    m_gravedadReducida = new GravityGenerator(Vector3D(0.0f, -3.0f, 0.0f));


    // Gravedad normal por fuerza
    m_emisorGravedadNormal = new EmisorParticula(
        Vector3D(-8.0f, 0.0f, 0.0f),
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


    m_emisorGravedadNormal->addForceGenerator(m_gravedadNormal);

    // Gravedad reducida
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


    // Gravedad directamente como aceleración
    m_emisorAceleracion = new EmisorParticula(
        Vector3D(8.0f, 0.0f, 0.0f),
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


    m_emisorAceleracion->setAcceleration(Vector3D(0.0f,-10.0f,0.0f));

    // ACTIVIDAD 2 - Viento

    m_windGenerator = new WindGenerator(Vector3D(10.0f, 0.0f, 0.0f),5.0f,5.0f);

    // emisor afectado por el viento
    m_emisorViento = new EmisorParticula(
        Vector3D(-8.0f, 10.0f, 0.0f),
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

    m_emisorViento->addForceGenerator(m_windGenerator);
    m_emisorViento->addForceGenerator(m_gravedadNormal);
}



void P3S_Scene::update(double dt)
{
    float deltaTime = (float)dt;


    // Actividad 1
    m_emisorGravedadNormal->update(deltaTime);
    m_emisorGravedadReducida->update(deltaTime);
    m_emisorAceleracion->update(deltaTime);

    // Actividad 2
    m_emisorViento->update(deltaTime);

}



void P3S_Scene::keyPress(
    unsigned char key,
    const physx::PxTransform& camera
)
{
}



void P3S_Scene::cleanup()
{
    // Emisores
    delete m_emisorGravedadNormal;
    m_emisorGravedadNormal = nullptr;

    delete m_emisorGravedadReducida;
    m_emisorGravedadReducida = nullptr;

    delete m_emisorAceleracion;
    m_emisorAceleracion = nullptr;

    delete m_emisorViento;
    m_emisorViento = nullptr;

    // Generadores
    delete m_gravedadNormal;
    m_gravedadNormal = nullptr;

    delete m_gravedadReducida;
    m_gravedadReducida = nullptr;

    delete m_windGenerator;
    m_windGenerator = nullptr;
}