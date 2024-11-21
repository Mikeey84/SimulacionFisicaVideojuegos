#pragma once
#include "ForceGenerator.h"

class ParticleSystem;

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(ParticleSystem* pS, double k, double restingLength, Particle* other);

	virtual void update(double t,Particle* p);

	inline void setk(double k) { _k = k; }
	
	virtual ~SpringForceGenerator(){};

protected: 
	double _k;
	double _restingLenght;
	Particle* _other;
	ParticleSystem* _pS;
};


