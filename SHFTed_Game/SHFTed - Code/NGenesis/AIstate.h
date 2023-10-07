#pragma once

#include "Vector3f.h"
#include "Game.h"

class Behaviour;

class AIstate
{
public:

	AIstate(void);
	~AIstate(void);

	//List of behaviours that AI state class will possess also possibly pass level pointer in behaviour constructer so they all inherit that
	Behaviour *seek;
	Behaviour *pursueB;
	Behaviour *wander;
	Behaviour *cohesionB;
	Behaviour *seperationB; 
	Behaviour *flee;
	Behaviour *obstacleAvoidanceB; 
	Behaviour *faceB;
	Game *currentLevel;

	void init(Game* theLevel) //Create current game instance and make everything available to current AI state
	{
		currentLevel = theLevel;
		initBehaviours();
	}

	void initBehaviours();
	virtual void stateUpdate();//Virtual function for update

	unsigned int aggroRange;
};


class melee : public AIstate
{
public :
	melee();
	~melee();

	virtual void stateUpdate(Enemy *enemy);

protected:
	Vector3f distanceCheck;
	float totalDistance; 
};


class ranged : public AIstate
{
public :
	ranged();
	~ranged();

	virtual void stateUpdate(Enemy *enemy);

protected:
	Vector3f distanceCheck;
	float totalDistance; 
};

class mobPattern : public AIstate
{
public:
	mobPattern();
	~mobPattern();

	virtual void stateUpdate(Enemy *enemy);

protected:
	Vector3f radius;
	float maxDistance;
	float maxSpeed;
};
