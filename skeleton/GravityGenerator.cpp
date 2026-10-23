#include "GravityGenerator.h"
#include "Particle.h"


// Calcula la fuerza gravitatoria que actúa

void GravityGenerator::updateForce(Particle* particle,float dt)
{
    Vector3D force = m_gravity * particle->getMass();

    //  añadimos la fuerza al acumulador
    particle->addForce(force);
}