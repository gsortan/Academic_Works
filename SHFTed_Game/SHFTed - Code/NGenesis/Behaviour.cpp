
#include "Vector3f.h"
#include <ctime>

#include "Behaviour.h"


Behaviour::Behaviour(void)
{
}


Behaviour::~Behaviour(void)
{
}

void Behaviour::apply(Enemy* enemy)
{
}


seekBehaviour::seekBehaviour()
{
	weightFactor = 1;
}

seekBehaviour::~seekBehaviour()
{
}


void seekBehaviour::apply(Enemy* enemy)
{
	direction = currentLevel ->getCharacter() ->getPosition() - enemy ->getPosition();
	
	direction.setY(0.0f); 
	direction.normalize();

	Vector3f tempVel = direction * enemy ->getSpeed();

	enemy ->setVelocity(tempVel);
}


arriveBehaviour::arriveBehaviour()
{
	arriveRadius = 5.0f;
	maxSpeed = 10.0f;
	speed = 0.0f;
	weightFactor = 1.0f;
}

arriveBehaviour::~arriveBehaviour()
{
}

void arriveBehaviour::apply(Enemy* enemy)
{

	Vector3f desiredVelocity(0.0f, 0.0f, 0.0f);
	vectorTarget = currentLevel ->getCharacter() ->getPosition() - enemy ->getPosition();
	distance = vectorTarget.calcMagnitude();
	
	if (distance > 0)
	{
		speed = maxSpeed * (distance / arriveRadius);
		speed = min(speed, maxSpeed);
		desiredVelocity = vectorTarget * (speed / distance);

		enemy ->setVelocity(desiredVelocity - enemy ->getVelocity());		
		enemy ->setVelocity(enemy ->getVelocity() * weightFactor);
	}
	else 
	{
		enemy ->setVelocity(Vector3f(0.0f, 0.0f, 0.0f));
	}
}

fleeBehaviour::fleeBehaviour()
{
	weightFactor = 1;
}

fleeBehaviour::~fleeBehaviour()
{
}

void fleeBehaviour::apply(Enemy* enemy)
{
	direction = enemy ->getPosition().subtract(currentLevel ->getCharacter() ->getPosition());
	direction.normalize();

	enemy ->setVelocity(direction * enemy ->getSpeed());
	enemy ->setVelocity(enemy ->getVelocity() * weightFactor);
}

wanderBehaviour::wanderBehaviour()
{
	weightFactor = 1;
	wanderTarget.set(0.0f, 0.0f, 0.0f);
	wanderDelay = 0;
}

wanderBehaviour::~wanderBehaviour()
{
}

void wanderBehaviour::apply(Enemy* enemy)
{
	Vector3f direction;
	
	++wanderDelay;

	if (wanderDelay >= 100 || wanderDelay == 1)
	{
		randomNum = rand() % 90 - 45;
	
		enemy ->setRotate(enemy ->getRotate().add(Vector3f(0.0f, randomNum, 0.0f)));
		angle = mDegToRad(enemy ->getRotate().getY());
		direction.set(sin(angle), 0, cos(angle));

		enemy ->setVelocity(direction * enemy ->getSpeed());
	}

	if (wanderDelay > 101) //Reset Delay
	{
		wanderDelay = 0;
	}
	
}

face::face()
{
	targetDirection.set(0.0f, 0.0f, 0.0f);
}

face::~face()
{
}

void face::apply(Enemy* enemy)
{
	float theta = 0;

	targetDirection = currentLevel ->getCharacter() ->getPosition() - enemy ->getPosition();
	angleCheck = targetDirection.dot(enemy ->getVelocity());

	if (angleCheck < 0.5 && angleCheck > -0.5) //If too close
	{
		
	}
	else
	{
		theta = mRadToDeg(atan(targetDirection.getX() / targetDirection.getZ())); //TOA in SOH CAH TOA. Also radians

		if (enemy ->getVelocity().getZ() < 0) //TOA only deals with one side of the circle, we need to force the other side
		{
			theta += 180;
		}

		enemy ->setRotate(Vector3f(enemy ->getRotate().getX(), theta, enemy ->getRotate().getZ()));
	}
}

cohesion::cohesion()
{
	weightFactor = 1;
}

cohesion::~cohesion()
{

}

void cohesion::apply(Enemy* enemy)
{

}

seperation::seperation()
{
	weightFactor = 1;
}

seperation::~seperation()
{
}

void seperation::apply(Enemy* enemy)
{
	
}

alignment::alignment()
{
}

alignment::~alignment()
{
}

void alignment::apply(Enemy* enemy)
{
	
}

pursue::pursue()
{
	distanceLength.set(0.0f, 0.0f, 0.0f);
	weightFactor = 1;
}

pursue::~pursue()
{
}

void pursue::apply(Enemy* enemy)
{

	distanceLength = currentLevel ->getCharacter() ->getPosition() - enemy ->getPosition();
	distance = distanceLength.calcMagnitude();

	T = distance / currentLevel ->getCharacter() ->getSpeed(); //Should be players maxspeed
	targetPosition = currentLevel ->getCharacter() ->getPosition() + (currentLevel ->getCharacter() ->getVelocity() * T);
	pursueDirection = targetPosition - enemy ->getPosition(); 
	enemy ->setVelocity(pursueDirection * enemy ->getSpeed());
}

evade::evade()
{
	distanceLength.set(0.0f, 0.0f, 0.0f);
	weightFactor = 1;
}

evade::~evade()
{
}

