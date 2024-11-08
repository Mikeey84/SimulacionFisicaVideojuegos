#include "ForceGenerator.h"
#include "ParticleSystem.h"

ForceGenerator::ForceGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area) : _pos(pos), _pS(pS), _area(area) {
}

bool ForceGenerator::checkArea(Vector3 pos) {
	
	float x, y, z; // Variables auxiliares 
	x = _area.x / 2;
	y = _area.y / 2;
	z = _area.z / 2;
	return (pos.x >= -x && pos.x <= x) &&
		(pos.y >= -y && pos.y <= y) &&
		(pos.z >= -z && pos.z <= z);
}

bool ForceGenerator::checkCircleArea(Vector3 pos)
{
	// Si la distancia entre la particula y el origen es menor que el radio (area.x) devuelve que esta en rango
	return (pos - _pos).magnitude() < _area.x;
}
