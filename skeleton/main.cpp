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
#include "ParticleSystem.h"
#include "SolidoRigido.h"
#include <vector>
#include "GeneraEscenaFinal.h"

std::string display_text = "PULSA \u0022ESPACIO\u0022 PARA EMPEZAR EL JUEGO";


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
ParticleSystem* sParticleSystem;
std::vector<Proyectil*> sProyectiles;
ForceGenerator* gravity;
ForceGenerator* wind;
ForceGenerator* whirlwind;
ExplosionGenerator* explosion;

Pistol* sPistol;
Rafaga* sRafaga;

GeneraEscenaFinal* EscenaFinal;
int sPuntos = 0;

void initGame() 
{
	display_text = "Puntos " + to_string(sPuntos);
	changeText(0, 0, PxVec4(0,0,0,1));
	//Armas
	sPistol = new Pistol(sParticleSystem, GetCamera(), gPhysics, gScene, 50, 10, 0.5);
	sParticleSystem->addGun(sPistol);
	sRafaga = new Rafaga(sParticleSystem, GetCamera(), gPhysics, gScene, 0.1, 0.5, 3, 70, 10);
	sParticleSystem->addGun(sRafaga);
	sParticleSystem->addGenerator(Generator::ENEMY, PxVec3(0, 10, 0), 1, 10, 100, 0, 0, 0, 0, 0, 0, 10, 50);
	sParticleSystem->_generators[0]->addForceGenerator(gravity);
	// Escena con las armas
	EscenaFinal = new GeneraEscenaFinal(GetCamera(), sParticleSystem, gPhysics, gScene, sPistol, sRafaga);
	EscenaFinal->_start = true;
}

