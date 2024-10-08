#pragma once

#include "PxPhysics.h"
#include "PxShape.h"
#include "Particle.h"
#include <cmath>

using namespace physx;

constexpr float GRAVEDAD = -9.86;
class Proyectil
{
	float _v;
	PxVec3 _vS;
	PxVec3 _vR;
	double _gS;
	float _mR;
	float _mS;
public: 
	Particle* _particle = nullptr;
	Proyectil(PxTransform camera, PxVec3 dir, float vel, float m, float escalar);
	void Escalado(float escalar);

};

