#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {

}

void ParticleSystem::update(double t) {
	//std::cout << t<< std::endl;
	for (ForceGenerator* f : _forceGenerators) {
		f->update(t);
	}
	for (Generator* g : _generators) {
		g->update(t);
	}
	for (Particle* p : _particles) {
		p->integrate(t);
		checkDeath(p);
	}
	

	for (Particle* p : _particlesToErase) {
		auto it = find(_particles.begin(), _particles.end(), p);
		_particles.erase(it);
		delete p;  
	}
	_particlesToErase.clear();
	
}

void ParticleSystem::addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass) {
	_particles.push_back(new Particle(pos, vel, acc, maxDis, maxTime, mass, color));
}



void ParticleSystem::addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime,
	float x1, float y1, float x2, float y2, float x3, float y3, float mass) {
	_generators.push_back(new Generator(this, type, pos, time, maxTime, maxDis, x1, y1, x2, y2, x3, y3, mass));
}

void ParticleSystem::addForceGenerator(ForceType fT, Vector3 pos, Vector3 area, Vector3 gravity_speed, float k1, float k2, bool easy) {
	switch (fT)
	{
	case ParticleSystem::GRAVITY:
		_forceGenerators.push_back(new GravityGenerator(this, pos, area, gravity_speed));
		break;
	case ParticleSystem::WIND:
		_forceGenerators.push_back(new WindGenerator(this, pos, area, gravity_speed, k1, k2, easy));
		break;
	case ParticleSystem::WHIRLWIND:
		_forceGenerators.push_back(new WhirlwindGenerator(this, pos, area, k1));
		break;
	default:
		break;
	}
}

void ParticleSystem::checkDeath(Particle* p) {
	if (p->checkDeath()) _particlesToErase.push_back(p);
	else if(p->checkDis()) _particlesToErase.push_back(p);
}





