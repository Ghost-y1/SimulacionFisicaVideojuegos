#include "P0S_Scene.h"
#include <iostream>
void P0S_Scene::init() {


	//esfera en el origen
	physx::PxShape* originShape =
		CreateShape(physx::PxSphereGeometry(1.0f));

	m_transform = physx::PxTransform(
		physx::PxVec3(0.0f, 0.0f, 0.0f)
	);

	m_renderItem = new RenderItem(
		originShape,
		&m_transform,
		Vector4(1.0f, 1.0f, 1.0f, 1.0f)
	);

	/*
	
	//RETO A eje de coordenadas

	// Creaci¨®n de una esfera 
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	// Creaci¨®n de una esfera 2
	physx::PxShape* shape2 = CreateShape(physx::PxSphereGeometry(2.0f));
	// Creaci¨®n de una esfera 3
	physx::PxShape* shape3 = CreateShape(physx::PxSphereGeometry(2.0f));

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
	
	m_transformX = physx::PxTransform(vecX.toPxVec3());
	m_transformY = physx::PxTransform(vecY.toPxVec3());
	m_transformZ = physx::PxTransform(vecW.toPxVec3());

	//debug para comprobar los valores de los vectores
	std::cout << "Vector X: (" << vecX.x << ", " << vecX.y << ", " << vecX.z << ")\n";
	std::cout << "Vector Y: (" << vecY.x << ", " << vecY.y << ", " << vecY.z << ")\n";
	std::cout << "Vector W: (" << vecW.x << ", " << vecW.y << ", " << vecW.z << ")\n";

	//renderizar ejes de coordenadas
	m_renderItem1 = new RenderItem(shape, &m_transformX, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	m_renderItem2 = new RenderItem(shape2, &m_transformY, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	m_renderItem3 = new RenderItem(shape3, &m_transformZ,  Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	*/

	// RETO B 

	//posicion y direccion del enemigo 
	Vector3D enemyPos(0.0f, 0.0f, 0.0f);
	Vector3D direction(0.0f, 0.0f, 1.0f);

	// posicion de esferas objetivas
	Vector3D p1(2.0f, 0.0f, 3.0f);
	Vector3D p2(-4.0f, 0.0f, 1.0f);
	Vector3D p3(0.0f, 0.0f, -5.0f);
	Vector3D p4(3.0f, 0.0f, 0.0f);

	// vector de direccion entre objetivos y enemigo
	Vector3D dirP1 = p1 - enemyPos;
	Vector3D dirP2 = p2 - enemyPos;
	Vector3D dirP3 = p3 - enemyPos;
	Vector3D dirP4 = p4 - enemyPos;

	// angulo entre vision enemigo y esfera objetivas
	float dotP1 = direction.dot(dirP1);
	float dotP2 = direction.dot(dirP2);
	float dotP3 = direction.dot(dirP3);
	float dotP4 = direction.dot(dirP4);

	//debug para ver el producto escalar
	std::cout << "Dot P1: " << dotP1 << std::endl;
	std::cout << "Dot P2: " << dotP2 << std::endl;
	std::cout << "Dot P3: " << dotP3 << std::endl;
	std::cout << "Dot P4: " << dotP4 << std::endl;
	
	// creamos los shape y el transform
	physx::PxShape* shapeP1 = CreateShape(physx::PxSphereGeometry(0.5f));
	physx::PxShape* shapeP2 = CreateShape(physx::PxSphereGeometry(0.5f));
	physx::PxShape* shapeP3 = CreateShape(physx::PxSphereGeometry(0.5f));
	physx::PxShape* shapeP4 = CreateShape(physx::PxSphereGeometry(0.5f));


	m_transformP1 = physx::PxTransform(p1.toPxVec3());
	m_transformP2 = physx::PxTransform(p2.toPxVec3());
	m_transformP3 = physx::PxTransform(p3.toPxVec3());
	m_transformP4 = physx::PxTransform(p4.toPxVec3());

	Vector4 colorP1;
	Vector4 colorP2;
	Vector4 colorP3;
	Vector4 colorP4;

	// P1
	if (dotP1 > 0) 
		colorP1 = Vector4(0.0f, 1.0f, 0.0f, 1.0f); // Verde
	else if (dotP1 < 0)
		colorP1 = Vector4(1.0f, 0.0f, 0.0f, 1.0f); // Rojo
	else
		colorP1 = Vector4(1.0f, 1.0f, 0.0f, 1.0f); // Amarillo

	// P2
	if (dotP2 > 0)
		colorP2 = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	else if (dotP2 < 0)
		colorP2 = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		colorP2 = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

	// P3
	if (dotP3 > 0)
		colorP3 = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	else if (dotP3 < 0)
		colorP3 = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		colorP3 = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

	// P4
	if (dotP4 > 0)
		colorP4 = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	else if (dotP4 < 0)
		colorP4 = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		colorP4 = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

	// renderizamos los puntos objetivos
	m_renderP1 = new RenderItem(shapeP1,&m_transformP1,colorP1);
	m_renderP2 = new RenderItem(shapeP2,&m_transformP2,colorP2);
	m_renderP3 = new RenderItem(shapeP3,&m_transformP3,colorP3);
	m_renderP4 = new RenderItem(shapeP4,&m_transformP4,colorP4);
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
	
	/*
	if (m_renderItem2)
	{
		m_renderItem2->release();
		m_renderItem2 = nullptr;
	}

	if (m_renderItem3)
	{
		m_renderItem3->release();
		m_renderItem3 = nullptr;
	}
	*/

	if (m_renderP1)
	{
		m_renderP1->release();
		m_renderP1 = nullptr;
	}

	if (m_renderP2)
	{
		m_renderP2->release();
		m_renderP2 = nullptr;
	}

	if (m_renderP3)
	{
		m_renderP3->release();
		m_renderP3 = nullptr;
	}

	if (m_renderP4)
	{
		m_renderP4->release();
		m_renderP4 = nullptr;
	}
}
