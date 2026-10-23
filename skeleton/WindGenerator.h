#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"
class WindGenerator :
    public ForceGenerator
{
public:

    WindGenerator(Vector3D windSpeed, float k1,float k2=0.0f) :
        m_windSpeed(windSpeed),
        k1(k1),
        k2(k2)
    {
    }

    // Calcula la fuerza peso de la partícula y la añade a su acumulador de fuerzas.
    void updateForce(Particle* particle, float dt) override;

    Vector3D getWindVelocity() const {
        return m_windSpeed;
    }
private:
    float k1;
    float k2;
    Vector3D m_windSpeed;
};

