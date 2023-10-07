#pragma once

#include "Vector3f.h"
#include <vector>

#define NG_CAT_MUL_ROM 0
#define NG_LERP 0

class Path
{
public:
	Path();
	~Path();

	void addNewPoint(Vector3f point);
	void clearPath();
	void setInfinite(bool state);
	void setActive(bool state);
	void setType(unsigned int type);
	void setSpeed(float speed);

	std::vector<Vector3f>* getPoints();
	bool getInfinite();
	bool getActive();
	unsigned int getType();
	float getSpeed();
	unsigned int getCurrentPoint();
	unsigned int getNumPoints();

	Vector3f calcCMR();
	void updatePoints();
	Vector3f update();

private:
	std::vector<Vector3f> _points;
	
	unsigned int _currentPoint;
	unsigned int _type;
	bool _isInfinite;
	bool _isActive;
	float _speed;
	float _deltaT;

	unsigned int _activePointIndex[4]; //The points that are active for the calculations; max of four
};