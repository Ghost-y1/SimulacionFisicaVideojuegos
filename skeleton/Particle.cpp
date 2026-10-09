#include "Particle.h"
#include <cmath>
Particle::Particle(Vector3D position, Vector3D velocity, Vector3D acceleration,float size,float mass, Vector4 color, float dumping)
	: m_position(position), m_velocity(velocity), m_acceleration(acceleration),m_size(size),m_mass (mass),m_color(color),m_dumping(dumping) {
	m_pose = physx::PxTransform(m_position.toPxVec3());

	m_renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(m_size)), &m_pose, m_color);
}

Particle::~Particle()
{
	if (m_renderItem)
	{
		m_renderItem->release();
		m_renderItem = nullptr;
	}
}

void Particle::integrate(float dt) {

	//m_acceleration = m_force * (1.0f / m_mass);

	m_velocity += m_acceleration * dt;
	
	m_velocity = m_velocity * pow(m_dumping,dt);
	
	m_position += m_velocity * dt;

	m_pose = physx::PxTransform(m_position.toPxVec3());
}