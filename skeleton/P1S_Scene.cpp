#include "P1S_Scene.h"
#include <iostream>
void P1S_Scene::init() {

	p1 = new Particle(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1.0f, 2.0f, 0.0f), Vector3D(0.0f, -9.81f, -10.0f), 1.0f, 0.99f);

}

void P1S_Scene::update(double dt) {
	p1->integrate(dt);
}

void P1S_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	
}

void P1S_Scene::cleanup() {

}
