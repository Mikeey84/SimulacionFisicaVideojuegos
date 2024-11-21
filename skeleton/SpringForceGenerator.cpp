#include "SpringForceGenerator.h"
#include "ParticleSystem.h"
SpringForceGenerator::SpringForceGenerator(ParticleSystem* pS, double k, double restingLength, Particle* other) : ForceGenerator(pS, {0,0,0}, {0,0,0}), _k(k),
_restingLenght(restingLength), _other(other), _pS(pS) {

}

void SpringForceGenerator::update(double t, Particle* p) {
	Vector3 relativePosVector = _other->_pos - p->_pos;

	const float length = relativePosVector.normalize();
	const float deltaX = length - _restingLenght;

	Vector3 force = relativePosVector * deltaX * _k;

	p->addForce(force);
}
