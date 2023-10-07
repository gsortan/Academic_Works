#include "Path.h"

Path::Path()
{
	_deltaT = 0;
	_currentPoint = 0;
	_speed = 0.01;
	_type = NG_CAT_MUL_ROM;
	_isInfinite = false;
	_isActive = false;
}

Path::~Path()
{
	
}

void Path::addNewPoint(Vector3f point)
{
	_points.push_back(point);
}

void Path::clearPath() //Resets path
{
	_points.clear();
	_deltaT = 0;
	_currentPoint = 0;
}

void Path::setInfinite(bool state)
{
	_isInfinite = state;
}

void Path::setActive(bool state)
{
	_isActive = state;
}

void Path::setType(unsigned int type)
{
	_type = type;
}

void Path::setSpeed(float speed)
{
	_speed = speed;
}

std::vector<Vector3f>* Path::getPoints()
{
	return &_points;
}

bool Path::getInfinite()
{
	return _isInfinite;
}

bool Path::getActive()
{
	return _isActive;
}

unsigned int Path::getType()
{
	return _type;
}

float Path::getSpeed()
{
	return _speed;
}

unsigned int Path::getCurrentPoint()
{
	return _currentPoint;
}

unsigned int Path::getNumPoints()
{
	return _points.size();
}

Vector3f Path::calcCMR()
{
	if (_points.size() >= 4) //Runs only if there are at least four points
	{
		if (_isInfinite)
		{
			updatePoints();			
		}
		else
		{
			if (_currentPoint + 3 < _points.size()) //Make sure that you are still in range
			{
				_activePointIndex[0] = _currentPoint;
				_activePointIndex[1] = _currentPoint + 1;
				_activePointIndex[2] = _currentPoint + 2;
				_activePointIndex[3] = _currentPoint + 3;
			}
			else
			{
				_isActive = false;
				return Vector3f(0.0f, 0.0f, 0.0f);				
			}
		}

		Vector3f result;

		result.setX(0.5 * ((2 * (_points[_activePointIndex[1]].getX())) //Catmulrom calculations are Catmulrom
					+ ((-_points[_activePointIndex[0]].getX() + _points[_activePointIndex[2]].getX()) * _deltaT)
					+ ((2 * _points[_activePointIndex[0]].getX() - 5 * _points[_activePointIndex[1]].getX() + 4 * _points[_activePointIndex[2]].getX() - _points[_activePointIndex[3]].getX()) * _deltaT * _deltaT)
					+ ((-_points[_activePointIndex[0]].getX() + 3 * _points[_activePointIndex[1]].getX() - 3 * _points[_activePointIndex[2]].getX() + _points[_activePointIndex[3]].getX()) * _deltaT * _deltaT * _deltaT)));

		result.setY(0.5 * ((2 * (_points[_activePointIndex[1]].getY())) //Remember that we are using 1, 2, 3, 4 instead of 0, 1, 2, 3
					+ ((-_points[_activePointIndex[0]].getY() + _points[_activePointIndex[2]].getY()) * _deltaT)
					+ ((2 * _points[_activePointIndex[0]].getY() - 5 * _points[_activePointIndex[1]].getY() + 4 * _points[_activePointIndex[2]].getY() - _points[_activePointIndex[3]].getY()) * _deltaT * _deltaT)
					+ ((-_points[_activePointIndex[0]].getY() + 3 * _points[_activePointIndex[1]].getY() - 3 * _points[_activePointIndex[2]].getY() + _points[_activePointIndex[3]].getY()) * _deltaT * _deltaT * _deltaT)));

		result.setZ(0.5 * ((2 * (_points[_activePointIndex[1]].getZ()))
					+ ((-_points[_activePointIndex[0]].getZ() + _points[_activePointIndex[2]].getZ()) * _deltaT)
					+ ((2 * _points[_activePointIndex[0]].getZ() - 5 * _points[_activePointIndex[1]].getZ() + 4 * _points[_activePointIndex[2]].getZ() - _points[_activePointIndex[3]].getZ()) * _deltaT * _deltaT)
					+ ((-_points[_activePointIndex[0]].getZ() + 3 * _points[_activePointIndex[1]].getZ() - 3 * _points[_activePointIndex[2]].getZ() + _points[_activePointIndex[3]].getZ()) * _deltaT * _deltaT * _deltaT)));

		if (_deltaT >= 1)
		{
			_deltaT = 0;
			++_currentPoint;
		}

		return result;
	}	
	else
	{
		std::cerr << "ERROR: CMR vector does not have enough points." << std::endl;
		return Vector3f(0.0f, 0.0f, 0.0f);
	}
}

void Path::updatePoints() //Checks if your current point is out of range. If it is, move it to the beginning
{
	if (_type == NG_CAT_MUL_ROM)
	{
		if (_currentPoint < _points.size()) //If the current point is not the last point
		{
			_activePointIndex[0] = _currentPoint;
		}
		else //If it is the last point
		{
			_currentPoint = 0; //Move it to the start
			_activePointIndex[0] = _currentPoint;
		}

		for (unsigned int i = 0; i < 3; ++i)
		{
			if (_activePointIndex[i] + 1 < _points.size()) //If the current point is not the last point
			{
				_activePointIndex[i + 1] = _activePointIndex[i] + 1;
			}
			else //If it is the last point
			{
				_activePointIndex[i + 1] = 0; //Move it to the start
			}
		}
	}
}

Vector3f Path::update() //Returns a vector which can be used to manipulate things
{
	_deltaT += _speed;

	if (_type == NG_CAT_MUL_ROM)
	{
		return calcCMR();
	}
	else
	{
		std::cerr << "ERROR: Incorrect path type specified." << std::endl;
		return Vector3f(0.0f, 0.0f, 0.0f);
	}
}