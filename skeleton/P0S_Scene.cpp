#include "P0S_Scene.h"
#include <iostream>
void P0S_Scene::init() {

	// Creaci車n de una esfera 
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	// Creaci車n de una esfera 2
	physx::PxShape* shape2 = CreateShape(physx::PxSphereGeometry(2.0f));
	// Creaci車n de una esfera 3
	physx::PxShape* shape3 = CreateShape(physx::PxSphereGeometry(2.0f));

	// Inicializaci車n de la posici車n de la esfera en el origen de coordenadas 
	m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

	// Se registra el RenderItem 
	//m_renderItem = new RenderItem(shape, &m_transform, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	// Creamos dos vectores del reto A de la practica 0 
	Vector3D vecX(3.0f, 1.0f, 0.0f);
	Vector3D vecY(0.0f, 4.0f, 0.0f);

	// Calculamos el productor vectorial de los dos vectores
	Vector3D vecW = Vector3D::cross(vecX,vecY);

	// normalizamos los vectores
	vecX = vecX.normalize();
	vecY = vecY.normalize();
	vecW = vecW.normalize();

	//escalamos los vectores por 5.0f
	vecX = vecX * 5.0f;
	vecY = vecY * 5.0f;
	vecW = vecW * 5.0f;
	
	//debug para comprobar los valores de los vectores
	std::cout << "Vector X: (" << vecX.x << ", " << vecX.y << ", " << vecX.z << ")\n";
	std::cout << "Vector Y: (" << vecY.x << ", " << vecY.y << ", " << vecY.z << ")\n";
	std::cout << "Vector W: (" << vecW.x << ", " << vecW.y << ", " << vecW.z << ")\n";

	m_renderItem = new RenderItem(shape, &physx::PxTransform(vecX.toPxVec3()), Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	m_renderItem2 = new RenderItem(shape2, &physx::PxTransform(vecY.toPxVec3()), Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	m_renderItem3 = new RenderItem(shape3, &physx::PxTransform(vecW.toPxVec3()),  Vector4(0.0f, 1.0f, 0.0f, 1.0f));
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
