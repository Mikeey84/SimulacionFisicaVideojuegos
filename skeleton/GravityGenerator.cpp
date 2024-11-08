#include "GravityGenerator.h"
#include "ParticleSystem.h"

GravityGenerator::GravityGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, Vector3 gravity) : ForceGenerator(pS, pos, area), _pS(pS) {
	_force = gravity;
}

void GravityGenerator::update(double t) {
	for (int i = 0; i < _pS->_particles.size(); ++i) {
		if (checkArea(_pS->_particles[i]->_pos)) _pS->_particles[i]->addForce(_force);
	}
}
