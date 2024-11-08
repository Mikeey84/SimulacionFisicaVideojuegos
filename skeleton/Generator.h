#pragma once
#include <random>
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Particle.h"

class ParticleSystem;

using namespace physx;

class Generator
{
public:
	enum Type
	{
		UNIFORM,
		GAUSS
	};
	Generator(ParticleSystem* pS, Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, float x2, float y2, float x3, 
		float y3, float mass, ForceGenerator* fG);
	
	void update(double t);

	Type _type;
	PxVec3 _pos;
	double _time, _maxDis, _maxTime, _lastTimeAdd = 0;
	Vector4 _c = {1,1,1,1};
	double _x1, _x2, _x3, _y1, _y2, _y3;
	float _mass;
	ParticleSystem* _pS;
	float generateGauss(float mean, float dv);
	float generateUniform(float min, float max);
	void changeColor(Vector4 color) {
		_c = color;
	};
	ForceGenerator* _fG = nullptr;
	
};

