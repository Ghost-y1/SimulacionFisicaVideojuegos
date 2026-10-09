#include "EmisorParticula.h"

EmisorParticula::EmisorParticula(Vector3D pos, Vector3D dir, Vector3D vel, Vector4 color, float angulo, float radio, float size, float mass, float life) :
	position(pos), direction(dir), p_velocity(vel), p_color(color), p_size(size), anguloDisparo(angulo), radioMaximo(radio), p_mass(mass), p_life(life)
{ 
}

void EmisorParticula::update() {

}
