#pragma once
#include "Vector3D.cpp"
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
#include <iostream>
#include <cmath>



using namespace physx;
using namespace std;

class ForceGenerator;

class Particle {

public:
	enum Type
	{
		BOX,
		PLANE
	};
	Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc, float maxDis, double maxTime, float mass, Vector4 color = Vector4{1,1,1,1});
	Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc, float maxDis, double maxTime, float mass, Type type);

	~Particle() {

		DeregisterRenderItem(_renderItem); //deregistrar el item
		//_renderItem->release();
		//delete _renderItem;
		
		_renderItem = nullptr;
		
	};

	void integrate(double t);
	bool checkDeath();
	bool checkDis();
	void addForce(Vector3 newForce);
	void addForceGenerator(vector<ForceGenerator*> _fGs);

	PxVec3 _vel;
	PxTransform _pose;
	PxVec3 _pos;
	PxVec3 _acc;
	PxVec3 _area;
	PxVec4 _color;
	float _maxDis;
	RenderItem* _renderItem = nullptr;
	float _damping;
	double _time = 0, _maxTime;
	bool _isAlive = true;
	PxVec3 _forces = { 0,0,0 }; // Vector aditivo para sumar las fuerzas
	float _mass;
	vector<ForceGenerator*> _forcesG;
};