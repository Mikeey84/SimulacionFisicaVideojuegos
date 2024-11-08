#pragma once
#include "ForceGenerator.h"

class ParticleSystem;

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k, double t, double tau);

	void update(double t) override;

	ParticleSystem* _pS;

	bool _explosion = false;
	float _k;
	double _t;
	double _tau;
};

