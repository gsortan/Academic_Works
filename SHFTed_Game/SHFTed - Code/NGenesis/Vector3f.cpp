#include <math.h>
#include "Vector3f.h"
#include "Conversion.h"

Vector3f::Vector3f()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3f::Vector3f(float newX, float newY, float newZ)
{
	_x = newX;
	_y = newY;
	_z = newZ;
}

Vector3f::~Vector3f()
{

}

Vector3f Vector3f::calcAngle(Vector3f &otherVec) //Needs work
{
	Vector3f temp1 = *this; //Needed due to normalize
	Vector3f temp2 = otherVec;

	temp1.normalize();
	temp2.normalize();

	float angle = mRadToDeg(acos(temp1.dot(temp2)));
	Vector3f axis = temp1.cross(temp2);
	axis.normalize();	

	Vector3f result = axis.scalarMultiply(angle);

	return result;
}

/*Vector3f Vector3f::calcProjection(Vector3f &otherVec)
{
	return otherVec.scalarMultiply(this ->dot(otherVec) / otherVec.calcMagnitude() * otherVec.calcMagnitude());
}

float Vector3f::calcProjectionLength(Vector3f &otherVec)
{
	return this ->subtract(otherVec.scalarMultiply(this ->dot(otherVec) / (otherVec.calcMagnitude() * otherVec.calcMagnitude()))).calcMagnitude();
}

void Vector3f::normalize()
{
	if (calcMagnitude() != 0)
	{
		float normalizationFactor = 1 / calcMagnitude();

		//this ->scalarMultiply(normalizationFactor);

		_x *= normalizationFactor;
		_y *= normalizationFactor;
		_z *= normalizationFactor;
	}
}

Vector3f Vector3f::subtract(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x - otherVec.getX(), _y - otherVec.getY(), _z - otherVec.getZ());

	return result;
}

Vector3f Vector3f::add(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x + otherVec.getX(), _y + otherVec.getY(), _z + otherVec.getZ());

	return result;
}

Vector3f Vector3f::multiply(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_x * otherVec.getX(), _y * otherVec.getY(), _z * otherVec.getZ());

	return result;
}

Vector3f Vector3f::scalarMultiply(float num)
{
	Vector3f result = Vector3f(_x * num, _y * num, _z * num);

	return result;
}

Vector3f& Vector3f::operator +=(Vector3f otherVec)
{
	_x += otherVec.getX();
	_y += otherVec.getY();
	_z += otherVec.getZ();

	return *this;
}

Vector3f& Vector3f::operator -=(Vector3f otherVec)
{
	_x -= otherVec.getX();
	_y -= otherVec.getY();
	_z -= otherVec.getZ();

	return *this;
}

Vector3f& Vector3f::operator *=(float scalar)
{
	_x *= scalar;
	_y *= scalar;
	_z *= scalar;

	return *this;
}

const Vector3f& Vector3f::operator =(Vector3f otherVec)
{
	_x = otherVec.getX();
	_y = otherVec.getY();
	_z = otherVec.getZ();

	return *this;
}

const Vector3f& Vector3f::operator +(Vector3f otherVec)
{
	return Vector3f(_x + otherVec.getX(), _y + otherVec.getY(), _z + otherVec.getZ());
}

const Vector3f& Vector3f::operator -(Vector3f otherVec)
{
	return Vector3f(_x - otherVec.getX(), _y - otherVec.getY(), _z - otherVec.getZ());
}

const Vector3f& Vector3f::operator *(float scalar)
{
	return Vector3f(_x * scalar, _y * scalar, _z * scalar);
}

float Vector3f::dot(Vector3f &otherVec)
{
	return (_x * otherVec.getX() + _y * otherVec.getY() + _z * otherVec.getZ());
}

Vector3f Vector3f::cross(Vector3f &otherVec)
{
	Vector3f result = Vector3f(_y * otherVec.getZ() - _z * otherVec.getY(), 
							   _z * otherVec.getX() - _x * otherVec.getZ(), 
							   _x * otherVec.getY() - _y * otherVec.getX());

	return result;
}

Vector3f Vector3f::lerp(Vector3f &otherVec, float &t)
{
	Vector3f result = Vector3f((1 - t) * _x + t * otherVec.getX(),
							   (1 - t) * _y + t * otherVec.getY(),
							   (1 - t) * _z + t * otherVec.getZ());

	return result;
}

void Vector3f::print()
{
	std::cout << _x << ", " << _y << ", " << _z << std::endl;
}*/