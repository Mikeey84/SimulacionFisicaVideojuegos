#include "Particle.h"

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 acc) : _vel(vel), _pos(pos), _acc(acc) {
	
	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);

	_pose = new physx::PxTransform(_pos);

	_renderItem = new RenderItem(shape, _pose, Vector4{ 1,0.5,1,1 });
	RegisterRenderItem(_renderItem);
	_damping = 0.99;
}

void Particle::integrate(double t) { // t = tiempo de simulacion 
	_pos = _pos + _vel * t;
	_vel = _vel * pow(_damping, t) + _acc * t;
	_pose->p = physx::PxVec3(_pos);
}
