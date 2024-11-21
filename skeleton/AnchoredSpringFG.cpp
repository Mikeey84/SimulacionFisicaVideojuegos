#include "AnchoredSpringFG.h"
#include "ParticleSystem.h"

AnchoredSpringFG::AnchoredSpringFG(ParticleSystem* pS, double k, double resting, const Vector3& anchorPos) : 
	SpringForceGenerator(pS, k,resting, nullptr) {
	_other = new Particle(anchorPos, { 0,0,0 }, { 0,0,0 }, 500, 10000, 1e6, Particle::BOX);
}
