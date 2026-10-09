#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"

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

    std::vector<Particle*> proyectiles;

    // Datos del proyectil real
    float masaReal = 0.01f;
    float velocidadReal = 400.0f;

    // Velocidad reducida para la simulación
    float velocidadSimulada = 40.0f;

    // Valores calculados automáticamente
    float masaSimulada = 1.0f;
    float gravedadSimulada = 9.81f;


    void recalcularParametros();

    void disparaProyectil(
        float speed,
        Vector3D acceleration
    );
};