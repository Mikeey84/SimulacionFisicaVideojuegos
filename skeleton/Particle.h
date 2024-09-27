#pragma once
#include "Vector3D.cpp"
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
#include <iostream>
#include <cmath>

using namespace physx;

class Particle {
public:
	Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc);
	~Particle() {
		DeregisterRenderItem(_renderItem); //deregistrar el item
		delete _renderItem;
	};

	void integrate(double t);

private:
	PxVec3 _vel;
	PxTransform* _pose;
	PxVec3 _pos;
	PxVec3 _acc;
	RenderItem* _renderItem = nullptr;
	float _damping;
};