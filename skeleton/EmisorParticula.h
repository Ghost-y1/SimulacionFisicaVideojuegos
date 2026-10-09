#pragma once
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>
#include "Particle.h"

class EmisorParticula
{
public:
	EmisorParticula(
		Vector3D pos, 
		Vector3D dir,
		Vector3D vel,
		Vector4 color,
		float angulo, 
		float radio, 
		float size, 
		float mass, 
		float life
	);

	void update();

private:

	std::vector<Particle*> particulas;

	Vector3D position;
	Vector3D direction;
	Vector3D p_velocity;
	Vector4 p_color;

	float anguloDisparo;
	float radioMaximo;
	float p_size;
	float p_mass;
	float p_life;
	float gravedad = -10.0f;

};

