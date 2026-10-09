#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "EmisorParticula.h"
#include <vector>

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


};
