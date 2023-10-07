#include "Character.h"

unsigned int Character::currentLevel = 0; //Forest

Character::Character() : Model()
{
	initVariables();
}

Character::~Character()
{

}

void Character::initVariables()
{
	_level = 1;

	_health = (float) (_level - 1) * 10 + 200;
	_maxHealth = (float) (_level - 1) * 10 + 200;
	_mana = (float) (_level - 1) * 5 + 100;
	_maxMana = (float) (_level - 1) * 5 + 100;
	_experience = 0.0f;
	_maxExperience = (float) (_level - 1) * 50 + 100;	

	_meleeAttackRange = 50.0f;
	_meleeDamage = (float) (_level - 1) * 1 + 20;
	_rangedAttackRange = 250.0f;
	_rangedDamage = (float) (_level - 1) * 1 + 15;

	_meleeDefense = 1.0f;
	_rangedDefense = 0.0f;

	_damageAccrued = 0.0f;
	_attackReference.set(0.0f, 0.0f, 0.0f);

	_isAttacking = false;

	_statusEffect = NG_NO_STATUS; //Controls your status effects
	_statusTimer = new Timer();

	_attackTimer = new Timer(); //The time we're currently at for attacking
	_attackTime = 1.0f; //The amount of time between each attack in seconds

	_healthBonus = 0.0f;
	_manaBonus = 0.0f;
	_meleeDamageBonus = 0.0f;
	_rangedDamageBonus = 0.0f;
	_meleeRangeBonus = 0.0f;
	_rangedDamageBonus = 0.0f;
	_meleeDefenseBonus = 0.0f;
	_rangedDefenseBonus = 0.0f;

	_environmentList[0] = new std::vector<Model*>;
	_environmentList[1] = new std::vector<Model*>;
	
	_interactableList[0] = new std::vector<Model*>;
	_interactableList[1] = new std::vector<Model*>;

	_commonCounter = 0;
	_storyCounter = 0;
	_promptText = new Text();
	_promptData = -1;

	_currentHitTestStatus = NG_NO_HIT;
	_platformIndex = -1;
	_previousPlatformIndex = -1;

	_skeletonAnimation = new playerAnimations();

	_animationTimer = new Timer();

	_sliding = false;
}

void Character::setHealth(float health)
{
	_health = health;
}

void Character::setMaxHealth(float health)
{
	_health = health;
	_maxHealth = health;
}

void Character::setMana(float mana)
{
	_mana = mana;
}

void Character::setExperience(float exp)
{
	_experience = exp;
}

void Character::setMeleeRange(float range)
{
	_meleeAttackRange = range;
}
	
float Character::getHealth()
{
	return _health;
}

float Character::getMaxHealth()
{
	return _maxHealth;
}

float Character::getMana()
{
	return _mana;
}

float Character::getMaxMana()
{
	return _maxMana;
}

float Character::getExperience()
{
	return _experience;
}

float Character::getMaxExperience()
{
	return _maxExperience;
}

unsigned int Character::getLevel()
{
	return _level;
}

float Character::getMeleeAttackRange()
{
	return _meleeAttackRange;
}

float& Character::getMeleeDamage()
{
	return _meleeDamage;
}

float Character::getRangedAttackRange()
{
	return _rangedAttackRange;
}

float& Character::getRangedDamage()
{
	return _rangedDamage;
}

void Character::setAttacking(bool state)
{
	_isAttacking = state;

	if (_isAttacking == true && _attackTimer ->isRunning() == false)
	{
		_attackTimer ->start();
	}
	else if (_isAttacking == false && _attackTimer ->isRunning() == true)
	{
		_attackTimer ->stop();
	}
}

bool Character::getAttacking()
{
	return _isAttacking;
}

void Character::setHitTestStatus(unsigned int status)
{
	_currentHitTestStatus = status;
}

int Character::getHitTestStatus()
{
	return _currentHitTestStatus;
}

int Character::getPlatformIndex()
{
	return _platformIndex;
}

int Character::getPreviousPlatformIndex()
{
	return _previousPlatformIndex;
}

bool Character::getLowHP()
{
	return _lowHP;
}

void Character::setStatusEffect(unsigned int effect)
{
		_statusEffect = effect;
		_statusTimer ->reset();
}

unsigned int Character::getStatusEffect()
{
	return _statusEffect;
}

