#pragma once

#include "Model.h"

#define NG_MELEE 0
#define NG_RANGED 1

#define NG_RANGED_SPEED 200

#define NG_MANA_REGEN 0.15
#define NG_HEALTH_REGEN 0.03
#define NG_HEALTH_POT_HEAL 30
#define NG_MANA_POT_HEAL 15

#define NG_PROMPT_JUMPPAD -2
#define NG_PROMPT_LARGEJUMPPAD -3
#define NG_PROMPT_COMMONCOLLECTABLE -4
#define NG_PROMPT_STORYCOLLECTABLE -5
#define NG_PROMPT_ALLSHARDS -6
#define NG_PROMPT_WATERDEATH -7

#define NG_NO_STATUS 0
#define NG_BURN_STATUS 1
#define NG_FREEZE_STATUS 2
#define NG_STUN_STATUS 3
#define NG_DEATH_STATUS 4

class Character : public Model
{
public:
	Character();
	~Character();

	void initVariables();

	void setHealth(float health);
	void setMaxHealth(float health);
	void setMana(float mana);
	void setExperience(float exp);
	void setMeleeRange(float range);
	
	float getHealth();
	float getMana();
	float getExperience();
	float getMaxHealth();
	float getMaxMana();
	float getMaxExperience();
	unsigned int getLevel();

	float getMeleeAttackRange();
	float& getMeleeDamage();
	float getRangedAttackRange();
	float& getRangedDamage();

	float getMeleeDefense();
	float getRangedDefense();

	void setAttacking(bool state);
	bool getAttacking();

	void setHitTestStatus(unsigned int status);
	int getHitTestStatus();
	int getPlatformIndex();
	int getPreviousPlatformIndex();

	bool getLowHP();

	void setStatusEffect(unsigned int effect);
	unsigned int getStatusEffect();

	void setGliding(bool state);
	void setSliding(bool state);
	bool getSliding();

	void setEnvironmentList(unsigned int level, std::vector<Model*> &vector);
	void setInteractableList(unsigned int level, std::vector<Model*> &vector);
	void setCollectableText(Text &common, Text &story);
	void setPromptText(Text &text);

	void setStoryCount(unsigned int num);
	unsigned int getCommonCount();
	unsigned int getStoryCount();
	int getPromptData();

	void setBonus(unsigned int num);
	
	void updateExperience();
	void updateHealth();
	void updatePosition(float &time);
	void updateEnvCollision();
	void updateIntCollision();
	void updateStatus();

	void resetPlatformStuff();
	bool meleeHit(Vector3f &position);
	void damageTaken(float damage, unsigned int type);
	void update(float &time);

	static unsigned int currentLevel;

protected:
	//Combat and Stat Stuff
	unsigned int _level;

	float _health;
	float _maxHealth;
	float _mana;
	float _maxMana;
	float _experience;
	float _maxExperience;

	float _meleeAttackRange;
	float _meleeDamage;
	float _rangedAttackRange;
	float _rangedDamage;

	float _meleeDefense;
	float _rangedDefense;

	float _damageAccrued; //This is the variable that keeps track of how much damage the character has taken since the last update.
	Vector3f _attackReference; //The "reference" point for your attacks. AKA where the attack circle is centered at

	bool _isAttacking;
	bool _lowHP;

	unsigned int _statusEffect;
	Timer* _statusTimer; //Timer used to keep track of how long you were afflicted with a status
	float _statusReference; //Reference variable for status effects

	Timer* _attackTimer; //The time we're currently at for attacking
	float _attackTime; //The amount of time between each attack in seconds

	//Misc Stats
	float _healthBonus;
	float _manaBonus;
	float _meleeDamageBonus;
	float _rangedDamageBonus;
	float _meleeRangeBonus;
	float _rangedRangeBonus;
	float _meleeDefenseBonus;
	float _rangedDefenseBonus;

	//Hit Test
	int _currentHitTestStatus; //Stores the non top/bottom hit test status for the hit test last check
	int _platformIndex; //Stores the index of the model you are on
	int _previousPlatformIndex; //Stores the index of the model you were last on if you are currently not on a model

	bool _collidingHorizontalLR; //Controls whether or not you already hit something's side (Left or right)
	bool _collidingHorizontalTB; //Controls whether or not you already hit something's side (Top or bottom)
	bool _collidingVertical; //Controls whether or not you are hitting something vertically

	//Misc
	bool _gliding;
	bool _sliding;

	//Pointers to stuff
	std::vector<Model*>* _environmentList[2];
	std::vector<Model*>* _interactableList[2];
	Text* _commonCollectableText;
	Text* _storyCollectableText;
	unsigned int _commonCounter;
	unsigned int _storyCounter;
	Text* _promptText;
	int _promptData;

	//Temps
	float tempFloat; //Just a temp float
	int tempInt; //Temp int
};