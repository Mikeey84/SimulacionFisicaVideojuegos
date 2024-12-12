#pragma once
#include "Particle.h"
#include "Generator.h"
#include <random>
#include "ForceGenerator.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BouyancyForceGenerator.h"
#include "SolidoRigido.h"
#include "PxScene.h"
#include "Proyectil.h"

using namespace std;

class ParticleSystem
{
public:
	enum ForceType
	{
		GRAVITY,
		WIND,
		WHIRLWIND,
		EXPLOSION

	};

	PxPhysics* _gPhysics;
	PxScene* _gScene;

	ParticleSystem(PxPhysics* gPhysics, PxScene* gScene);
	vector<Particle*> _particles;
	vector<SolidoRigido*> _solidosRigidos;
	vector<Particle*> _particlesToErase;
	vector<Generator*> _generators;
	vector<Gun*> _guns;
	vector<ForceGenerator*> _forceGenerators;
	vector<ForceGenerator*> _forcesModelGravity;
	vector<ForceGenerator*> _forcesModelGravityWind;
	// lista/vector de generadores
	void update(double t);
	void addParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG);
	void addRBParticles(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color, float mass, vector<ForceGenerator*> fG);
	void addGenerator(Generator::Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, float x2, float y2, float x3, 
		float y3, float mass, int maxCount);
	void addForceGenerator(ForceType fT, Vector3 pos, Vector3 area, Vector3 gravity_speed, float k1, float k2, bool easy, double t, double tau);

	void addGun(Gun* g) {
		_guns.push_back(g);
	}

	void checkDeath(Particle* p);
	
	void generateSpringDemo();
	void generateBouyancyDemo();

};

