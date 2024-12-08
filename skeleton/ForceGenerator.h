#pragma once
#include <random>
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Particle.h"

class ParticleSystem;

class ForceGenerator
{
public:
	enum Type
	{
		GRAVITY,
		WIND,
		WHIRL,
		EXPLOSION,
		SPRING
	};
	ForceGenerator(ParticleSystem* pS,Vector3 pos, Vector3 area);
	
	virtual void update(double t, Particle* p) = 0;
	virtual Vector3 getForce(Vector3 pos) = 0;
	bool checkArea(Vector3 pos);
	bool checkCircleArea(Vector3 pos);
	Vector3 _force;
	Type _type;
protected:
	Vector3 _pos;
	Vector3 _area;
	ParticleSystem* _pS;
};

