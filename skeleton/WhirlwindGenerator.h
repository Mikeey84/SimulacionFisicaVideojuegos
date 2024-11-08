#pragma once
#include "ForceGenerator.h"

class ParticleSystem;

class WhirlwindGenerator : public ForceGenerator
{
public:
	WhirlwindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k);

	void update(double t) override;

	ParticleSystem* _pS = nullptr;
	float _k;
};

