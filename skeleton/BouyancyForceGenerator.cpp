#include "BouyancyForceGenerator.h"
#include "ParticleSystem.h"


BouyancyForceGenerator::BouyancyForceGenerator(ParticleSystem* pS, float h, float V, float d) :
	ForceGenerator(pS,{0,0,0},{0,0,0}), _height(h), _volume(V), _liquidDensity(d) {
	//_liquidParticle = new Particle({-10,_height,0},{0,0,0 }, {0,0,0}, 200, 10000, 1e6, Particle::PLANE);
	_type = ForceGenerator::BOUYANCY;
}

void BouyancyForceGenerator::update(double t, Particle* p) {
	
	_force = getF(p->_pos, p->_initPos);
	p->addForce(_force);
}

Vector3 BouyancyForceGenerator::getF(Vector3 pos, Vector3 initPos) {
	float h = pos.y;
	float h0 = initPos.y;

	Vector3 f(0, 0, 0);
	float inmersed = 0.0;

	if (h - h0 > _height * 0.5) {
		inmersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		inmersed = 1.0;
	}
	else {
		inmersed = (h0 - h) / _height + 0.5;
	}
	f.y = _liquidDensity * _volume * inmersed;

	return f;
}
