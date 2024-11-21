#include "ExplosionGenerator.h"
#include "ParticleSystem.h"

ExplosionGenerator::ExplosionGenerator(ParticleSystem* pS, Vector3 pos, Vector3 area, float k, double t, double tau) : ForceGenerator(pS, pos, area), _pS(pS),
_k(k), _t(t), _tau(tau) {
}

void ExplosionGenerator::update(double t, Particle* p) {
    if (!_explosion) return;

    double factor_tiempo = exp(-_t / _tau);

    
    Vector3 posParticula = p->_pos;
           
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
        p->addForce(_force);
    
    
    _t += t;
   
}
