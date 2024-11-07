#pragma once
#include "Particle.h"
#include "Generator.h"
#include <random>
#include "ForceGenerator.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
using namespace std;

class ParticleSystem
{
public:
	enum ForceType
	{
		GRAVITY,
		WIND

	};


	ParticleSystem();
	vector<Particle*> _particles;
	vector<Particle*> _particlesToErase;
	vector<Generator*> _generators;

	vector<ForceGenerator*> _forceGenerators;
	// lista/vector de generadores
	void update(double t);
	void addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass);
	void addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, float x2, float y2, float x3, float y3, float mass);
	void addForceGenerator(ForceType fT, Vector3 pos, Vector3 area, Vector3 gravity_speed, float k1, float k2, bool easy);
	void checkDeath(Particle* p);
	



};

