#include "GravityGenerator.h"
#include "ParticleSystem.h"

GravityGenerator::GravityGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, Vector3 gravity) : ForceGenerator(pS, pos, area), _pS(pS) {
	_force = gravity;
}

void GravityGenerator::update(double t, Particle* p) {
	
	p->addForce(_force);
	
}
