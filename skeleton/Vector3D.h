#pragma once

#include "PxPhysicsAPI.h"
using namespace physx;

class Vector3D
{
public:

	float x, y, z;
	
	//constructor por defecto 
	Vector3D(int x = 0,int y = 0, int z = 0) : x(x), y(y), z(z) {}

	//constructor a traves de un PxVec3 de physx
	Vector3D(physx::PxVec3 vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}

	//conversion explicita desde clase Vector3D a clase physx::PxVec3
	physx::PxVec3 toPxVec3() const { return physx::PxVec3(x, y, z); }

	// devuelve la magnitud del vector
	float magnitude() const;

	//normaliza el vector y devuelve un nuevo vector normalizado
	Vector3D normalize() const;

	//productor escalar
	float dot(const Vector3D& v) const;
	
	//producto vectorial
	Vector3D cross(const Vector3D& v) const;

	// producto vectorial
	static Vector3D cross(const Vector3D& v1, const Vector3D& v2);

	//suma de vectores
	Vector3D operator+(const Vector3D& v) const;

	//resta de vectores
	Vector3D operator-(const Vector3D& v) const;

	//multiplicacion por escalar
	Vector3D operator*(float escalar) const;

	//asignar a un vector
	Vector3D& operator=(const Vector3D& v);

	//suma de vectores y asignacion
	Vector3D& operator+=(const Vector3D& v);

};

