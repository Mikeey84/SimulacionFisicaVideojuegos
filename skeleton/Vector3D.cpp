#pragma once
#include <vector>
#include <algorithm>
template<typename T>

class Vector3D {
	
	// Poner ejex(x,y,z)
	// Poner ejey(x,y,z)
	// Poner ejez(x,y,z)
	T _ejeX, _ejeY, _ejeZ;
	Vector3D(T x, T y, T z) : _ejeX(x,y,z), _ejeY(x,y,z), _ejeZ(x,y,z) {};

	T modulo() {
		return sqrt(pow(this._x,2) + pow(this._y, 2) + pow(this._x, 2))
	}

	Vector3D normalize() {
		T aux = modulo(this);
		return Vector3D(v._x / aux, v._y / aux, v._z / aux);
	}
	// scalar mult
	Vector3D operator*(const T& v)
	{
		return Vector3D(x * v, y * v, z * v);
	}
	Vector3D operator*(const Vector3D& v) {
		
	}
};