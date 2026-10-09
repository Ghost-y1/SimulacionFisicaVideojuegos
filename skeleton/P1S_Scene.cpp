#include "P1S_Scene.h"
#include <iostream>


void P1S_Scene::init()
{
    recalcularParametros();
}


void P1S_Scene::update(double dt)
{
    for (Particle* p : proyectiles)
    {
        p->integrate(dt);
    }
}


void P1S_Scene::keyPress( unsigned char key, const physx::PxTransform& camera)
{
    if (key == 'j' || key == 'J')
    {
        Vector3D gravedad( 0.0f, -gravedadSimulada, 0.0f);
        disparaProyectil(velocidadSimulada, gravedad);
    }
}


void P1S_Scene::cleanup()
{
    for (Particle* p : proyectiles)
    {
        delete p;
    }

    proyectiles.clear();
}


void P1S_Scene::disparaProyectil(float speed,Vector3D acceleration)
{
    Vector3D position = GetCamera()->getEye();

    Vector3D velocity = GetCamera()->getDir() * speed;

    Particle* p = new Particle(position,velocity,acceleration, masaSimulada);

    proyectiles.push_back(p);
}


void P1S_Scene::recalcularParametros()
{
    float factor = velocidadSimulada / velocidadReal;

    masaSimulada = masaReal / (factor * factor);

    gravedadSimulada = 9.81f * factor * factor;
}