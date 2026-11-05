#include "VortexGenerator.h"
#include "Particle.h"


VortexGenerator::VortexGenerator(
    Vector3D center,
    float strength,
    float radius,
    float k1
)
    : WindGenerator(
        Vector3D(0.0f, 0.0f, 0.0f),
        k1,
        0.0f
    ),
    m_center(center),
    m_strength(strength),
    m_radius(radius)
{
}


// Calcula un viento tangencial alrededor del eje Y
Vector3D VortexGenerator::getWindVelocity(
    Particle* particle
) const
{
    Vector3D relative =
        particle->getPosition() - m_center;

    float distance =
        relative.magnitude();


    // Fuera del radio no hay torbellino
    if (distance > m_radius)
    {
        return Vector3D(
            0.0f,
            0.0f,
            0.0f
        );
    }


    // Dirección tangencial alrededor del eje Y
    Vector3D tangential(
        -relative.z,
        0.0f,
        relative.x
    );


    return tangential * m_strength;
}