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
		checkDeath(p);
	}

	for (Particle* p : _particlesToErase) {
		auto it = find(_particles.begin(), _particles.end(), p);
		_particles.erase(it);
		delete p;  
	}
	_particlesToErase.clear();
	
}

void ParticleSystem::addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG) {
	Particle* p = new Particle(pos, vel, acc, maxDis, maxTime, mass, color);
	_particles.push_back(p);
	p->addForceGenerator(fG);
}



void ParticleSystem::addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime,
	float x1, float y1, float x2, float y2, float x3, float y3, float mass) {
	_generators.push_back(new Generator(this, type, pos, time, maxTime, maxDis, x1, y1, x2, y2, x3, y3, mass));
}

void ParticleSystem::addForceGenerator(ForceType fT, Vector3 pos, Vector3 area, Vector3 gravity_speed, float k1, float k2, bool easy, double t, double tau) {
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
	case ParticleSystem::EXPLOSION:
		_forceGenerators.push_back(new ExplosionGenerator(this, pos, area, k1, t, tau));
		break;
	default:
		break;
	}
}

void ParticleSystem::checkDeath(Particle* p) {
	if (p->checkDeath()) _particlesToErase.push_back(p);
	else if(p->checkDis()) _particlesToErase.push_back(p);
}

void ParticleSystem::generateSpringDemo() {
	Particle* p1 = new Particle({-10,10,0},{0,0,0}, {0,0,0}, 200, 10000, 0.85, {1,1,1,1});
	Particle* p2 = new Particle({ 10,10,0 }, { 0,0,0 }, { 0,0,0 }, 200, 10000, 0.85, { 1,1,1,1 });
	
	p2->_mass = 2;
	SpringForceGenerator* f1 = new SpringForceGenerator(this,1.5, 11, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(this, 1.5, 11, p1);

	_particles.push_back(p1);
	_particles.push_back(p2);

	vector<ForceGenerator*> _f1;
	_f1.push_back(f1);
	vector<ForceGenerator*> _f2;
	_f2.push_back(f2);

	p1->addForceGenerator(_f1);
	p2->addForceGenerator(_f2);

	
	Particle* p3 = new Particle({ -10,20,0 }, { 0,0,0 }, { 0,0,0 }, 200, 10000, 0.85, { 1,1,1,1 });
	AnchoredSpringFG* f3 = new AnchoredSpringFG(this, 1.5, 10, { -10.0,40.0,0.0 });
	_particles.push_back(p3);
	vector<ForceGenerator*> _f3;
	_f3.push_back(f3);
	_f3.push_back(new GravityGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -10, 0)));

	p3->addForceGenerator(_f3);
}

void ParticleSystem::generateBouyancyDemo() {
	Particle* p1 = new Particle({ -10,5,0 }, { 0,0,0 }, { 0,0,0 }, 200, 10000, 0.85, { 1,1,1,1 });
	_particles.push_back(p1);
	BouyancyForceGenerator* f1 = new BouyancyForceGenerator(this, 8, 10, 2);
	vector<ForceGenerator*> _f1;
	_f1.push_back(f1);
	_f1.push_back(new GravityGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -9.8, 0)));
	p1->addForceGenerator(_f1);
}









