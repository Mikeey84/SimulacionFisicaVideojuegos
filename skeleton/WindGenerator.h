#pragma once
#include "ForceGenerator.h"

class ParticleSystem;

class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, Vector3 windSpeed, float k1, float k2, bool eazy);
	void update(double t) override;

	float areaOfObject(float radius);
	Vector3 _windSpeed;
	
	ParticleSystem* _pS = nullptr;
	float _k1, _k2;
	bool _easy;
};

