#pragma once
#include "SpringForceGenerator.h"

class ParticleSystem; 

class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(ParticleSystem* ps, double k, double resting, const Vector3& anchorPos);

	~AnchoredSpringFG() { delete _other; };
};

