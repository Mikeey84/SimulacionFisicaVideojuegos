#pragma once
#include <random>
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"


class ForceGenerator
{
public:
	ForceGenerator(Vector3 pos, Vector3 area);
	~ForceGenerator() {};
	bool checkArea(Vector3 pos);
	virtual void update(double t) = 0;

protected:
	Vector3 _pos;
	float areaX, areaY, areaZ;
};

