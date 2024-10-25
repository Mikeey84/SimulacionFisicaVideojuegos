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
	Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color = Vector4{1,1,1,1});
	~Particle() {
		DeregisterRenderItem(_renderItem); //deregistrar el item
		//delete _renderItem;
		_renderItem = nullptr;
	};

	void integrate(double t);
	bool checkDeath();

	PxVec3 _vel;
	PxTransform* _pose;
	PxVec3 _pos;
	PxVec3 _acc;
	PxVec4 _color;
	double _maxDis;
	RenderItem* _renderItem = nullptr;
	float _damping;
	double _time = 0, _maxTime;
};