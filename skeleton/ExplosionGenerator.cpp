#include "ExplosionGenerator.h"
#include "ParticleSystem.h"

ExplosionGenerator::ExplosionGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k, double t, double tau) : ForceGenerator(pS, pos, area), _pS(pS),
_k(k), _t(t), _tau(tau) {
}

void ExplosionGenerator::update(double t) {

    //for (int i = 0; i < _pS->_particles.size(); ++i) {
    //    const Vector3 pPos = _pS->_particles[i]->_pos;
    //    if (checkCircleArea(_pS->_particles[i]->_pos)){

    //        double dx = pPos.x - _pos.x;
    //        double dy = pPos.y - _pos.y;
    //        double dz = pPos.z - _pos.z;
    //        float distance = (pPos - _pos).magnitude(); // Distancia de la particula con respecto al origen

    //        double decay = std::exp(-_t / _tau);

    //        // Calcula la magnitud del campo con la constante K y el decaimiento por r^2

    //        double factor = _k / (_area.x * _area.x) * decay;

    //        _force = {
    //            /*(float)(dx * factor),
    //            (float)(dy * factor),
    //            (float)(dz * factor)*/
    //             (float)(factor * dx * decay),
    //            (float)(factor * dy * decay),
    //             (float)(factor * dz * decay)
    //        };
    //       

    //        _pS->_particles[i]->addForce(_force);
    //    }
    //}
   
    
    //if (!_explosion) return;

    double factor_tiempo = exp(-_t / _tau);

    for (int i = 0; i < _pS->_particles.size(); ++i) { 
        Vector3 posParticula = _pS->_particles[i]->_pos;
        if (checkCircleArea(_pS->_particles[i]->_pos)) {
           
            Vector3 distancia = posParticula - _pos; 
            double r = distancia.magnitude(); 

            double factor_fuerza = (_k / (r * r)) * factor_tiempo;

            Vector3 direccion = {
                distancia.x / distancia.magnitude(),
                distancia.y / distancia.magnitude(),
                distancia.z / distancia.magnitude()
            };

            _force = direccion * factor_fuerza;

            // Aplicar la fuerza a la partícula
            _pS->_particles[i]->addForce(_force);
        }
    }
    _t += t;
}
