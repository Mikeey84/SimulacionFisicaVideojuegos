#include "Proyectil.h"
#include "ParticleSystem.h"

Proyectil::Proyectil(PxTransform camera, PxVec3 dir, float  vel, float m, float escalar) : _v(vel), _mR(m) {
	_vR = dir;
	Escalado(escalar);

	// Modificar la velocidad
	double vr2 = sqrt(pow(_vR.x, 2) + pow(_vR.y, 2) + pow(_vR.z, 2));
	double vs2 = sqrt(pow(_vS.x, 2) + pow(_vS.y, 2) + pow(_vS.z, 2));
	// Masa
	_mS = _mR * pow(vr2,2) / pow(vs2,2);

	
	// Modificar la gravedad
	_gS = GRAVEDAD * pow(vs2,2) / pow(_v, 2);
	_particle = new Particle(camera.p, _vS, PxVec3(0, _gS, 0), 0, 10, 0);
}

void Proyectil::Escalado(float escalar) {
	_vS = _vR * _v / escalar;
}

Pistol::Pistol(ParticleSystem* pS, Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float vel, float mass, float shootingTime)
	: Gun(pS, cam, gPhysics, gScene, vel, mass, shootingTime) {
	_lastTimeShoot = shootingTime; // Para que pueda disparar directamente sin espera
}
void Pistol::update(double t) {
	_lastTimeShoot += t;

	if (_canShoot) { // Dispara 
		// Añadir Rb
		_pS->addRBParticlesC(_cam->getTransform().p, _cam->getDir() * _vel, 1000, 1000, { 1.0, 0.843, 0.0, 1 },
			10, _pS->_forcesModelGravityWind, 50);

		_canShoot = false; 
	}
}

void Pistol::shoot() {
	if (_lastTimeShoot > _shootingTime) {
		_canShoot = true;
		_lastTimeShoot = 0;
	}
}

Rafaga::Rafaga(ParticleSystem* pS, Camera* cam, PxPhysics* gPhysics, PxScene* gScene, float timeBetShoot,
	float shootingTime, int n, float vel, float mass)
	: Gun(pS, cam, gPhysics, gScene, vel, mass, shootingTime), _timeBetShoot(timeBetShoot), _numberOfShoots(n) {
	_lastTimeShoot = shootingTime; // Para que pueda disparar directamente sin espera
}

void Rafaga::update(double t) {
	_lastTimeAdd += t; // Suma de contadores para disparos
	_lastTimeShoot += t;

	if (_canShoot && _lastTimeAdd > _timeBetShoot) { // Dispara 
		// Añadir Rb
		_pS->addRBParticlesC(_cam->getTransform().p, _cam->getDir() * _vel, 1000, 1000, { 1.0, 0.843, 0.0, 1 },
			10, _pS->_forcesModelGravity, 10);

		_lastTimeAdd = 0;
		_index++;
		if (_index == _numberOfShoots) {
			_canShoot = false; // Termina de disparar la rafaga
			_index = 0;
		}
	}
		
	
}

void Rafaga::shoot() {
	if (_lastTimeShoot > _shootingTime) {
		_canShoot = true;
		_lastTimeShoot = 0;
	}
}
