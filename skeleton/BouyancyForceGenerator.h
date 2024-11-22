#pragma once
#include "ForceGenerator.h"

class ParticleSystem;
class BouyancyForceGenerator : public ForceGenerator
{
public:
	BouyancyForceGenerator(ParticleSystem* pS, float h, float V, float d);

	virtual void update(double t, Particle* p);

	virtual ~BouyancyForceGenerator() {};

protected:
	float _height;
	float _volume;
	float _liquidDensity;
	const float _gravity = 9.8;

	Particle* _liquidParticle;
};

