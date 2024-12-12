#pragma once
#include "PxPhysics.h"
#include "PxScene.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include "ForceGenerator.h"
#include "WindGenerator.h"
using namespace physx;

class SolidoRigido
{
public:
	SolidoRigido(PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel, Vector3 angularVel,
		double maxDis, double maxTime, float mass, Vector4 color = Vector4{ 1,1,1,1 });

	SolidoRigido(PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel,
		double maxDis, double maxTime, float mass, Vector4 color = Vector4{ 1,1,1,1 });

	~SolidoRigido();
	void addForceGenerator(vector<ForceGenerator*> _fGs);
	void update();
	PxRigidDynamic* _newSolid;
	vector<ForceGenerator*> _forcesG;
	PxVec3 _linearVel;
	PxVec3 _angularVel;
	PxTransform* _pos;
	PxVec3 _area;
	PxVec4 _color;
	float _maxDis;
	float _maxTime;
	float _mass;
};

