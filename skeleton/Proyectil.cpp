#include "Proyectil.h"

Proyectil::Proyectil(PxTransform camera, PxVec3 dir, float  vel, float m, float escalar) : _v(vel), _mR(m) {
	_vR = dir;
	Escalado(escalar);

	// Modificar la masa
	double vr2 = sqrt(pow(_vR.x, 2) + pow(_vR.y, 2) + pow(_vR.z, 2));
	double vs2 = sqrt(pow(_vS.x, 2) + pow(_vS.y, 2) + pow(_vS.z, 2));
	_mS = _mR * vr2 / vs2;

	
	// Modificar la gravedad
	_gS = GRAVEDAD * vs2 / _v;
	_particle = new Particle(camera.p, _vS, PxVec3(0, _gS, 0));
}

void Proyectil::Escalado(float escalar) {
	_vS = _vR * _v / escalar;
}
