#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"
#include <array>
#include <vector>

class Vector3D;
class Particle;

class P1S_Scene : public Scene {
public:
    explicit P1S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

	void disparaProyectil(float speed, Vector3D acceleration);

private:
    Particle* p1; 
	std::vector<Particle*> proyectiles;

   // physx::PxTransform m_transform;
   // RenderItem* m_renderItem{ nullptr };

};