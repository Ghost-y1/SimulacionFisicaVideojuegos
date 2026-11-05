#pragma once

#include "ForceGenerator.h"

#include <vector>

class ParticleForceRegistry
{
public:
    // Añade un generador al registro
    void add(ForceGenerator* generator, bool active = true);

    // Elimina un generador
    void remove(ForceGenerator* generator);

    // Activa o desactiva un generador
    void setActive(ForceGenerator* generator, bool active);

    // Cambia el estado activo/inactivo
    void toggle(ForceGenerator* generator);

    // Devuelve los generadores activos
    std::vector<ForceGenerator*> getActiveGenerators() const;

    // Actualiza los generadores dependientes del tiempo
    void update(float dt);

    void clear();

private:
    struct Registration
    {
        ForceGenerator* generator;
        bool active;
    };

    std::vector<Registration> m_generators;
};