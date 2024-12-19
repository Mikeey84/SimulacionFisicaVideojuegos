#pragma once
#include "ForceGenerator.h"

class ParticleSystem;

class WhirlwindGenerator : public ForceGenerator
{
public:
	WhirlwindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k);

	void update(double t, Particle* p) override;
	Vector3 getForce(Vector3 pos) override;
	Vector3 getF(Vector3 pos, Vector3 initPos) override { return Vector3(); };
	ParticleSystem* _pS = nullptr;
	float _k;
};

