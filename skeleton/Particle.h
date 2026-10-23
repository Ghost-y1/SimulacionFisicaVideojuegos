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

    // Fuerzas
    void addForce(const Vector3D& force);
    void clearForces();

    // Getters necesarios para los generadores
    Vector3D getPosition() const;
    Vector3D getVelocity() const;

    float getMass() const;

    bool isAlive() const;

private:

    Vector3D m_position;
    Vector3D m_velocity;

    // Aceleración constante independiente de fuerzas
    Vector3D m_acceleration;

    // Fuerzas acumuladas durante el frame
    Vector3D m_forceAccum;

    Vector4 m_color;

    float m_size;
    float m_mass;
    float m_damping;

    float m_age;
    float m_life;

    physx::PxTransform m_pose;
    RenderItem* m_renderItem = nullptr;
};