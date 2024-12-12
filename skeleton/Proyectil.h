#pragma once

#include "PxPhysics.h"
#include "PxScene.h"
#include "PxShape.h"
#include "Particle.h"
#include "core.hpp"
#include <cmath>
#include "SolidoRigido.h"

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

class Gun {
public:
	Gun(Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float vel, float mass) :
		_cam(cam), _gPhysics(gPhysics), _gScene(gScene), _vel(vel), _mass(mass) {}
	virtual void update(double t) = 0;
protected:
	Camera* _cam = nullptr;
	float _vel;
	float _mass;
	float _lastTimeAdd;
	PxPhysics* _gPhysics = nullptr;
	PxScene* _gScene = nullptr;
};

class Pistol : public Gun {
public:
	Pistol(Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float vel, float mass);
	virtual void update(double t) {}
}; 

class Rafaga : Gun {
public: 
	Rafaga(Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float timeBetShoot, int n, float vel, float mass);
	virtual void update(double t);
	float _timeBetShoot;
	float _n;
};