void menuPrincipal() 
{

}


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	//glutFullScreen();
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



	sParticleSystem = new ParticleSystem(gPhysics, gScene);
	//---------------------FORCEGENERATORS-----------------------------//
	
	gravity = new GravityGenerator(sParticleSystem, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, -10, 0));
	wind = new WindGenerator(sParticleSystem, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(30, 0, 0), 0.2,0,true);


	whirlwind = new WhirlwindGenerator(sParticleSystem, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.4);
	explosion = new ExplosionGenerator(sParticleSystem, Vector3(0, 20, 0), Vector3(0, 0, 0), 100000000, 0.1, 0.1);

	//sParticleSystem->addForceGenerator(ParticleSystem::ForceType::GRAVITY, Vector3(0, 0, 0), Vector3(10000, 10000, 10000), Vector3(0, -10, 0), 0, 0, false, 0, 0);
	//sParticleSystem->addForceGenerator(ParticleSystem::ForceType::GRAVITY, Vector3(0, 0, 0), Vector3(10000, 10000, 10000), Vector3(0, 50, 0), 0, 0, false, 0, 0);
	//sParticleSystem->addForceGenerator(ParticleSystem::ForceType::WIND, Vector3(0, 0, 0), Vector3(10000, 10000, 10000), Vector3(30, 0, 0), 0.2, 0, true, 0, 0);
	//sParticleSystem->addForceGenerator(ParticleSystem::ForceType::WHIRLWIND, Vector3(0, 0, 0), Vector3(10000, 10000, 10000), Vector3(0, 0, 0), 0.06, 0, false, 0, 0);

	//sParticle = new Particle(PxVec3(0,0,0), PxVec3(3, 0, 0), PxVec3(0,5,0));

	//sParticleSystem->addGenerator(Generator::UNIFORM, PxVec3(0,0,0), 0.01, 100, 10000, -1, 1, 20, 25, -1, 1, 1);
	


	//-----------------------------PRACTICAFUERZAS--------------------------------------------------------------
	/*sParticleSystem->addGenerator(Generator::UNIFORM, PxVec3(0,0,0), 0.001, 100, 10000, -5, 5, 20, 25, -5, 5, 1,0);
	sParticleSystem->_generators[0]->addForceGenerator(gravity);
	sParticleSystem->_generators[0]->addForceGenerator(explosion);*/

	//sParticleSystem->_generators[0]->addForceGenerator(wind);
	//sParticleSystem->_generators[0]->addForceGenerator(whirlwind);
	
	// 
	//sParticleSystem->_generators[0]->changeColor(Vector4{ 1, 0, 1, 1 });

	/*sParticleSystem->addGenerator(Generator::GAUSS, PxVec3(0,40,0), 0.1, 10, 100, 2, 2, 0, 2, 15, 2, 100, 0);*/
	/*sParticleSystem->addGenerator(Generator::UNIFORM, PxVec3(0, 35, 0), 0.001, 100, 10000, -5, 5, 20, 25, -5, 5, 1, 0);
	sParticleSystem->_generators[1]->changeColor(Vector4{ 1, 0, 1, 1 });*/
	
	/*sParticleSystem->addGenerator(Generator::GAUSS, PxVec3(50,0,-100), 0.1, 1000, 10000, 0,10, 0,0, 0 ,10, 10);
	sParticleSystem->_generators[2]->changeColor(Vector4{ 0, 0, 1, 1 });*/
	/*sParticleSystem->addGenerator(Generator::GAUSS, PxVec3(50,0,-100), 0.1, 10, 100, 0,10, 0,0, 0 ,10, 10);
	sParticleSystem->_generators[2]->changeColor(Vector4{ 0, 0, 1, 1 });*/
	
	
	//------------------------------MUELLES----------------------------------------

	//sParticleSystem->generateSpringDemo();
	//sParticleSystem->generateBouyancyDemo();



	//---------------------------SOLIDORIGIDO-------------------------------------
	/*PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({0,0,0}));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	gScene->addActor(*suelo);
	RenderItem* _dynamicItem;
	_dynamicItem = new RenderItem(shape, suelo, { 1,1,1,1 });
	RegisterRenderItem(_dynamicItem);

	
	sParticleSystem->addGenerator(Generator::UNIFORM_RB, PxVec3(0, 0, 0), 1, 100, 10000, -5, 5, 30, 35, -5, 5, 1, 5);
	sParticleSystem->_generators[0]->_c = { 1,0,1,1 };
	sParticleSystem->_generators[0]->addForceGenerator(gravity);
	sParticleSystem->_generators[0]->addForceGenerator(wind);*/



	//--------------------------PRACTICAFINAL------------------------------------




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

	if (sProyectiles.size() > 0) {
		for (Proyectil* e : sProyectiles) {
			e->_particle->integrate(t);
		}
	}
	sParticleSystem->update(t);
	if(EscenaFinal != nullptr)
		EscenaFinal->update(t);
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
		sPistol->shoot();
		break;
	case 'E':
		
		break;
	case 'R':
		sRafaga->shoot();
		break;
	case ' ':
	{
		initGame();
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);

	for(SolidoRigido* s : sParticleSystem->_solidosRigidos){

		if ((actor1 == s->_newSolid || actor2 == s->_newSolid)) {
			s->_maxTime = 0;
		}
		
	}
	//for (SolidoRigido* s : sParticleSystem->_solidosEnemigos) {
	//	if ((actor1 == s->_newSolid || actor2 == s->_newSolid)) { // Si uno de los 2 es una caja
	//		if (actor1->getType() != PxActorType::eRIGID_STATIC && actor2->getType() != PxActorType::eRIGID_STATIC) {
	//			
	//		}
	//	}
	//}
	for (SolidoRigido* s1 : sParticleSystem->_solidosRigidos) {
		for (SolidoRigido* s2 : sParticleSystem->_solidosEnemigos) {
			if(actor1 == s1->_newSolid && actor2 == s2->_newSolid){
				s2->_maxTime = 0;
				
				sPuntos += s1->_points;
				display_text = "Puntos " + to_string(sPuntos);
			}
		}
	}
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