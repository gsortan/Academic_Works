#pragma once

#include "Character.h"

class Game;
class AIstate;
class melee;
class ranged;

#define NG_RESPAWN_TIME 30

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	void initAI(Game* game);

	void setType(unsigned int type);
	void setDamage(float damage);
	void setEnemyType(unsigned int type);
	void setExperience(unsigned int experience);
	void setAggroRange(unsigned int range);

	void setCharacter(Character* chararacter);

	unsigned int getEnemyType();
	bool getLeashing();
	unsigned int getExperienceGiven();
	Timer* getSpawnTimer();

	//void updateDeath();
	void update(float &time);

private:
	unsigned int _type;
	unsigned int _experience;
	Character* _character;

	melee* _meleeAI;
	ranged* _rangedAI;

	Timer* _spawnTimer;

	bool _isLeashing;
};