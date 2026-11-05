#pragma once

#include "Scene.h"
#include "ParticleSystem.h"
#include "GravityGenerator.h"

class P2S_Scene : public Scene
{
public:
    explicit P2S_Scene(std::string name)
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
    ParticleSystem* m_system = nullptr;

    GravityGenerator* m_gravity = nullptr;

    EmisorParticula* m_uniformEmitter = nullptr;
    EmisorParticula* m_gaussianEmitter = nullptr;
    EmisorParticula* m_fogEmitter = nullptr;
};