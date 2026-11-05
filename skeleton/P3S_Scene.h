#pragma once

#include "Scene.h"
#include "Particle.h"
#include "EmisorParticula.h"

#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "VortexGenerator.h"
#include "ExplosionGenerator.h"
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

    // ACTIVIDAD 1 - GRAVEDAD

    GravityGenerator* m_gravedadNormal = nullptr;
    GravityGenerator* m_gravedadReducida = nullptr;

    EmisorParticula* m_emisorGravedadNormal = nullptr;
    EmisorParticula* m_emisorGravedadReducida = nullptr;
    EmisorParticula* m_emisorAceleracion = nullptr;


    // ACTIVIDAD 2 - VIENTO

    WindGenerator* m_viento = nullptr;
    EmisorParticula* m_emisorViento = nullptr;


    // ACTIVIDAD 3 - TORBELLINO

    VortexGenerator* m_torbellino = nullptr;
    EmisorParticula* m_emisorTorbellino = nullptr;


    // ACTIVIDAD 4 - EXPLOSION

    ExplosionGenerator* m_explosion = nullptr;

    ParticleForceRegistry m_explosionRegistry;

    std::vector<Particle*> m_particulasExplosion;

    bool m_explosionActiva = false;
};