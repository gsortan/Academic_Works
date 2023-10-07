#pragma once

#include <iostream>

class Conversion;

class Vector3f
{
public:
	Vector3f();
	Vector3f(float newX, float newY, float newZ);
	~Vector3f();

	inline float getX();
	inline float getY();
	inline float getZ();


	inline void set(float x, float y, float z);
	inline void setX(float newX);
	inline void setY(float newY);
	inline void setZ(float newZ);

	void print();

	inline float calcMagnitude();
	inline float calcDistance(Vector3f &otherVec);
	Vector3f calcAngle(Vector3f &otherVec);	//Not inline because it uses a macro
	inline Vector3f calcProjection(Vector3f &otherVec);
	inline float calcProjectionLength(Vector3f &otherVec);

	inline void normalize();

	inline Vector3f subtract(Vector3f &otherVec);
	inline Vector3f add(Vector3f &otherVec);
	inline Vector3f multiply(Vector3f &otherVec);
	inline Vector3f scalarMultiply(float num);
	
	inline Vector3f& operator +=(Vector3f otherVec);
	inline Vector3f& operator -=(Vector3f otherVec);
	inline Vector3f& operator *=(float scalar);

	inline const Vector3f& operator =(Vector3f otherVec);
	inline const Vector3f& operator +(Vector3f otherVec);
	inline const Vector3f& operator -(Vector3f otherVec);
	inline const Vector3f& operator *(float scalar);

	inline float dot(Vector3f &otherVec);
	inline Vector3f cross(Vector3f &otherVec);

	inline Vector3f lerp(Vector3f &otherVec, float &t);

	inline void print();

protected:
	float _x, _y, _z;
};

#include "Vector3f.inl"