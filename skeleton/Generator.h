#pragma once
#include <random>
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Particle.h"

class ParticleSystem;

using namespace physx;

class Generator
{
public:
	enum Type
	{
		UNIFORM,
		UNIFORM_RB,
		GAUSS,
		GAUSS_RB,
		ENEMY
	};
	Generator(ParticleSystem* pS, Type type, PxVec3 pos, double time, double maxDis, double maxTime, float x1, float y1, 
		float x2, float y2, float x3, 
		float y3, float mass, int maxCount);
	

	void update(double t);

	Type _type;
	PxVec3 _pos;
	double _time, _maxDis, _maxTime, _lastTimeAdd = 0;
	Vector4 _c = {1,1,1,1};
	double _x1, _x2, _x3, _y1, _y2, _y3;
	float _mass;
	int _count = 0;
	int _maxCount;
	ParticleSystem* _pS;
	float generateGauss(float mean, float dv);
	float generateUniform(float min, float max);
	void changeColor(Vector4 color) {
		_c = color;
	};
	vector<ForceGenerator*> _forces;
	void addForceGenerator(ForceGenerator* fG);

	// Para enemigos
	std::vector<Vector3> _enemyPositions = {
	{ 0, 2, 0 },            // Suelo
	{ -50, 2, 0 },         // Pared izquierda
	{ -10, 2, -20 },        // Caja izquierda
	{ 0, 11, -20 },         // Caja central
	{ -20, 6, 10 },         // Rampa izquierda
	{ 20, 6, 10 }           // Rampa derecha
	};
	Vector3 _prevPos;
	void addEnemies();
	void addRandomEnemy();
	std::random_device rd;
	std::mt19937 gen;
};

