#include "AIstate.h"
#include "Behaviour.h"

AIstate::AIstate(void)
{
	seek = new seekBehaviour();
	pursueB = new pursue();
	wander =   new wanderBehaviour();
	cohesionB = new cohesion(); 
	seperationB = new seperation();
	flee = new fleeBehaviour();
	obstacleAvoidanceB = new obstacleAvoidance();
	faceB = new face();

	aggroRange = 300; //Defaults to 300
}


AIstate::~AIstate(void)
{
}


void AIstate::initBehaviours()
{
	seek ->init(currentLevel);
	pursueB ->init(currentLevel);
	wander ->init(currentLevel);
	cohesionB ->init(currentLevel);
	seperationB ->init(currentLevel);
	flee ->init(currentLevel);
	obstacleAvoidanceB ->init(currentLevel);
	faceB ->init(currentLevel);
}

void AIstate::stateUpdate()
{
}

melee::melee() : AIstate()
{
}

melee::~melee()
{
}

void melee::stateUpdate(Enemy *enemy)
{
	if (enemy ->getLeashing() == false)
	{
		distanceCheck = enemy ->getPosition() - currentLevel ->getCharacter() ->getPosition();
		totalDistance = distanceCheck.calcMagnitude();

		if (enemy ->getScale().getX() != 10) //The big guy has a slightly different AI
		{
			if (enemy ->getLowHP() == true)
			{
				flee ->apply(enemy);
				enemy ->setAttacking(false);
				faceB ->apply(enemy);
			}
			else if (totalDistance >= aggroRange)
			{
				wander ->apply(enemy);
				enemy ->setAttacking(false);
			}
			else if (enemy ->getLowHP() == false && totalDistance < aggroRange && totalDistance > enemy ->getMeleeAttackRange())
			{
				seek ->apply(enemy);
				enemy ->setAttacking(false);
				faceB ->apply(enemy);
			}
			else if (totalDistance <= enemy ->getMeleeAttackRange())
			{
				enemy ->setVelocity(Vector3f(0.0f, enemy ->getVelocity().getY(), 0.0f));
				enemy ->setAttacking(true);
				faceB ->apply(enemy);
			}
		}
		else //The big guy doesn't run away. ever.
		{
			if (totalDistance >= aggroRange)
			{
				wander ->apply(enemy);
				enemy ->setAttacking(false);
			}
			else if (totalDistance < aggroRange && totalDistance > enemy ->getMeleeAttackRange())
			{
				seek ->apply(enemy);
				enemy ->setAttacking(false);
				faceB ->apply(enemy);
			}
			else if (totalDistance <= enemy ->getMeleeAttackRange())
			{
				enemy ->setVelocity(Vector3f(0.0f, enemy ->getVelocity().getY(), 0.0f));
				enemy ->setAttacking(true);
				faceB ->apply(enemy);
			}
		}
	}
	else
	{
		distanceCheck.set(enemy ->getSpawnPoint().getX() - enemy ->getPosition().getX(), 
						  0.0f,
						 enemy ->getSpawnPoint().getZ() - enemy ->getPosition().getZ()); 
 
		distanceCheck.normalize();
		enemy ->setVelocity(distanceCheck * enemy ->getSpeed());
	}
}

ranged::ranged() : AIstate()
{
}

ranged::~ranged()
{
}

void ranged::stateUpdate(Enemy *enemy)
{
	if (enemy ->getLeashing() == false)
	{
		distanceCheck = enemy ->getPosition() - currentLevel ->getCharacter() ->getPosition();
		totalDistance = distanceCheck.calcMagnitude();

		if (totalDistance > aggroRange) //If too far away from player
		{
			wander ->apply(enemy);
			enemy ->setAttacking(false);
		}
		else if (totalDistance > aggroRange * 0.8 && totalDistance <= aggroRange) //If close enough to seek
		{
			seek ->apply(enemy);
			faceB ->apply(enemy);
			enemy ->setAttacking(false);
		}
		else if (totalDistance > aggroRange * 0.45 && totalDistance <= aggroRange * 0.8) //If close enough to attack
		{
			enemy ->setVelocity(Vector3f(0.0f, 0.0f, 0.0f));
			enemy ->setRotate(Vector3f(0.0f, mRadToDeg(atan(distanceCheck.getX() / distanceCheck.getZ())), 0.0f));

			if (distanceCheck.getZ() > 0)
			{
				enemy ->setRotate(enemy ->getRotate().add(Vector3f(0.0f, 180.0f, 0.0f)));
			}

			enemy ->setAttacking(true);
		}
		else if (totalDistance <= aggroRange * 0.45) //WAY TOO CLOSE
		{
			flee ->apply(enemy);
			faceB ->apply(enemy);
			enemy ->setAttacking(false);
		}
	}
	else
	{
		distanceCheck.set(enemy ->getSpawnPoint().getX() - enemy ->getPosition().getX(),
						  0.0f, 
						 enemy ->getSpawnPoint().getZ() - enemy ->getPosition().getZ()); 
 
		distanceCheck.normalize();
		enemy ->setVelocity(distanceCheck * enemy ->getSpeed());
	}
}

mobPattern::mobPattern() : AIstate()
{
}

mobPattern::~mobPattern()
{
}

void mobPattern::stateUpdate(Enemy *enemy)
{
}
