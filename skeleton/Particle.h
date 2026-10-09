#include "Vector3D.h"
#include "RenderUtils.hpp"

#pragma once
class Particle
{
public: 
	Particle(
		Vector3D position,
		Vector3D velocity,
		Vector3D acceleration,
		float mass = 1.0f,
		float damping = 1.0f
	);
	~Particle();

	void integrate(float dt);

private:
	Vector3D m_force;
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	float m_dumping;
	float m_mass;
	physx::PxTransform m_pose;
	RenderItem* m_renderItem = nullptr;
};

