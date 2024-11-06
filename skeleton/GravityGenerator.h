#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(Vector3 pos, Vector3 area);
	~GravityGenerator() {};
	void update(double t) override;
};

