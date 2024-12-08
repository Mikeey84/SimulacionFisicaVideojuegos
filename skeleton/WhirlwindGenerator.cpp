#include "WhirlwindGenerator.h"
#include "ParticleSystem.h"

WhirlwindGenerator::WhirlwindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k) : ForceGenerator(pS, pos, area), _pS(pS), _k(k) {
	_type = ForceGenerator::WHIRL;
}

void WhirlwindGenerator::update(double t, Particle* p) {
	
	// Creacion de la fuerza tangencial cambiando al x y z 
	_force = getForce(p->_pos);

	p->addForce(_force);
	
}

Vector3 WhirlwindGenerator::getForce(Vector3 pPos)
{
	return { -_k * (pPos.z - _pos.z),
				_k * (50 - pPos.y - _pos.y),
				_k * (pPos.x - _pos.x) };
}
