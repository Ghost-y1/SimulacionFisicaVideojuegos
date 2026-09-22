#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"

class Vector3D;

class P0S_Scene : public Scene {
public:
    explicit P0S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;

private:

    physx::PxTransform m_transform;
    physx::PxTransform m_transformX;
    physx::PxTransform m_transformY;
    physx::PxTransform m_transformZ;

    RenderItem* m_renderItem{ nullptr };
    RenderItem* m_renderItem1{ nullptr };
    RenderItem* m_renderItem2{ nullptr };
    RenderItem* m_renderItem3{ nullptr }; 
};