void Character::setGliding(bool state)
{
	_gliding = state;
}

void Character::setSliding(bool state)
{
	_sliding = state;
}

bool Character::getSliding()
{
	return _sliding;
}

void Character::setEnvironmentList(unsigned int level, std::vector<Model*> &vector)
{
	_environmentList[level] = &vector;
}

void Character::setInteractableList(unsigned int level, std::vector<Model*> &vector)
{
	_interactableList[level] = &vector;
}

void Character::setCollectableText(Text &common, Text &story)
{
	_commonCollectableText = &common;
	_storyCollectableText = &story;
}

void Character::setPromptText(Text &text)
{
	_promptText = &text;
}

void Character::setStoryCount(unsigned int num)
{
	_storyCounter = 0;
}

unsigned int Character::getCommonCount()
{
	return _commonCounter;
}

unsigned int Character::getStoryCount()
{
	return _storyCounter;
}

int Character::getPromptData()
{
	return _promptData;
}

void Character::setBonus(unsigned int num) //Gives you a bonus depending on which you feed it
{
	switch (num)
	{
	case (0):

		_notificationText[_notificationCounter] ->setText("HEALTH BONUS"); //*_notificationCounter
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_healthBonus += 5;
		_maxHealth = (_level - 1) * 10 + 200 + _healthBonus;
		break;
	case (1):
		_notificationText[_notificationCounter] ->setText("MANA BONUS");
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_manaBonus += 5;
		_maxMana = (_level - 1) * 5 + 100 + _manaBonus;
		break;
	case (2):
		_notificationText[_notificationCounter] ->setText("MELEE DAMAGE BONUS");
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_meleeDamageBonus += 0.5;
		_meleeDamage = (_level - 1) * 1 + 10 + _meleeDamageBonus;
		break;
	case (3):
		_notificationText[_notificationCounter] ->setText("RANGED DAMAGE BONUS");
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_rangedDamageBonus += 0.5;
		_rangedDamage = (_level - 1) * 1 + 5 + _rangedDamageBonus;
		break;
	case (4):
		_notificationText[_notificationCounter] ->setText("MELEE DAMAGE BONUS");
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_meleeDefenseBonus += 0.5;
		_meleeDamage = (_level - 1) * 1 + 5 + _meleeDamageBonus;
		break;
	case (5):
		_notificationText[_notificationCounter] ->setText("RANGED DAMAGE BONUS");
		_notificationTimer[_notificationCounter] ->reset();
		_notificationTimer[_notificationCounter] ->start();
		++_notificationCounter;

		if (_notificationCounter == 5) //Reached the cap
		{
			_notificationCounter = 0;
		}

		_rangedDefenseBonus += 0.5;
		_rangedDamage = (_level - 1) * 1 + 5 + _rangedDamageBonus;
		break;
	}
}

void Character::updateExperience()
{
	if (_experience >= _maxExperience) //If you can level up
	{
		++_level;
		_experience = _experience - _maxExperience; //Deducts exp used in level up

		_maxExperience = (_level - 1) * 50 + 100;
		_maxHealth = (_level - 1) * 10 + 200 + _healthBonus;
		_maxMana = (_level - 1) * 5 + 100 + _manaBonus;
		_meleeDamage = (_level - 1) * 1 + 12 + _meleeDamageBonus;
		_rangedDamage = (_level - 1) * 1 + 15 + _rangedDamageBonus;

		_health = _maxHealth; //Sets you back to full health
		_mana = _maxMana; //Sets you back to full mana
	}
}

void Character::updateHealth()
{
	_health -= _damageAccrued; //This makes it so that damage is accrued is taken into account
	_damageAccrued = 0; //And then set to 0 for this frame.

	if (_health <= _maxHealth)
	{
		_health += NG_HEALTH_REGEN;

		_lowHP = false;

		if (_health <= 0) //If you be dead
		{
			_active = false;
			_health = 0;
		}
		else if (_health <= _maxHealth * 0.3)
		{
			_lowHP = true;
		}
		
	}

}

