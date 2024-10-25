#include "Particle.h"


Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc, double maxDis, double maxTime, Vector4 color) :
	_pos(pos), _vel(vel), _acc(acc), _maxDis(maxDis), _maxTime(maxTime)
	{
		PxSphereGeometry geo(1);
		PxShape* shape = CreateShape(geo);
		_color = color;
		_pose = new physx::PxTransform(_pos);
		_renderItem = new RenderItem(shape, _pose, _color);
		RegisterRenderItem(_renderItem);
		_damping = 0.99;
	}
	


void Particle::integrate(double t) { // t = tiempo de simulacion 
	_time += t;
	_pos = _pos + _vel * t;
	_vel = _vel * pow(_damping, t) + _acc * t;
	_pose->p = physx::PxVec3(_pos);
}

bool Particle::checkDeath()
{
	if (_time > _maxTime) return true;
	return false;
}
