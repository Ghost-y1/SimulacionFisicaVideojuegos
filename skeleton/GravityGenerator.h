#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

// Generador encargado de aplicar la fuerza de gravedad sobre una partícula.
class GravityGenerator : public ForceGenerator
{
public:

    // Recibe el vector de gravedad que queremos utilizar.
    GravityGenerator(Vector3D gravity)
        : m_gravity(gravity)
    {
    }

    // Calcula la fuerza peso de la partícula y la añade a su acumulador de fuerzas.
    void updateForce(Particle* particle,float dt) override;

private:

    // Aceleración producida por la gravedad.
    Vector3D m_gravity;
};