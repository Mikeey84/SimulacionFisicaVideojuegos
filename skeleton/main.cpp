#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.cpp"
#include "Particle.h"
#include "Proyectil.h"
#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* sSphere;
RenderItem* sSphereRed;
RenderItem* sSphereGreen;
RenderItem* sSphereBlue;
Particle* sParticle;
std::vector<Proyectil*> sProyectiles;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;

	//PxShape* sph = CreateShape(PxSphereGeometry(2), gMaterial);
	PxSphereGeometry geo;
	geo.radius = 1;
	sSphere = new RenderItem();
	sSphere->transform = new PxTransform(PxVec3(0, 0, 0));
	sSphere->color = Vector4{ 1,1,1,1 };
	sSphere->shape = CreateShape(geo);
	gScene = gPhysics->createScene(sceneDesc);
	//sSphere = new RenderItem(sph, &PxTransform{ 0,0,0 }, Vector4{ 1,1,1,1 });
	// Ejes


	Vector3D<float> v1(1,0,0);
	Vector3D<float> v2(0,1,0);
	Vector3D<float> v3 = v1*v2;

	sSphereRed = new RenderItem();
	sSphereRed->transform = new PxTransform(PxVec3(v1._x, v1._y, v1._z)*10);
	sSphereRed->color = Vector4{ 1,0,0,1 };
	sSphereRed->shape = CreateShape(geo);

	sSphereGreen = new RenderItem();
	sSphereGreen->transform = new PxTransform(PxVec3(v2._x, v2._y, v2._z)*10);
	sSphereGreen->color = Vector4{ 0,1,0,1 };
	sSphereGreen->shape = CreateShape(geo);
	
	sSphereBlue = new RenderItem();
	sSphereBlue->transform = new PxTransform(PxVec3(v3._x, v3._y, v3._z)*10);
	sSphereBlue->color = Vector4{ 0,0,1,1 };
	sSphereBlue->shape = CreateShape(geo);


	//sParticle = new Particle(PxVec3(0,0,0), PxVec3(3, 0, 0), PxVec3(0,5,0));


	//Registers
	/*RegisterRenderItem(sSphere);
	RegisterRenderItem(sSphereRed);
	RegisterRenderItem(sSphereGreen);
	RegisterRenderItem(sSphereBlue);*/
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t) // pasar la t
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);
	//sParticle->integrate(t);
	for (Proyectil* e : sProyectiles) {
		e->_particle->integrate(t);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	/*DeregisterRenderItem(sSphere);
	DeregisterRenderItem(sSphereRed);
	DeregisterRenderItem(sSphereGreen);
	DeregisterRenderItem(sSphereBlue);*/
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'P':
		
		sProyectiles.push_back(new Proyectil(GetCamera()->getTransform(), GetCamera()->getDir(), 50, 10, 1));
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}