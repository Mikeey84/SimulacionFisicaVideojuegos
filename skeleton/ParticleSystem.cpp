#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {

}

void ParticleSystem::update(double t) {
	//std::cout << t<< std::endl;
	for (Generator* g : _generators) {
		g->update(t);

	}
	for (Particle* p : _particles) {
		p->integrate(t);
		checkDis(p);
		checkDeath(p);

	}

	for (Particle* p : _particlesToErase) {
		_particles.erase(std::remove(_particles.begin(), _particles.end(), p), _particles.end());
		delete p;  
	}
	_particlesToErase.clear();
}

void ParticleSystem::addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color) {
	_particles.push_back(new Particle(pos, vel, acc, maxDis, maxTime, color));
}



void ParticleSystem::addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, float x2, float y2, float x3, float y3) {
	_generators.push_back(new Generator(this, type, pos, time, maxDis, maxTime, x1, y1, x2, y2, x3, y3));
}

void ParticleSystem::checkDis(Particle* p) {
	if (abs(p->_pos.x) > p->_maxDis || abs(p->_pos.y) > p->_maxDis || abs(p->_pos.z) > p->_maxDis) {
		_particlesToErase.push_back(p);
	}
}

void ParticleSystem::checkDeath(Particle* p) {
	if (p->checkDeath()) _particlesToErase.push_back(p);
}



