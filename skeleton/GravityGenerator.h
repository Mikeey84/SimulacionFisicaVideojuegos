#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class ParticleSystem;

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, Vector3 gravity);
	~GravityGenerator() {};
	void update(double t, Particle* p) override;
	
	ParticleSystem* _pS = nullptr;
};

