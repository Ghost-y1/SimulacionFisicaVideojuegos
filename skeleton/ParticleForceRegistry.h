#pragma once

#include <vector>

#include "Particle.h"
#include "ForceGenerator.h"

// Registro que relaciona partículas con generadores de fuerzas.
// Se encarga de aplicar a cada partícula todos los generadores

class ParticleForceRegistry
{
private:

    // Cada registro guarda una pareja de una partícula y el generador que actúa sobre ella.
    struct Registration
    {
        Particle* particle;
        ForceGenerator* generator;
    };

    // Lista de todas las asociaciones partícula-generador.
    std::vector<Registration> registrations;

public:

    // Asocia un generador de fuerzas a una partícula.
    void add(Particle* particle, ForceGenerator* generator);

    // Elimina todas las asociaciones correspondientes
    void remove(Particle* particle);

    // Vacía completamente el registro.
    void clear();

    // Recorre todos los registros y aplica las fuerzas
    void updateForces(float dt);
};