void Character::updatePosition(float &time)
{
	if (_sliding == false)
	{
		_previousPosition = _position;

		if (_platformIndex == -1) //Kinda hacky, but our only accel is gravity. So runs when not on platform
		{
			_velocity = _velocity.add(_acceleration.scalarMultiply(time));
		}

		if (_gliding == true) //If you are gliding
		{
			_velocity.setY(2 * _acceleration.scalarMultiply(time).getY()); //Slow your descent
		}
	
		_platformIndex = -1; //Resets every update

		_position = _position.add(_velocity.scalarMultiply(time));
		_adjustedPosition = _position.add(_velocity.scalarMultiply(time));

		if (_position.getY() < 0) //DON'T FALL THROUGH THE WORLD BRO
		{
			_position.setY(0.0f);
			_adjustedPosition.setY(0.0f);
			_platformIndex = 0;
		}
	}
	else //Just go if you be sliding
	{
		_position = _position.add(_velocity.scalarMultiply(time));
		_adjustedPosition = _position.add(_velocity.scalarMultiply(time));
	}
}

void Character::updateEnvCollision()
{
	_collidingHorizontalLR = false; //Resets to false. When both are true break out of collision
	_collidingHorizontalTB = false; //See above.
	_collidingVertical = false; //See above.


	for (unsigned int i = 0; i < _environmentList[currentLevel] ->size(); ++i)
	{
		{
			setHitTestStatus(hitTest(*_environmentList[currentLevel] ->at(i), NG_BOX_COLLISION));

			if (_currentHitTestStatus == NG_HIT_TOP)
			{	
				_platformIndex = i;
				_previousPlatformIndex = i;
				_position.setY(_environmentList[currentLevel] ->at(i) ->getPosition().getY() + _environmentList[currentLevel] ->at(i) ->getMaxSize().getY());

				if (_environmentList[currentLevel] ->at(i) ->getModelName() == "Water.obj") //Hard coded to figure out if you are landing in water
				{
					_health = 0.0f; //YOU DIEDED
					_active = false;
					_promptData = NG_PROMPT_WATERDEATH;
				}

				_collidingVertical = true;
			}
			else if (_currentHitTestStatus == NG_HIT_BOTTOM)
			{
				_position.setY(_environmentList[currentLevel] ->at(i) ->getPosition().getY() + _environmentList[currentLevel] ->at(i) ->getMinSize().getY() - _modelSizeMax.getY());
				_velocity.setY(0.0f); //Zero out your vertical velocity
			}
			else if (_currentHitTestStatus == NG_HIT_LEFT)
			{
				_position.setX(_previousPosition.getX() - 0.1);

				_collidingHorizontalLR = true;
			}
			else if (_currentHitTestStatus == NG_HIT_RIGHT) //If you are hitting something
			{
				_position.setX(_previousPosition.getX() + 0.1);
				
				_collidingHorizontalLR = true;
			}
			else if (_currentHitTestStatus == NG_HIT_UP)
			{
				_position.setZ(_previousPosition.getZ() + 0.1);

				_collidingHorizontalTB = true;
			}
			else if (_currentHitTestStatus == NG_HIT_DOWN)
			{
				_position.setZ(_previousPosition.getZ() - 0.1);
				
				_collidingHorizontalTB = true;
			}

			if (_collidingHorizontalLR && _collidingHorizontalTB && _collidingVertical) //If you are already on something and are hitting something on the side, we don't need to check anymore
			{
				break; //Break out of loop
			}
		}
	}		
}

