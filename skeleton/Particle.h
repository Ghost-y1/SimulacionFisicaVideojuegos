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
		float size = 0.5f,
		Vector4 color = Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		float damping = 1.0f
	);
	~Particle();

	void integrate(float dt);

private:
	Vector3D m_force;
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	Vector4 m_color;
	float m_size;
	float m_dumping;
	float m_mass;
	physx::PxTransform m_pose;
	RenderItem* m_renderItem = nullptr;
};

