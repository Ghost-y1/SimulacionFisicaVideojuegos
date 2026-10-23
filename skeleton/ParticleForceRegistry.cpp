#include "ParticleForceRegistry.h"


// Registra una nueva pareja 
void ParticleForceRegistry::add(Particle* particle,ForceGenerator* generator)
{
    registrations.push_back({ particle, generator });
}


// Elimina del registro todos los generadores asociados a una  partícula.
void ParticleForceRegistry::remove(Particle* particle)
{
    for (auto it = registrations.begin();
        it != registrations.end(); )
    {
        if (it->particle == particle)
        {
            // erase devuelve el iterador al siguiente elemento.
            it = registrations.erase(it);
        }
        else
        {
            ++it;
        }
    }
}


// Elimina todas las asociaciones existentes.
void ParticleForceRegistry::clear()
{
    registrations.clear();
}


// Aplica todos los generadores registrados.
void ParticleForceRegistry::updateForces(float dt)
{
    for (Registration& registration : registrations)
    {
        registration.generator->updateForce(
            registration.particle,
            dt
        );
    }
}