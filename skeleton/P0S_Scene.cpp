#include "P0S_Scene.h"

void P0S_Scene::init() {

	// Creaci¨®n de una esfera 
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	// Inicializaci¨®n de la posici¨®n de la esfera en el origen de coordenadas 
	m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

	// Se registra el RenderItem 
	m_renderItem = new RenderItem(shape, &m_transform, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

void P0S_Scene::update(double dt) {

}

void P0S_Scene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'r' || key == 'R') {
		m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
	}
}

void P0S_Scene::cleanup() {

	// si existe un RenderItem registrado, se libera y se pone a nullptr
	if (m_renderItem) {
		m_renderItem->release(); 
		m_renderItem = nullptr;
	}
}