void evade::apply(Enemy* enemy)
{

	distanceLength = currentLevel ->getCharacter() ->getPosition() - enemy ->getPosition();
	distance = distanceLength.calcMagnitude();

	T = distance / currentLevel ->getCharacter() ->getSpeed(); //Should be players maxspeed
	targetPosition = currentLevel ->getCharacter() ->getPosition() + (currentLevel ->getCharacter() ->getVelocity() * T);
	evadeDirection = targetPosition - enemy ->getPosition(); 
	evadeDirection *= -1;

	enemy ->setVelocity(evadeDirection * enemy ->getSpeed());
}

obstacleAvoidance::obstacleAvoidance()
{
	weightFactor = 1.0f;
}

obstacleAvoidance::~obstacleAvoidance()
{
}

void obstacleAvoidance::apply(Enemy* enemy)
{
	
}

//Pathfollowing behaviour with speed control 
pathFollowing::pathFollowing()
{
	index = 0;
	currentGoal = 0;
	arcIndex = 0;
	distanceAhead = 0.0f;
}

pathFollowing::~pathFollowing()
{
}

void pathFollowing::fillTableUp()
{
	//Fills table up using LERP values

	for (float t = 0; t < 1; t += 0.001)
	{
		lookupTable[index] = LERP(t);
		++index;
	}

	for (int i = 0; i < index; ++i)
	{
		if (i == 0)
		{
			tempArcLength = lookupTable[i + 1] - lookupTable[i];
			arcLengthList[arcIndex] = tempArcLength.calcMagnitude();
		}
		else if(i >= 1)
		{
			tempArcLength = lookupTable[i + 1] - lookupTable[i];
			storedArcLength = tempArcLength.calcMagnitude();
			storedArcLength+=arcLengthList[arcIndex];

			++arcIndex;
			arcLengthList[arcIndex] = storedArcLength;
		}
	}
}

Vector3f pathFollowing::LERP(float t)
{

	Vector3f lerpedVec;
	rightSide = goals[currentGoal] * (1 - t);
	lHs = (goals[currentGoal + 1] * t);
	lerpedVec = rightSide + lHs;

	return lerpedVec;
}

Vector3f pathFollowing::catmullrom(float t)
{
	Vector3f point;
	Vector3f p0 = goals[currentGoal];
	Vector3f p1 = goals[currentGoal + 1];
	Vector3f p2 = goals[currentGoal + 2];
	Vector3f p3 = goals[currentGoal + 3];

	float x = 0.5 * (p1.getX() * 2) + (-p0.getX() + p2.getX()) * t + (2 * p0.getX() - 5 * p1.getX() + 4 * p2.getX() -p3.getX()) * (t * t) + (-p0.getX() + 3 * p1.getX() - 3 * p2.getX() + p3.getX()) * (t * t * t);
	float y = 0.5 * (p1.getY() * 2) + (-p0.getY() + p2.getY()) * t + (2 * p0.getY() - 5 * p1.getY() + 4 * p2.getY() -p3.getY()) * (t * t) + (-p0.getY() + 3 * p1.getY() - 3 * p2.getY() + p3.getY()) * (t * t * t);
	float z = 0.5 * (p1.getZ() * 2) + (-p0.getZ() + p2.getZ()) * t + (2 * p0.getZ() - 5 * p1.getZ() + 4 * p2.getZ() -p3.getZ()) * (t * t) + (-p0.getZ() + 3 * p1.getZ() - 3 * p2.getZ() + p3.getZ()) * (t * t * t);
	
	point.set(x, y, z);

	return point;
}

void pathFollowing::reparameratize( )
{
	//Figures out u time value along the curve of where I should be
	//Plug u into interpolation equation to get correct interpolated point for a particular velocity
	float f;

	for(int i = 0; i < index; ++i)
	{
		if(distanceAhead > arcLengthList[i] && distanceAhead < arcLengthList[i + 1])
		{
			f = (distanceAhead - arcLengthList[i]) / (arcLengthList[i+1] - arcLengthList[i]);
			u = ((1 - f) * (i * 0.001)) + ((i * 0.001) * f);//0.001 used because of 1000 sample values
		}
	}
}

void pathFollowing::apply(Enemy* enemy)
{
	predictedPoint = enemy ->getPosition() + enemy ->getVelocity();
	distanceAhead = predictedPoint.calcMagnitude();
	
	reparameratize();

	//Uses lerp interpolation with parameratized u value
	first = goals[currentGoal] * (1 - u);

	interpolatedPoint = first + (goals[currentGoal + 1] * u);

	directionToPoint = interpolatedPoint - enemy ->getPosition();

	pathRange = predictedPoint - interpolatedPoint;

	pathRadius = pathRange.calcMagnitude();

	if (pathRadius < 10)
	{
		currentGoal = (currentGoal + 1) % 3;
		index = 0;
		arcIndex = 0;
		fillTableUp();
		reparameratize();
	}

	directionToPoint.normalize();

	enemy ->setVelocity(directionToPoint * enemy ->getSpeed());
}

Paths::Paths(const char * path)
{
	loadPath(path);
	fillTableUp();
	distanceAhead = 0;
	reparameratize();
}


Paths::~Paths(void)
{
}

void Paths::loadPath(const char * path)
{
	char header[128];
	std::string currentLine;
	FILE * file2 = fopen(path, "r");
	float x = 0;
	float y = 0;
	float z = 0;
	int i = 0;

	if (file2 != NULL)
	{
		while (fgets(header, sizeof(header), file2) != NULL)
		{
			if (sscanf(header, "( %f, %f, %f )", &x, &y, &z) != NULL)
			{
				goals[i] = Vector3f(x, y, z);
				++i;
			}
		}
	}
}

int start = 0;
int last = 1000;

mySecondBehaviour::mySecondBehaviour()
{
}

mySecondBehaviour::~mySecondBehaviour()
{
}