#pragma once

#include "Scene.h"
#include "ParticleSystem.h"

#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "VortexGenerator.h"
#include "ExplosionGenerator.h"

class P3S_Scene : public Scene
{
public:
    explicit P3S_Scene(std::string name)
        : Scene(std::move(name))
    {
    }

    void init() override;
    void update(double dt) override;

    void keyPress(
        unsigned char key,
        const physx::PxTransform& camera
    ) override;

    void cleanup() override;

private:
    ParticleSystem* m_gravitySystem = nullptr;
    ParticleSystem* m_reducedGravitySystem = nullptr;
    ParticleSystem* m_accelerationSystem = nullptr;

    ParticleSystem* m_windSystem = nullptr;
    ParticleSystem* m_vortexSystem = nullptr;
    ParticleSystem* m_explosionSystem = nullptr;

    GravityGenerator* m_gravity = nullptr;
    GravityGenerator* m_reducedGravity = nullptr;

    WindGenerator* m_wind = nullptr;
    VortexGenerator* m_vortex = nullptr;
    ExplosionGenerator* m_explosion = nullptr;
};