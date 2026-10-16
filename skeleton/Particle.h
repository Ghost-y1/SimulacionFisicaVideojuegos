#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle
{
public:

    Particle(
        Vector3D position,
        Vector3D velocity,
        Vector3D acceleration,
        float size = 0.5f,
        float mass = 1.0f,
        Vector4 color = Vector4(1.0f, 0.0f, 0.0f, 1.0f),
        float damping = 1.0f,
        float life = 5.0f
    );

    ~Particle();

    void integrate(float dt);

    bool isAlive() const;

    Vector3D getPosition() const;

private:

    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;

    Vector4 m_color;

    float m_size;
    float m_mass;
    float m_damping;

    // Ciclo de vida
    float m_age;
    float m_life;

    physx::PxTransform m_pose;

    RenderItem* m_renderItem = nullptr;
};