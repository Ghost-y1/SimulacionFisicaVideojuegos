#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(
    ForceGenerator* generator,
    bool active
)
{
    m_generators.push_back({ generator, active });
}

void ParticleForceRegistry::remove(
    ForceGenerator* generator
)
{
    for (auto it = m_generators.begin();
        it != m_generators.end(); )
    {
        if (it->generator == generator)
            it = m_generators.erase(it);
        else
            ++it;
    }
}

void ParticleForceRegistry::setActive(
    ForceGenerator* generator,
    bool active
)
{
    for (Registration& entry : m_generators)
    {
        if (entry.generator == generator)
            entry.active = active;
    }
}

void ParticleForceRegistry::toggle(
    ForceGenerator* generator
)
{
    for (Registration& entry : m_generators)
    {
        if (entry.generator == generator)
            entry.active = !entry.active;
    }
}

std::vector<ForceGenerator*>
ParticleForceRegistry::getActiveGenerators() const
{
    std::vector<ForceGenerator*> activeGenerators;

    for (const Registration& entry : m_generators)
    {
        if (entry.active)
            activeGenerators.push_back(entry.generator);
    }

    return activeGenerators;
}

void ParticleForceRegistry::update(float dt)
{
    for (Registration& entry : m_generators)
    {
        if (entry.active)
            entry.generator->update(dt);
    }
}

void ParticleForceRegistry::clear()
{
    m_generators.clear();
}