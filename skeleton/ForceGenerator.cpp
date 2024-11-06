#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(Vector3 pos, Vector3 area) : _pos(pos) {
	// Inicializar las areas para que se evaluen las posiciones de las particulas
	areaX = area.x;
	areaY = area.y;
	areaZ = area.z;
}

bool ForceGenerator::checkArea(Vector3 pos) {
	
	float x, y, z; // Variables auxiliares 
	x = areaX / 2;
	y = areaY / 2;
	z = areaZ / 2;
	return (pos.x >= -x && pos.x <= x) &&
		(pos.y >= -y && pos.y <= y) &&
		(pos.z >= -z && pos.z <= z);
}
