#include "Particle.h"
#include "ForceGenerator.h"

Particle::Particle(ForceGenerator* fG, PxVec3 pos, PxVec3 vel, PxVec3 acc, float maxDis, double maxTime, float mass, Vector4 color) :
	_pos(pos), _vel(vel), _acc(acc), _maxDis(maxDis), _maxTime(maxTime), _mass(mass), _fG(fG)
	{
		PxSphereGeometry geo(1);
		PxShape* shape = CreateShape(geo);
		_color = color;
		_area = { abs(pos.x) + _maxDis, abs(pos.y) + _maxDis , abs(pos.z) + _maxDis };
		_pose = physx::PxTransform(_pos);
		_renderItem = new RenderItem(shape, &_pose, _color);
		RegisterRenderItem(_renderItem);
		_damping = 0.99;
	}

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc, float maxDis, double maxTime, float mass, Vector4 color) :
	_pos(pos), _vel(vel), _acc(acc), _maxDis(maxDis), _maxTime(maxTime), _mass(mass)
{
	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);
	_color = color;
	_area = { abs(pos.x) + _maxDis, abs(pos.y) + _maxDis , abs(pos.z) + _maxDis };
	_pose = physx::PxTransform(_pos);
	_renderItem = new RenderItem(shape, &_pose, _color);
	RegisterRenderItem(_renderItem);
	_damping = 0.99;
}
	


void Particle::integrate(double t) { // t = tiempo de simulacion 
	// Llamar al generador de fuerzas para que solo se actualice ese
	_fG->update(t, this);

	// Movimiento de particula con velocidad
	_time += t;
	_pos = _pos + _vel * t;

	// Añadir las fuerzas a la aceleracion
	_acc = _forces / _mass ;
	
	// Calculo velocidad
	_vel = _vel * pow(_damping, t) + _acc * t;

	// Aplicacion del movimiento de la particula 
	_pose.p = physx::PxVec3(_pos);

	// Reset de acumulador de fuerzas
	this->_forces = { 0,0,0 }; 

}

bool Particle::checkDeath()
{
	if (_time > _maxTime) return true;
	return false;
}

bool Particle::checkDis() {
	return (abs(_pos.x) > _area.x || abs(_pos.y) > _area.x || abs(_pos.z) > _area.x);
}

void Particle::addForce(Vector3 newForce) { // Metodo que añade lña nueva fuerza para que se aplique
	_forces += newForce;
}


