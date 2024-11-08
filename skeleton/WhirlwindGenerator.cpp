#include "WhirlwindGenerator.h"
#include "ParticleSystem.h"

WhirlwindGenerator::WhirlwindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k) : ForceGenerator(pS, pos, area), _pS(pS), _k(k) {
}

void WhirlwindGenerator::update(double t, Particle* p) {

	const Vector3 pPos = p->_pos;
	
	// Creacion de la fuerza tangencial cambiando al x y z 
	_force = {	-_k * (pPos.z - _pos.z),
				_k * (50 - pPos.y - _pos.y),
				_k * (pPos.x - _pos.x)};

	p->addForce(_force);
	
}
