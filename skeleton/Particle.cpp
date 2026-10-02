#include "Particle.h"
#include <cmath>
Particle::Particle(Vector3D position, Vector3D velocity, Vector3D acceleration,float mass,float dumping)
	: m_position(position), m_velocity(velocity), m_acceleration(acceleration),m_mass (mass),m_dumping(dumping) {
	m_pose = physx::PxTransform(m_position.toPxVec3());

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &m_pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

void Particle::integrate(float dt) {

	//m_acceleration = m_force * (1.0f / m_mass);

	m_velocity += m_acceleration * dt;
	
	m_velocity = m_velocity * pow(m_dumping,dt);
	
	m_position += m_velocity * dt;

	m_pose = physx::PxTransform(m_position.toPxVec3());
}