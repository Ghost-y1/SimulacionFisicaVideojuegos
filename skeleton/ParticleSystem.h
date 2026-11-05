#pragma once

#include "Particle.h"
#include "EmisorParticula.h"
#include "ForceGenerator.h"

#include <vector>

class ParticleSystem
{
public:
    ~ParticleSystem();

    void addParticle(Particle* particle);

    void addEmitter(EmisorParticula* emitter);

    void addForceGenerator(
        ForceGenerator* generator,
        bool active = true
    );

    void setEmitterActive(
        EmisorParticula* emitter,
        bool active
    );

    void setForceActive(
        ForceGenerator* generator,
        bool active
    );

    void toggleForce(ForceGenerator* generator);

    void update(float dt);

private:
    struct EmitterEntry
    {
        EmisorParticula* emitter;
        bool active;
    };

    struct ForceEntry
    {
        ForceGenerator* generator;
        bool active;
    };

    std::vector<Particle*> m_particles;
    std::vector<EmitterEntry> m_emitters;
    std::vector<ForceEntry> m_forces;
};