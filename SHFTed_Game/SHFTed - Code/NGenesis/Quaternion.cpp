#include "Quaternion.h"

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	_w = w;
	_x = x;
	_y = y;
	_z = z;	
}

Quaternion::Quaternion(float scalar, Vector3f vector)
{
	_w = scalar;
	_x = vector.getX();
	_y = vector.getY();
	_z = vector.getZ();
}

Quaternion::Quaternion(Vector3f vector)
{
	_w = 0;
	_x = vector.getX();
	_y = vector.getY();
	_z = vector.getZ();
}

Quaternion::~Quaternion()
{
}

Quaternion Quaternion::createRotation(float angle, unsigned int axis)
{
	Quaternion result;

	float cosAmount = cos(mDegToRad(angle/2));
	float sinAmount = sin(mDegToRad(angle/2));

	Vector3f rotateAxis;

	if (axis == NG_X)
	{
		rotateAxis.set(1.0f, 0.0f, 0.0f);
	}
	else if (axis == NG_Y)
	{
		rotateAxis.set(0.0f, 1.0f, 0.0f);
	}
	else
	{
		rotateAxis.set(0.0f, 0.0f, 1.0f);
	}

	rotateAxis = rotateAxis.scalarMultiply(sinAmount);
	rotateAxis.normalize();
	
	_w = cosAmount;
	_x = rotateAxis.getX();
	_y = rotateAxis.getY();
	_z = rotateAxis.getZ();

	return *this;
}

float Quaternion::getW()
{
	return _w;
}

float Quaternion::getX()
{
	return _x;
}

float Quaternion::getY()
{
	return _y;
}

float Quaternion::getZ()
{
	return _z;
}

void Quaternion::setW(float value)
{
	_w = value;
}

void Quaternion::setX(float value)
{
	_x = value;
}

void Quaternion::setY(float value)
{
	_y = value;
}

void Quaternion::setZ(float value)
{
	_z = value;
}

void Quaternion::setVector(Vector3f &vector)
{
	_w = 0.0f;
	_x = vector.getX();
	_y = vector.getY();
	_z = vector.getZ();
}

Vector3f Quaternion::getVector()
{
	Vector3f result = Vector3f(_x, _y, _z);

	return result;
}

Quaternion Quaternion::getInverse()
{
	Quaternion result = *this;

	result.setVector(result.getVector().scalarMultiply(-1));

	return result;
}

Quaternion Quaternion::add(Quaternion &otherQuat)
{
	Quaternion result = Quaternion(_w + otherQuat.getW(), _x + otherQuat.getX(), _y + otherQuat.getY(), _z + otherQuat.getZ());

	return result;
}

Quaternion Quaternion::subtract(Quaternion &otherQuat)
{
	Quaternion result = Quaternion(_w - otherQuat.getW(), _x - otherQuat.getX(), _y - otherQuat.getY(), _z - otherQuat.getZ());

	return result;
}

Quaternion Quaternion::multiply(Quaternion &otherQuat)
{
	Quaternion result;

	result.setW(_w * otherQuat.getW() - _x * otherQuat.getX() - _y * otherQuat.getY() - _z * otherQuat.getZ());
	result.setX(_w * otherQuat.getX() + _x * otherQuat.getW() + _y * otherQuat.getZ() - _z * otherQuat.getY());
	result.setY(_w * otherQuat.getY() - _x * otherQuat.getZ() + _y * otherQuat.getW() + _z * otherQuat.getX());
	result.setZ(_w * otherQuat.getZ() + _x * otherQuat.getY() - _y * otherQuat.getX() + _z * otherQuat.getW());

	return result;
}

Quaternion Quaternion::multiply(float scalar)
{
	Quaternion result;

	result.setW(_w * scalar);
	result.setX(_x * scalar);
	result.setY(_y * scalar);
	result.setZ(_z * scalar);

	return result;
}

Quaternion Quaternion::divide(float scalar)
{
	Quaternion result = Quaternion(_w / scalar, _x / scalar, _y / scalar, _z / scalar);

	return result;
}

