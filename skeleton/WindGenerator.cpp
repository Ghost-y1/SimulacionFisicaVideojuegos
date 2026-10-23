#include "WindGenerator.h"
#include "Particle.h"
void WindGenerator::updateForce(Particle* particle, float dt) {

	Vector3D relativeForce = this->getWindVelocity() - particle->getVelocity();

	Vector3D force = relativeForce * k1;

	// parte opcional: si K2 no es 0
	if (k1 != 0) {
		force += relativeForce * (k2 * relativeForce.magnitude());
	}
	
	// añadimos la fuerza al acumulador
	particle->addForce(force);
}