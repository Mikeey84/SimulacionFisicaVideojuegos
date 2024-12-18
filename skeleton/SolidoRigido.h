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
class ParticleSystem;

class SolidoRigido
{
public:
	SolidoRigido(ParticleSystem* pS, PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel, Vector3 angularVel,
		double maxDis, double maxTime, float mass, Vector4 color = Vector4{ 1,1,1,1 });

	SolidoRigido(ParticleSystem* ps, PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel,
		double maxDis, double maxTime, float mass, Vector4 color = Vector4{ 1,1,1,1 });

	~SolidoRigido() {
		DeregisterRenderItem(_dynamicItem); //deregistrar el item
		delete _dynamicItem;
		//_dynamicItem = nullptr;
		//_dynamicItem->release();
		_dynamicItem = nullptr;
	};
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
	ParticleSystem* _pS = nullptr;
	bool _isAlive = true;
	bool _bola;
	RenderItem* _dynamicItem;
};

