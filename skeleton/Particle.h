#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class ForceGenerator;

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
        float life = 5.0f,
        bool render = true
    );

    virtual ~Particle();

    void integrate(float dt);

    // Gestión de fuerzas
    void addForce(const Vector3D& force);
    void clearForces();
    void applyForceGenerator(ForceGenerator* generator, float dt);

    // Crea una copia a partir de la partícula modelo
    Particle* clone(Vector3D position, Vector3D velocity) const;

    bool isAlive() const;

    Vector3D getPosition() const;
    Vector3D getVelocity() const;

    float getMass() const;
    float getSize() const;

private:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;
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