#include "GeneraEscenaFinal.h"

GeneraEscenaFinal::GeneraEscenaFinal(Camera* cam, ParticleSystem* pS, PxPhysics* gPhysics, PxScene* gScene, Pistol* sPistol, Rafaga* sRafaga) :
    _pS(pS), _gPhysics(gPhysics), _gScene(gScene), _sPistol(sPistol), _sRafaga(sRafaga), _cam(cam) {
    // Camara
    _cam->_canMove = false;
    
    std::cout << _cam->getTransform().p.x << " " << _cam->getTransform().p.y << " " << _cam->getTransform().p.z;

    // Suelo 
    PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0, 0, 0 }));
    PxShape* groundShape = CreateShape(PxBoxGeometry(100, 0.1, 100));
    suelo->attachShape(*groundShape);
    gScene->addActor(*suelo);
    RenderItem* groundItem = new RenderItem(groundShape, suelo, { 0.1, 0.1, 0.1, 1 }); 
    RegisterRenderItem(groundItem);

    // Paredes 
    PxRigidStatic* wallLeft = gPhysics->createRigidStatic(PxTransform({ -50, 25, 0 }));
    PxShape* wallLeftShape = CreateShape(PxBoxGeometry(0.1, 25, 100));
    wallLeft->attachShape(*wallLeftShape);
    gScene->addActor(*wallLeft);
    RenderItem* leftWallItem = new RenderItem(wallLeftShape, wallLeft, { 0.8, 0.8, 0.8, 1 }); 
    RegisterRenderItem(leftWallItem);

    PxRigidStatic* wallRight = gPhysics->createRigidStatic(PxTransform({ 50, 25, 0 }));
    PxShape* wallRightShape = CreateShape(PxBoxGeometry(0.1, 25, 100));
    wallRight->attachShape(*wallRightShape);
    gScene->addActor(*wallRight);
    RenderItem* rightWallItem = new RenderItem(wallRightShape, wallRight, { 0.8, 0.8, 0.8, 1 });
    RegisterRenderItem(rightWallItem);

    PxRigidStatic* backWall = gPhysics->createRigidStatic(PxTransform({ 0, 25, -50 }));
    PxShape* backWallShape = CreateShape(PxBoxGeometry(50, 25, 0.1));
    backWall->attachShape(*backWallShape);
    gScene->addActor(*backWall);
    RenderItem* backWallItem = new RenderItem(backWallShape, backWall, { 0.8, 0.8, 0.8, 1 });
    RegisterRenderItem(backWallItem);

    // Cajas 
    CreateBox({ -10, 5, -20 }, { 10, 10, 10 }, { 0.6, 0.3, 0.1, 1 }); 
    CreateBox({ 10, 5, -20 }, { 10, 10, 10 }, { 0.6, 0.3, 0.1, 1 });
    CreateBox({ 0, 15, -20 }, { 10, 10, 10 }, { 0.6, 0.3, 0.1, 1 });

    // Rampas 
    CreateRamp({ -20, 5, 10 }, { 20, 5, 10 }, { 0.8, 0.8, 0.8, 1 }); 
    CreateRamp({ 20, 5, 10 }, { 20, 5, 10 }, { 0.8, 0.8, 0.8, 1 });
}

void GeneraEscenaFinal::CreateBox(PxVec3 position, PxVec3 dimensions, PxVec4 color) {
    PxRigidStatic* box = _gPhysics->createRigidStatic(PxTransform(position));
    PxShape* boxShape = CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2));
    box->attachShape(*boxShape);
    _gScene->addActor(*box);
    RenderItem* boxItem = new RenderItem(boxShape, box, color);
    RegisterRenderItem(boxItem);
}

void GeneraEscenaFinal::CreateRamp(PxVec3 position, PxVec3 dimensions, PxVec4 color) {
    PxRigidStatic* ramp = _gPhysics->createRigidStatic(PxTransform(position));
    PxShape* rampShape = CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2));
    ramp->attachShape(*rampShape);
    _gScene->addActor(*ramp);
    RenderItem* rampItem = new RenderItem(rampShape, ramp, color);
    RegisterRenderItem(rampItem);
}

void GeneraEscenaFinal::update(double t) {

    

}

