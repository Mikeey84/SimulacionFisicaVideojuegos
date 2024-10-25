#include "Generator.h"
#include "ParticleSystem.h"

Generator::Generator(ParticleSystem* pS, Type type, PxVec3 pos, double time, double maxDis, double maxTime, 
	float x1, float y1, float x2, float y2, float x3, float y3) :
	_pS(pS), _type(type), _pos(pos), _time(time), _maxDis(maxDis), _maxTime(maxTime)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
	_x3 = x3;
	_y3 = y3;
}

void Generator::update(double t) {
	_lastTimeAdd += t;
	if (_lastTimeAdd > _time) {
		switch (_type) {
		case UNIFORM:
			_pS->addParticles(_pos, { generateUniform(_x1,_y1), generateUniform(_x2,_y2), generateUniform(_x3,_y3)}, {0.0f,-10.0f,0.0f}, _maxDis, _maxTime);
			
			_lastTimeAdd = 0;
			break;
		case GAUSS:
			_pS->addParticles(_pos, { generateGauss(_x1, _y1), generateGauss(_x2,_y2), generateGauss(_x3, _y3) }, { 0.0f,-10.0f,0.0f }, _maxDis, _maxTime);

			_lastTimeAdd = 0;
			break;
		}
	}
	
}

float Generator::generateGauss(float mean, float dev) {
	if (dev == 0.0f) {
		return mean;  // Si la desviación es 0, siempre retornamos la media
	}

	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::normal_distribution<float> distribution(mean, dev);
	return distribution(generator);
}

float Generator::generateUniform(float min, float max) {
	std::random_device rd;  
	std::mt19937 gen(rd()); 

	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);

}