void Character::updateIntCollision()
{
	for (unsigned int i = 0; i < _interactableList[currentLevel] ->size(); ++i) //For every object..
	{
		if (_interactableList[currentLevel] ->at(i) ->getActive() == true)
		{
			if (hitTest(*_interactableList[currentLevel] ->at(i), NG_CIRCLE_COLLISION) == NG_HIT) //Checks if you are hitting the object
			{

				if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getModelName().find("Chest"))
				{
					if (_promptText ->getText() != "Press X to open the chest.") //Only throw that in if it's not already in there
					{
						_promptText ->setText("Press X to open the chest.");
					}

					_promptData = i;

					break; //Level design says we can only hit one of them at a time
				}
		
				else if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getModelName().find("Jump"))
				{
					if (_interactableList[currentLevel] ->at(i) ->getTextureName(0) == "red.jpg") //Only do it if it's the read
					{
						if (!(std::string::npos != _interactableList[currentLevel] ->at(i) ->getModelName().find("LARGE"))) //Check if it's not the super one
						{
							_velocity = Vector3f(_velocity.getX(), 400.0f, _velocity.getZ()); //JUMP'D
							_promptData = NG_PROMPT_JUMPPAD;
						}
						else
						{
							_velocity = Vector3f(_velocity.getX(), 670.0f, _velocity.getZ()); //SUPER JUMP'D
							_promptData = NG_PROMPT_LARGEJUMPPAD;
						}	
					}

					break; //Level design says we can only hit one of them at a time
				}
			
				else if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getModelName().find("Story"))
				{
					if (_interactableList[currentLevel] ->at(i) ->getPath() ->getActive() == false) //Only care about it if it is not currently active
					{
						if (_storyCounter < 5)
						{
							
							++_storyCounter;
							_promptData = i;

							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_interactableList[currentLevel] ->at(i) ->getPosition());
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_interactableList[currentLevel] ->at(i) ->getPosition());
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(15.0f, 0.0f, 15.0f)));
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(15.0f, 0.0f, -15.0f)));
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(-15.0f, 0.0f, -15.0f)));
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(-15.0f, 0.0f, 15.0f)));
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(0.0f, 100.0f, 0.0f)));
							_interactableList[currentLevel] ->at(i) ->getPath() ->addNewPoint(_position.add(Vector3f(0.0f, 100.0f, 0.0f)));

							_interactableList[currentLevel] ->at(i) ->getPath() ->setActive(true);
							_interactableList[currentLevel] ->at(i) ->getPath() ->setSpeed(0.05f);

							if (_storyCounter == 5)
							{
								_promptData = NG_PROMPT_ALLSHARDS;
								_storyCollectableText ->setText("Find the alter!");
							}
						}

						break; //Level design says we can only hit one of them at a time
					}
				}
				else if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getTextureName(0).find("HP")) //Texture name since model name is the same
				{
					_interactableList[currentLevel] ->at(i) ->setActive(false); //Turn it off
					_health += NG_HEALTH_POT_HEAL;

					if (_health > _maxHealth) //Clamps health to max if you passed it
					{
						_health = _maxHealth;
					}

					break; //Level design says we can only hit one of them at a time
				}
				else if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getTextureName(0).find("MP")) //Texture name since model name is the same
				{
					_interactableList[currentLevel] ->at(i) ->setActive(false); //Turn it off
					_mana += NG_MANA_POT_HEAL;

					if (_mana > _maxMana) //Clamps mana to max if you passed it
					{
						_mana = _maxMana;
					}

					break; //Level design says we can only hit one of them at a time
				}
				else if (std::string::npos != _interactableList[currentLevel] ->at(i) ->getModelName().find("slide")) //ARE YOU GONNA SLIDE?!
				{
					_sliding = true;

					break; //Level design says we can only hit one of them at a time
				}
			}
		}
	}
}

void Character::updateStatus() //Changes the character depending on it's status effects
{
	if (_statusEffect != NG_NO_STATUS)
	{
		if (_statusTimer ->isRunning() == false) //Turns on the timer if it was off, since clearly you have a status effect
		{
			_statusReference = 0; //Zeros out the refernece variable
			_statusTimer ->start();			
		}

		if (_statusEffect != NG_DEATH_STATUS)
		{
			if (_statusEffect == NG_BURN_STATUS) //If you are burned, take DoT
			{
				_color.r = 1.0f; //Turns you orange
				_color.g = 0.65f;
				_color.b = 0.0f;

				_health -= (_statusTimer ->get(NG_TIMER_SECONDS) - _statusReference) * 5.0f; //Takes damage over time
				_statusReference = _statusTimer ->get(NG_TIMER_SECONDS); //Updates the reference

				if (_statusTimer ->get(NG_TIMER_SECONDS) >= 3) //If more than 3 seconds, turn off
				{
					_statusTimer ->stop();
					_statusEffect = NG_NO_STATUS;
					_color.r = 1.0f;
					_color.g = 1.0f;
					_color.b = 1.0f;
				}
			}
			else if (_statusEffect == NG_FREEZE_STATUS) //Slows movement speed by 75% if slowed
			{
				_color.r = 0.2f; //Turns you icey blue
				_color.g = 0.7f;
				_color.b = 1.0f;

				_velocity = _velocity.scalarMultiply(0.25f);

				if (_statusTimer ->get(NG_TIMER_SECONDS) >= 3) //If more than 3 seconds, turn off
				{
					_statusTimer ->stop();
					_statusEffect = NG_NO_STATUS;
					_color.r = 1.0f;
					_color.g = 1.0f;
					_color.b = 1.0f;
				}
			}
			else if (_statusEffect == NG_STUN_STATUS) //Stuns you for a second if youre stunned
			{
				_color.r = 0.4f; //Turns you brown
				_color.g = 0.2f;
				_color.b = 0.0f;

				_velocity = Vector3f(0.0f, 0.0f, 0.0f); //Zeros velocity

				if (_statusTimer ->get(NG_TIMER_SECONDS) >= 1) //If more than 1 second, turn off
				{
					_statusTimer ->stop();
					_statusEffect = NG_NO_STATUS;
					_color.r = 1.0f;
					_color.g = 1.0f;
					_color.b = 1.0f;
				}
			}
		}
		else
		{
			_color.r = 1.0f;
			_color.g = 1.0f;
			_color.b = 1.0f;

			_color.a -= 0.01f;
		}
	}
}

