#include "Enemy.h"
#include "Game.h"
#include "AIstate.h"

Enemy::Enemy() : Character()
{
	_type = NG_MELEE; //Defaults to melee character
	_experience = 25; //Default EXP amount
	_isLeashing = false;

	_meleeAI = new melee();
	_rangedAI = new ranged();

	_spawnTimer = new Timer();
}

Enemy::~Enemy()
{
}

void Enemy::initAI(Game *game)
{
	if (_type == NG_MELEE)
	{
		_meleeAI ->init(game);
	}
	else
	{
		_rangedAI ->init(game);
	}
}

void Enemy::setType(unsigned int type)
{
	_type = type;
}

void Enemy::setDamage(float damage)
{
	_meleeDamage = damage;
	_rangedDamage = damage;
}

void Enemy::setEnemyType(unsigned int type)
{
	_type = type;
}

void Enemy::setExperience(unsigned int num)
{
	_experience = num;
}

void Enemy::setAggroRange(unsigned int range)
{

	_meleeAI ->aggroRange = range;
	_rangedAI ->aggroRange = range;
}

void Enemy::setCharacter(Character* character)
{
	_character = new Character();
	_character = character;
}

unsigned int Enemy::getEnemyType()
{
	return _type;
}

bool Enemy::getLeashing()
{
	return _isLeashing;
}

unsigned int Enemy::getExperienceGiven()
{
	return _experience;
}

Timer* Enemy::getSpawnTimer()
{
	return _spawnTimer;
}

void Enemy::update(float &time)
{
	if (_active)
	{
		if (_platformIndex != -1) //Makes sure you're not falling
		{
			if (_type == NG_MELEE)
			{
				_meleeAI ->stateUpdate(this);
			}
			else
			{
				_rangedAI ->stateUpdate(this);
			}

		}

		updateStatus();
		updateHealth();
		
		if (_linkType == NG_NO_LINK)
		{
			updatePosition(time);

		}
		else
		{
			updateLink();
		}

		updateEnvCollision();

		if (_statusEffect != NG_STUN_STATUS)
		{
			if (_vShader ->getShaderName() == "skinMeshWithLighting") //Are you GPU Mesh skinning?
			{

				_promptData = -1;

				if (_isAttacking == false)
				{
					if (_platformIndex == -1) //You are in the air
					{
	
					}
					else
					{
						if (_velocity.getX() != 0 || _velocity.getZ() != 0) //You are moving in the X and/or Z
						{
							_skeletonAnimation ->setAnimation(ANIM_RUN); 
						}
						else
						{
							_skeletonAnimation ->setAnimation(ANIM_IDLE);
						}
					}
				}
				else
				{
					_skeletonAnimation ->setAnimation(ANIM_ATTACK);

					float tempTime = _skeletonAnimation ->animTimer ->get(NG_TIMER_MILLISECONDS);

					float currentTime = tempTime * _skeletonAnimation ->currentClip ->getFrameTime();

					if (currentTime * _skeletonAnimation ->animationSpeed * _skeletonAnimation ->hardcodeSpeed > _skeletonAnimation ->currentClip ->getNumFrames() - 1) //If you are currently over the animation time
					{
						_isAttacking = false;
					}

					if (_attackTimer ->get(NG_TIMER_SECONDS) > _attackTime) //Is your cooldown up?
					{
						if (_type == NG_RANGED)
						{
							_promptData = NG_RANGED; //Fire projectile
							_attackTimer ->reset();
						}
						else if (_type == NG_MELEE)
						{
							_attackTimer ->reset();
						}
					}
				}

				_skeletonAnimation ->animationUpdate();
			}

			transformations.makeHomogenous(_rotate, _position, _scale);
		}
}