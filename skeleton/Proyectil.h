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

class ParticleSystem;

class Gun {
public:
	Gun(ParticleSystem* pS, Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float vel, float mass, float shootingTime) :
		_cam(cam), _gPhysics(gPhysics), _gScene(gScene), _vel(vel), _mass(mass), _shootingTime(shootingTime), _pS(pS){}
	virtual void update(double t) = 0;
	virtual void shoot() = 0;
protected:
	Camera* _cam = nullptr;
	float _vel;
	float _mass;
	bool _canShoot = false;
	float _lastTimeAdd = 0;
	float _lastTimeShoot;
	float _shootingTime;
	ParticleSystem* _pS = nullptr;
	PxPhysics* _gPhysics = nullptr;
	PxScene* _gScene = nullptr;
};

class Pistol : public Gun {
public:
	Pistol(ParticleSystem* pS, Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float vel, float mass, float shootingTime);
	~Pistol() {};
	virtual void update(double t) override;
	virtual void shoot() override;
}; 

class Rafaga : public Gun {
public: 
	Rafaga(ParticleSystem* pS, Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float timeBetShoot, float shootingTime, int n, float vel, float mass);
	~Rafaga() {};
	virtual void update(double t) override;
	virtual void shoot()override;
	float _timeBetShoot;
	float _numberOfShoots;
	float _index = 0;
};