void Character::resetPlatformStuff() //Resets the previuos and current platform indices
{
	_previousPlatformIndex = -1;
	_platformIndex = -1;
}

bool Character::meleeHit(Vector3f &position) //Checks whether or not that point is found within your hit range
{
	if (position.subtract(_position).calcMagnitude() <= _meleeAttackRange + _meleeRangeBonus) //Initial check; is the point within your attack radius? If not then we don't need to go in depth
	{
		_attackReference.setX(_position.getX() + (_meleeAttackRange + _meleeRangeBonus) / 2 * sin(mDegToRad(_rotate.getY()))); //Calculates your circle using trig based off of your current position
		_attackReference.setY(_position.getY()); //You attack on the same level as your character
		_attackReference.setZ(_position.getZ() + (_meleeAttackRange + _meleeRangeBonus) / 2 * cos(mDegToRad(_rotate.getY())));

		if (_attackReference.subtract(position).calcMagnitude() <= (_meleeAttackRange + _meleeRangeBonus) / 2) //If that point is found within the circle
		{
			return true; //Hitting it
		}
		else
		{
			return false; //Not hitting it
		}
	}
	else //Not even close.
	{
		return false; 
	}
}

void Character::damageTaken(float damage, unsigned int type) //Accrues damage for this frame
{
	if (type == NG_MELEE)
	{
		if (damage - _meleeDefense - _meleeDefenseBonus > 0.5) //0.5 is the min damage taken
		{
			_damageAccrued += damage - _meleeDefense - _meleeDefenseBonus;
		}
		else
		{
			_damageAccrued += 0.5;
		}
	}
	else
	{
		_damageAccrued += damage - _rangedDefense - _rangedDefenseBonus;
	}
}

void Character::update(float &time)
{
	if (_active)
	{
		_promptData = -1; //Resets prompt data

		updateStatus();
		updateExperience();	
		updateHealth();

		if (_sliding == true) //Sets your velocity to a hard coded amount if you are sliding
		{
			_velocity = Vector3f(_velocity.getX(), -sin(mDegToRad(30)) * _speed * 1.5, cos(mDegToRad(30)) * _speed * 1.5);
			//30 deg
		}

		if (_linkType == NG_NO_LINK)
		{
			updatePosition(time);
		}
		else
		{
			updateLink();
		}
		
		updateEnvCollision();
		updateIntCollision();

		if (_mana < _maxMana)
		{
			_mana += (float) NG_MANA_REGEN;
		}		


		if (_statusEffect != NG_STUN_STATUS)
		{
			if (_vShader ->getShaderName() == "skinMeshWithLighting") //Are you GPU Mesh skinning?
			{

				if (!_skeletonAnimation ->isWeapon)
				{
					if (_isAttacking == false)
					{
						if (_platformIndex == -1) //You are in the air
						{
							if (_velocity.getY() > 0) //You are moving in the Y
							{
								_skeletonAnimation ->setAnimation(ANIM_JUMP); 
							}
							else
							{
								_skeletonAnimation ->setAnimation(ANIM_FALL);
							}
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
					}
				}

				_skeletonAnimation ->animationUpdate();
			}

			transformations.makeHomogenous(_rotate, _position, _scale);
		}
	}
}