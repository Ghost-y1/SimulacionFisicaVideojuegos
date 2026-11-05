#include "P1S_Scene.h"

void P1S_Scene::init()
{
    // Proyectil 1
    m_bullet = {
        0.01f,
        400.0f,
        40.0f,
        9.81f,
        0.15f,
        0.99f,
        Vector4(1.0f, 1.0f, 0.0f, 1.0f)
    };

    // Proyectil 2
    m_ball = {
        0.06f,
        50.0f,
        15.0f,
        9.81f,
        0.35f,
        0.98f,
        Vector4(1.0f, 0.0f, 0.0f, 1.0f)
    };
}

void P1S_Scene::update(double dt)
{
    for (Projectile* p : m_projectiles)
        p->integrate((float)dt);
}

void P1S_Scene::keyPress(
    unsigned char key,
    const physx::PxTransform& camera
)
{
    if (key == 'j' || key == 'J')
        shoot(m_bullet);

    if (key == 'k' || key == 'K')
        shoot(m_ball);
}

void P1S_Scene::shoot(const ProjectileData& data)
{
    Projectile* projectile = new Projectile(
        GetCamera()->getEye(),
        GetCamera()->getDir(),
        data
    );

    m_projectiles.push_back(projectile);
}

void P1S_Scene::cleanup()
{
    for (Projectile* p : m_projectiles)
        delete p;

    m_projectiles.clear();
}