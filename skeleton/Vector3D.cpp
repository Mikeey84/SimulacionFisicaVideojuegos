#pragma once
#include <vector>
#include <algorithm>
template<typename T>

class Vector3D {
public:
	// Poner ejex(x,y,z)
	// Poner ejey(x,y,z)
	// Poner ejez(x,y,z)
	T _ejeX, _ejeY, _ejeZ, _x, _y, _z;
	Vector3D(T x, T y, T z) : _x(x), _y(y), _z(z) {
		_ejeX = _ejeY = _ejeZ = (_x, _y, _z);
	};

	T modulo() {
		return sqrt(pow(this._x,2) + pow(this._y, 2) + pow(this._x, 2))
	}
	Vector3D normalize() {
		T aux = modulo(this);
		return Vector3D(v._x / aux, v._y / aux, v._z / aux);
	}

	//add & sub
	Vector3D operator+(const Vector3D& v) {
		return Vector3D(_x + v._x, _y+ v._y, _z + v._z);
	}
	Vector3D operator-(const Vector3D& v) {
		return Vector3D(_x - v._x, _y - v._y, _z - v._z);
	}
	

	// scalar mult
	Vector3D operator*(const T& v)
	{
		return Vector3D(_x * v, _y * v, _z * v);
	}
	float dot(const Vector3D& v) {
		return _x * v._x + _y * v._y + _z * v._z;
	}
	Vector3D operator*(const Vector3D& v) {
		return Vector3D((_y * v._z - _z * v._y), (_z * v._x - v._z * -_x), _x * v._y - v._x - _y);
	}
	void operator=(const Vector3D& v) {
		_x = v._x;
		_y = v._y;
		_z = v._z;
	}
};