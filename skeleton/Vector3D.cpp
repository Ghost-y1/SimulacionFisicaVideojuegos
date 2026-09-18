#include "Vector3D.h"
#include <cmath>

float Vector3D::magnitude() const {
	return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize() const {
	float mag = magnitude();

	// evitar division por cero
	if (mag == 0) return Vector3D(0, 0, 0);
	return Vector3D(x / mag, y / mag, z / mag);
}

float Vector3D::dot(const Vector3D& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
	return Vector3D(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

Vector3D Vector3D::cross(const Vector3D& v1, const Vector3D& v2) {
	return Vector3D(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator*(float escalar) const {
	return Vector3D(x * escalar, y * escalar, z * escalar);
}

Vector3D& Vector3D::operator=(const Vector3D& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

