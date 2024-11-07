#include "WindGenerator.h"
#include "ParticleSystem.h"

WindGenerator::WindGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, Vector3 windSpeed, float k1, float k2, bool easy) : 
	ForceGenerator(pS, pos, area), _windSpeed(windSpeed), _pS(pS), _k1(k1), _k2(k2), _easy(easy) {
}

void WindGenerator::update(double t) {
	for (int i = 0; i < _pS->_particles.size(); ++i) {
		// Si la particula esta dentro del area aplicamos la formula con k2 = 0 de momenento
		if (checkArea(_pS->_particles[i]->_pos)){
			if (_easy) {
				Vector3 pVel = _pS->_particles[i]->_vel;
				_force = _k1 * (_windSpeed - pVel) + _k2 * (_windSpeed - pVel).magnitude() * (_windSpeed - pVel);
				_pS->_particles[i]->addForce(_force);
			}
			else {
				Vector3 velReal = _windSpeed - _pS->_particles[i]->_vel;
				Vector3 vel2 = velReal * velReal;
				_force = (areaOfObject(1) * 0.5 * 1.2) * vel2;
				std::cout << velReal.x << " " << velReal.y << " " << velReal.z << std::endl;
				_pS->_particles[i]->addForce(_force);
			}
			
		}
	}
}

float WindGenerator::areaOfObject(float radius)
{
	const double pi = 3.141592653589793;

	return 4 * pi * radius * radius;


}
