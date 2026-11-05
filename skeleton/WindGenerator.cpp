#include "WindGenerator.h"
#include "Particle.h"


WindGenerator::WindGenerator(
    Vector3D windVelocity,
    float k1,
    float k2
)
    : m_windVelocity(windVelocity),
    m_k1(k1),
    m_k2(k2)
{
}


// En el viento uniforme la velocidad del aire
// es la misma para todas las partículas.
Vector3D WindGenerator::getWindVelocity(
    Particle* particle
) const
{
    return m_windVelocity;
}


// Calcula la fuerza producida por el viento.
void WindGenerator::updateForce(
    Particle* particle,
    float dt
)
{
    // Diferencia entre la velocidad del viento
    // y la velocidad de la partícula.
    Vector3D relativeVelocity =
        getWindVelocity(particle)
        - particle->getVelocity();


    // Parte lineal:
    // F = k1 * (Vviento - Vparticula)
    Vector3D force =
        relativeVelocity * m_k1;


    // Parte cuadrática opcional.
    if (m_k2 != 0.0f)
    {
        force +=
            relativeVelocity *
            (m_k2 * relativeVelocity.magnitude());
    }


    // Añadimos la fuerza al acumulador de la partícula.
    particle->addForce(force);
}