Quaternion Quaternion::rotate(float angle, unsigned int axis)
{
	Quaternion result;

	float cosAmount = cos(mDegToRad(angle / 2));
	float sinAmount = cos(mDegToRad(angle / 2));

	Vector3f rotateAxis;

	if (axis == NG_X)
	{
		rotateAxis = Vector3f(1, 0, 0);
	}
	else if (axis == NG_Y)
	{
		rotateAxis = Vector3f(0, 1, 0);
	}
	else
	{
		rotateAxis = Vector3f(0, 0, 1);
	}

	Quaternion rotationQuat = Quaternion(cosAmount, rotateAxis.scalarMultiply(sinAmount));
	result = rotationQuat.multiply(*this);
	result = result.multiply(rotationQuat.calculateConjugate());

	return result;
}

//Creates rotation quaternions 
Quaternion Quaternion::createRotationQ(float angle, unsigned int axis)
{
	Quaternion result;

	float cosAmount = cos(mDegToRad(angle / 2));
	float sinAmount = sin(mDegToRad(angle / 2));

	Vector3f rotateAxis;

	if (axis == NG_X)
	{
		rotateAxis.set(1.0f, 0.0f, 0.0f);
	}
	else if (axis == NG_Y)
	{
		rotateAxis.set(0.0f, 1.0f, 0.0f);
	}
	else
	{
		rotateAxis.set(0.0f, 0.0f, 1.0f);
	}

	rotateAxis = rotateAxis.scalarMultiply(sinAmount);
	
	_w = cosAmount;
	_x = rotateAxis.getX();
	_y = rotateAxis.getY();
	_z = rotateAxis.getZ();

	return *this;
}

float Quaternion::dot(Quaternion &otherQuat)
{
	float result = _w * otherQuat.getW() + getVector().dot(otherQuat.getVector());

	return result;
}


Quaternion Quaternion::slerp(float angle, Quaternion &otherQuat, float t)
{
	float partOne;
	float partTwo;
	float partThree;

	Quaternion temp(_w, _x, _y, _z);
	Quaternion temp2;
	Quaternion result;

	//If angle between quaternions is small lerp them instead
	if (angle < 1.00001f && angle > 0.99999f)
	{
		temp.multiply(1 - t);
		temp2 = otherQuat.multiply(t);

		result = temp.add(temp2);

		return result;
	}

	temp2 = otherQuat;
	partOne = sin((1 - t) * angle);

	partTwo = sin(angle);
	partThree = sin(t * angle);

	temp = temp.multiply(partOne / partTwo);
	temp2 = temp2.multiply(partThree / partTwo);
    
	result = temp.add(temp2);
	return result; 
}

void Quaternion::normalize()
{
	float magnitude = calculateMagnitude();

	_w /= magnitude;
	_x /= magnitude;
	_y /= magnitude;
	_z /= magnitude;
}

void Quaternion::clean() 
{
	//W
	if (_w >= -0.001 && _w <= 0.001)
	{
		_w = 0.0f;
	}
	else if (_w >= 0.999 && _w <= 1.001)
	{
		_w = 1.0f;
	}
	else if (_w <= -0.999 && _w >= -1.001)
	{
		_w = -1.0f;
	}

	//X
	if (_x >= -0.001 && _x <= 0.001)
	{
		_x = 0.0f;
	}
	else if (_x >= 0.999 && _x <= 1.001)
	{
		_x = 1.0f;
	}
	else if (_x <= -0.999 && _x >= -1.001)
	{
		_x = -1.0f;
	}

	//Y
	if (_y >= -0.001 && _y <= 0.001)
	{
		_y = 0.0f;
	}
	else if (_w >= 0.999 && _y <= 1.001)
	{
		_y = 1.0f;
	}
	else if (_y <= -0.999 && _y >= -1.001)
	{
		_y = -1.0f;
	}

	//Z
	if (_z >= -0.001 && _z <= 0.001)
	{
		_z = 0.0f;
	}
	else if (_z >= 0.999 && _z <= 1.001)
	{
		_z = 1.0f;
	}
	else if (_z <= -0.999 && _z >= -1.001)
	{
		_z = -1.0f;
	}
}

float Quaternion::calculateMagnitude()
{
	float result = sqrt(_w * _w + _x * _x + _y * _y + _z * _z);

	return result;
}

Quaternion Quaternion::calculateConjugate()
{
	Quaternion result = Quaternion(_w, -_x, -_y, -_z);

	return result;
}

void Quaternion::print()
{
	std::cout << _w << ", " << _x << ", " << _y << ", " << _z << std::endl;
}