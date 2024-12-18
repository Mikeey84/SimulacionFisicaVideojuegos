#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(PxPhysics* gPhysics, PxScene* gScene) : _gPhysics(gPhysics), _gScene(gScene) { 
	_forcesModelGravity.push_back(new GravityGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -10, 0)));
	_forcesModelGravityWind.push_back(new GravityGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -10, 0)));
	_forcesModelGravityWind.push_back(new WindGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), 
		Vector3(30, 0, 0), 0.2, 0, true));
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
	for (SolidoRigido* s : _solidosRigidos) {
		s->update();
	}
	for (SolidoRigido* s : _solidosEnemigos) {
		s->update();
	}
	for (Gun* g : _guns) {
		g->update(t);
	}
	for (Particle* p : _particlesToErase) {
		auto it = find(_particles.begin(), _particles.end(), p);
		_particles.erase(it);
		delete p;  
	}
	for (SolidoRigido* p : _solidosToErase) {
		auto it = find(_solidosRigidos.begin(), _solidosRigidos.end(), p);
		_solidosRigidos.erase(it);
		delete p;
	}
	for (SolidoRigido* p : _enemigosToErase) {
		auto it = find(_solidosEnemigos.begin(), _solidosEnemigos.end(), p);
		_solidosEnemigos.erase(it);
		delete p;
	}
	for (int i = 0; i < _numSolidosToAdd; ++i) {
		for (Generator* g : _generators) {
			if (g->_type == Generator::ENEMY) g->addRandomEnemy();
		}
	}
	

	_particlesToErase.clear();
	_solidosToErase.clear();
	_enemigosToErase.clear();
	_numSolidosToAdd = 0;
}

void ParticleSystem::addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG) {
	Particle* p = new Particle(pos, vel, acc, maxDis, maxTime, mass, color);
	_particles.push_back(p);
	p->addForceGenerator(fG);
}

void ParticleSystem::addRBParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG) {
	SolidoRigido* p = new SolidoRigido(this, _gPhysics, _gScene, &PxTransform(pos), vel, acc, maxDis, maxTime, mass, color);
	_solidosRigidos.push_back(p);
	p->addForceGenerator(fG);
}

void ParticleSystem::addRBParticlesC(PxVec3 pos, PxVec3 vel, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG) {
	SolidoRigido* p = new SolidoRigido(this, _gPhysics, _gScene, &PxTransform(pos), vel, maxDis, maxTime, mass, color);
	_solidosRigidos.push_back(p);
	p->addForceGenerator(fG);
}

void ParticleSystem::addRBEnemies(PxVec3 pos, PxVec3 vel, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG) {
	SolidoRigido* p = new SolidoRigido(this, _gPhysics, _gScene, &PxTransform(pos), vel, {0,0,0}, maxDis, maxTime, mass, color);
	_solidosEnemigos.push_back(p);
	p->addForceGenerator(fG);
}



void ParticleSystem::addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime,
	float x1, float y1, float x2, float y2, float x3, float y3, float mass, int maxCount) {
	_generators.push_back(new Generator(this, type, pos, time, maxTime, maxDis, x1, y1, x2, y2, x3, y3, mass, maxCount));
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

void ParticleSystem::addEnemies() {
	for (Generator* g : _generators) {
		if (g->_type == Generator::ENEMY) g->addEnemies();
	}
}

void ParticleSystem::addRandomEnemy() {
	_numSolidosToAdd++;
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
	Particle* p1 = new Particle({ -10,5,0 }, { 0,0,0 }, { 0,0,0 }, 200, 10000, 0.85, Particle::BOX);
	_particles.push_back(p1);
	BouyancyForceGenerator* f1 = new BouyancyForceGenerator(this, 8, 10, 2);
	vector<ForceGenerator*> _f1;
	_f1.push_back(f1);
	_f1.push_back(new GravityGenerator(this, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -9.8, 0)));
	p1->addForceGenerator(_f1);
}









