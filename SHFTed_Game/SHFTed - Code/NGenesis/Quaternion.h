#pragma once

#include "Vector3f.h"
#include "Conversion.h"

#define NG_X 0
#define NG_Y 1
#define NG_Z 2

//class Conversion;

class Quaternion
{
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float scalar, Vector3f vector);
	Quaternion(Vector3f vector);
	~Quaternion();

	Quaternion createRotation(float angle, unsigned int axis);

	float getW();
	float getX();
	float getY();
	float getZ();

	void setW(float value);
	void setX(float value);
	void setY(float value);
	void setZ(float value);

	void setVector(Vector3f &vector);
	Vector3f getVector();
	Quaternion getInverse();

	Quaternion add(Quaternion &otherQuat);
	Quaternion subtract(Quaternion &otherQuat);
	Quaternion multiply(Quaternion &otherQuat);
	Quaternion multiply(float scalar);
	Quaternion divide(float scalar);
	
	Quaternion rotate(float angle, unsigned int axis);
	Quaternion createRotationQ(float angle, unsigned int axis);
	float dot(Quaternion &otherQuat);
	Quaternion slerp(float angle, Quaternion &otherQuat, float t);

	void normalize();
	void clean();

	float calculateMagnitude();
	Quaternion calculateConjugate(); //Also inverse

	void print();

private:
	float _w, _x, _y, _z;
};