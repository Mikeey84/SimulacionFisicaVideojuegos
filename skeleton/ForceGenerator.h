#pragma once
#include <random>
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

class ParticleSystem;

class ForceGenerator
{
public:
	ForceGenerator(ParticleSystem* pS,Vector3 pos, Vector3 area);
	
	virtual void update(double t) = 0;
	bool checkArea(Vector3 pos);
protected:
	Vector3 _pos;
	Vector3 _area;
	ParticleSystem* _pS;
};

