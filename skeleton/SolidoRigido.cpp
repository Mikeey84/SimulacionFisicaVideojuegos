#include "SolidoRigido.h"
#include "ParticleSystem.h"

SolidoRigido::SolidoRigido(ParticleSystem* pS, PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel, Vector3 angularVel,
	double maxDis, double maxTime, float mass, Vector4 color) :
	_pos(gTransform), _linearVel(linearVel), _angularVel(angularVel), _maxDis(maxDis), _maxTime(maxTime), _mass(mass), _pS(pS)
{
	_newSolid = gPhysics->createRigidDynamic(*_pos);
	_newSolid->setLinearVelocity(linearVel);
	_newSolid->setAngularVelocity(angularVel);
	PxShape* shape_ad = CreateShape(PxBoxGeometry(2, 2, 2));
	_newSolid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*_newSolid, 0.5);
	gScene->addActor(*_newSolid);
	_newSolid->setMass(_mass);
	_dynamicItem = new RenderItem(shape_ad, _newSolid, color);
	RegisterRenderItem(_dynamicItem);
	_bola = false;
	_initialPos = _pos->p;
}

SolidoRigido::SolidoRigido(ParticleSystem* pS, PxPhysics* gPhysics, PxScene* gScene, PxTransform* gTransform, Vector3 linearVel,
	double maxDis, double maxTime, float mass, int points, Vector4 color) :
	_pos(gTransform), _linearVel(linearVel), _angularVel({0,0,0}), _maxDis(maxDis), _maxTime(maxTime), _mass(mass), _pS(pS), _points(points) {
	_newSolid = gPhysics->createRigidDynamic(*_pos);
	_newSolid->setLinearVelocity(linearVel);
	_newSolid->setAngularVelocity({0,0,0});
	PxShape* shape_ad = CreateShape(PxSphereGeometry(0.5));
	_newSolid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*_newSolid, 0.15);
	gScene->addActor(*_newSolid);
	_newSolid->setMass(_mass);
	_dynamicItem = new RenderItem(shape_ad, _newSolid, color);
	RegisterRenderItem(_dynamicItem);
	_bola = true;
	_initialPos = _pos->p;
}

void SolidoRigido::addForceGenerator(vector<ForceGenerator*> _fGs) {
	_forcesG = _fGs;
	/*for (ForceGenerator* f : _fGs) {
		_newSolid->addForce(f->_force, PxForceMode::eFORCE);
	}*/
}

void SolidoRigido::update(double t) {
	_livingTime += t;
	if (_livingTime > _maxTime) _maxTime = 0;
	if (_maxTime == 0 && _isAlive) {
		if (_bola) {
			_pS->_solidosToErase.push_back(this);
		}
		else {
			_pS->_enemigosToErase.push_back(this);
		}


		_isAlive = false;
	}
	else {
		for (ForceGenerator* f : _forcesG) {
			if (f->_type == ForceGenerator::WIND) {
				if (f->getForce(_linearVel).magnitude() > 1 && f->getForce(_linearVel).magnitude() < 1000)
					_newSolid->addForce(f->getForce(_linearVel), PxForceMode::eFORCE);
			}
			else if(f->_type == ForceGenerator::GRAVITY){
				if (f->getForce(_pos->p).magnitude() > 1 && f->getForce(_pos->p).magnitude() < 20)
					_newSolid->addForce(f->getForce(_pos->p), PxForceMode::eFORCE);
			}
			else if (f->_type == ForceGenerator::BOUYANCY) {
				//if (f->getForce(_pos->p).magnitude() > 1 && f->getForce(_pos->p).magnitude() < 20)
					//cout << f->getF(_pos->p, _initialPos).x << " " << f->getF(_pos->p, _initialPos).y << " " << f->getF(_pos->p, _initialPos).z << endl;
					_newSolid->addForce(f->getF(_pos->p, _initialPos), PxForceMode::eFORCE);
			}
		}
	}
	
}


