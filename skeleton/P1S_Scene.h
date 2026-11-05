#pragma once

#include "Scene.h"
#include "Projectile.h"

#include <vector>

class P1S_Scene : public Scene
{
public:
    explicit P1S_Scene(std::string name)
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
    void shoot(const ProjectileData& data);

    std::vector<Projectile*> m_projectiles;

    ProjectileData m_bullet;
    ProjectileData m_ball;
};