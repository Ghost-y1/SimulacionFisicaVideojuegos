#include "P1S_Scene.h"
#include <iostream>
void P1S_Scene::init() {

	p1 = new Particle(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(1.0f, 2.0f, 0.0f), Vector3D(0.0f, -9.81f, -10.0f), 1.0f, 0.99f);

}

void P1S_Scene::update(double dt) {
	p1->integrate(dt);

	for (auto p: proyectiles) {
		p->integrate(dt);
	}
}

void P1S_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'j' || key == 'J') {
		disparaProyectil(10, Vector3D(0.0f, -9.81f, -10.0f));
	}
}

void P1S_Scene::cleanup() {
	if (p1) {
		delete p1;
		p1 = nullptr;
	}
	for (auto p: proyectiles) {
		delete p;
	}
}

void P1S_Scene::disparaProyectil(float speed, Vector3D acceleration) {
	Particle* p = new Particle(GetCamera()->getEye(), GetCamera()->getDir()*speed, Vector3D(0, -9.81f, 0), 1.0f, 0.99f);
	proyectiles.push_back(p);
}
