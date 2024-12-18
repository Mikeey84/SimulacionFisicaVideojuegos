#pragma once
#include "core.hpp"
#include "Proyectil.h"
#include "PxScene.h"
#include "PxPhysics.h"
#include <iostream>
#include "ParticleSystem.h"
#include "SolidoRigido.h"
#include <vector>
#include <ostream>
#include "Generator.h"


class GeneraEscenaFinal
{
public:
	GeneraEscenaFinal(Camera* cam, ParticleSystem* pS, PxPhysics* gPhysics, PxScene* gScene, Pistol* sPistol, Rafaga* sRafaga);
	void CreateBox(PxVec3 position, PxVec3 dimensions, PxVec4 color);
	void CreateRamp(PxVec3 position, PxVec3 dimensions, PxVec4 color);
	ParticleSystem* _pS = nullptr;
	PxPhysics* _gPhysics = nullptr;
	PxScene* _gScene = nullptr;
	Pistol* _sPistol = nullptr;
	Rafaga* _sRafaga = nullptr;
	Camera* _cam = nullptr;

};

