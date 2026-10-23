#pragma once

#include "Scene.h"

#include "Particle.h"
#include "EmisorParticula.h"

#include "ForceGenerator.h"
#include "GravityGenerator.h"
#include "ParticleForceRegistry.h"

#include <vector>


class P3S_Scene : public Scene
{
public:

    explicit P3S_Scene(std::string name)
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
    // ACTIVIDAD 1

    EmisorParticula* m_emisorGravedadNormal = nullptr;

    EmisorParticula* m_emisorGravedadReducida = nullptr;

    EmisorParticula* m_emisorAceleracion = nullptr;


    GravityGenerator* m_gravedadNormal = nullptr;

    GravityGenerator* m_gravedadReducida = nullptr;

};