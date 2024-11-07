#include "WhirlwindGenerator.h"
#include "ParticleSystem.h"

WhirlwindGenerator::WhirlwindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k) : ForceGenerator(pS, pos, area), _pS(pS), _k(k) {
}

void WhirlwindGenerator::update(double t) {
	for (int i = 0; i < _pS->_particles.size(); ++i) {
		const Vector3 pPos = _pS->_particles[i]->_pos;
		if (checkArea(pPos)) {
			// Creacion de la fuerza tangencial cambiando al x y z 
			_force = {	-_k * (pPos.z - _pos.z),
						_k * (50 - pPos.y - _pos.y),
						_k * (pPos.x - _pos.x)};

			_pS->_particles[i]->addForce(_force);
		}
	}
}
