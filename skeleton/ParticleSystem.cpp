#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
    for (Particle* p : m_particles)
        delete p;

    for (EmitterEntry& entry : m_emitters)
        delete entry.emitter;

    m_particles.clear();
    m_emitters.clear();
    m_forces.clear();
}

void ParticleSystem::addParticle(Particle* particle)
{
    m_particles.push_back(particle);
}

void ParticleSystem::addEmitter(EmisorParticula* emitter)
{
    m_emitters.push_back({ emitter, true });
}

void ParticleSystem::addForceGenerator(
    ForceGenerator* generator,
    bool active
)
{
    m_forces.push_back({ generator, active });
}

void ParticleSystem::setEmitterActive(
    EmisorParticula* emitter,
    bool active
)
{
    for (EmitterEntry& entry : m_emitters)
    {
        if (entry.emitter == emitter)
            entry.active = active;
    }
}

void ParticleSystem::setForceActive(
    ForceGenerator* generator,
    bool active
)
{
    for (ForceEntry& entry : m_forces)
    {
        if (entry.generator == generator)
            entry.active = active;
    }
}

void ParticleSystem::toggleForce(
    ForceGenerator* generator
)
{
    for (ForceEntry& entry : m_forces)
    {
        if (entry.generator == generator)
            entry.active = !entry.active;
    }
}

void ParticleSystem::update(float dt)
{
    // Generación de partículas
    for (EmitterEntry& entry : m_emitters)
    {
        if (!entry.active)
            continue;

        std::vector<Particle*> newParticles =
            entry.emitter->emit();

        for (Particle* p : newParticles)
            m_particles.push_back(p);
    }

    // Actualización de fuerzas dependientes del tiempo
    for (ForceEntry& entry : m_forces)
    {
        if (entry.active)
            entry.generator->update(dt);
    }

    // Fuerzas e integración
    for (Particle* p : m_particles)
    {
        for (ForceEntry& entry : m_forces)
        {
            if (entry.active)
                p->applyForceGenerator(entry.generator, dt);
        }

        p->integrate(dt);
    }

    // Eliminar partículas muertas
    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        if (!(*it)->isAlive())
        {
            delete* it;
            it = m_particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}