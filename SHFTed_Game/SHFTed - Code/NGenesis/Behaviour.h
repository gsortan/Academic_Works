#pragma once

#include "Conversion.h"
#include "Game.h"

class Behaviour
{
public:
	Behaviour(void);
	~Behaviour(void);

	void init(Game* theLevel) //Create current game instance and make everything available to behaviour
	{
		currentLevel = theLevel;
	}

	float weightFactor;
	Game *currentLevel;
	
	virtual void apply(Enemy* enemy);

};

class seekBehaviour : public Behaviour
{
public :
	seekBehaviour();
	~seekBehaviour();

	virtual void apply(Enemy* enemy);

protected:
	float radius;
	float distance;
	Vector3f direction;

};

class arriveBehaviour : public Behaviour
{
public:
	arriveBehaviour();
	~arriveBehaviour();

	virtual void apply(Enemy* enemy);

protected:
	float distance;
	float speed;
	Vector3f direction;
	Vector3f vectorTarget;
	float arriveRadius;
	float maxSpeed;
};

class fleeBehaviour : public Behaviour
{
public:
	fleeBehaviour();
	~fleeBehaviour();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f direction;
};

class wanderBehaviour : public Behaviour
{
public:
	wanderBehaviour();
	~wanderBehaviour();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f wanderTarget;
	float wanderDelay;
	float randomNum;
	float angle;
};

class face : public Behaviour
{
public:
	face();
	~face();
;
	virtual void apply(Enemy* enemy);

protected:
	Vector3f forwardVec;
	Vector3f rotAxis;
	Vector3f targetDirection;
	float rotAngle;
	float angleCheck; 
};

class cohesion : public Behaviour
{
public:
	cohesion();
	~cohesion();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f center;
	Vector3f groupVec;
	Vector3f averagePosition;
	float cohesionDistance;
};


class seperation : public Behaviour
{
public:
	seperation();
	~seperation();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f tempDirection; 
	Vector3f averageDirection;
	Vector3f separationForce;
	float distance;
};

class alignment : public Behaviour
{
public:
	alignment();
	~alignment();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f averageDirection;
	Vector3f distanceCheck;
	Vector3f direction;
	Vector3f position;
	float alignmentDistance; 
	
};

class obstacleAvoidance : public Behaviour
{

public:
	obstacleAvoidance();
	~obstacleAvoidance();

	virtual void apply(Enemy* enemy);

protected:
	Vector3f distanceCheck;
	Vector3f forwardVector;
	Vector3f diff;
	Vector3f ray;
	Vector3f rayTouchVec; 
	Vector3f projection; 
	Vector3f force;

	float length;
	float dotProduct;
	float checkLength; 
	float dist; 
	float circleRadius;
	float width;
};

class pursue : public Behaviour
{
public:
	pursue();
	~pursue();

	virtual void apply(Enemy* enemy);

protected:
	float T;
	float distance;
	Vector3f distanceLength;
	Vector3f targetPosition;
	Vector3f pursueDirection; 	
};

class evade : public Behaviour
{
public:
	evade();
	~evade();

	virtual void apply(Enemy* enemy);

protected:
	float T;
	float distance;
	Vector3f distanceLength;
	Vector3f targetPosition;
	Vector3f evadeDirection; 	
};

class pathFollowing : public Behaviour
{
public:
	pathFollowing();
	~pathFollowing();

	virtual void apply(Enemy* enemy);

	void fillTableUp();
	void reparameratize();
	Vector3f LERP(float t);
	Vector3f catmullrom(float t);

protected:
	Vector3f goals[4];
	Vector3f lookupTable[2000];
	Vector3f directionToPoint;
	Vector3f interpolatedPoint;
	Vector3f predictedPoint;
	Vector3f pathRange;

	Vector3f first;
	Vector3f startPos;
	Vector3f rightSide;
	Vector3f lHs;
	Vector3f tempArcLength;

	float distanceAhead;
	float distance; 
	float distanceToPoint;
	float pathRadius;
	float u;
	float storedArcLength;

	float arcLengthList[1000];
	float distanceTable[2000];

	int currentGoal;
	int index;
	int arcIndex;
};

class Paths : public pathFollowing
{
public:
	Paths(const char * path);
	~Paths(void);
	void loadPath(const char * file);
	
	void createPath();
	
	std::vector<Paths*> activePath; 
	Paths *path1;
	Paths *path2;
	Paths *path3;
	Paths *path4;

	int arcIndex;
	Vector3f rHs;
};


class mySecondBehaviour : public seekBehaviour 
{
public:	
	 mySecondBehaviour();
	~ mySecondBehaviour();
};
