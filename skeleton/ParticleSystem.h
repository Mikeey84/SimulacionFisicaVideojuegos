#pragma once
#include "Particle.h"
#include "Generator.h"
#include <random>

using namespace std;

class ParticleSystem
{
public:
	ParticleSystem();
	vector<Particle*> _particles;
	vector<Particle*> _particlesToErase;
	vector<Generator*> _generators;
	// lista/vector de generadores
	void update(double t);
	void addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color);
	void addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, float x2, float y2, float x3, float y3);
	void checkDis(Particle* p);
	void checkDeath(Particle* p);
};

