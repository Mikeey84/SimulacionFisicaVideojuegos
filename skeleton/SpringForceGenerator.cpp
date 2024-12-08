#include "SpringForceGenerator.h"
#include "ParticleSystem.h"
SpringForceGenerator::SpringForceGenerator(ParticleSystem* pS, double k, double restingLength, Particle* other) : ForceGenerator(pS, {0,0,0}, {0,0,0}), _k(k),
_restingLenght(restingLength), _other(other), _pS(pS) {
	_type = ForceGenerator::SPRING;
}

void SpringForceGenerator::update(double t, Particle* p) {
	
	_force = getForce(p->_pos);
	p->addForce(_force);
}

Vector3 SpringForceGenerator::getForce(Vector3 pos)
{
	Vector3 relativePosVector = _other->_pos - _pos;

	const float length = relativePosVector.normalize();
	const float deltaX = length - _restingLenght;

	Vector3 force = relativePosVector * deltaX * _k;
	return force;
}
