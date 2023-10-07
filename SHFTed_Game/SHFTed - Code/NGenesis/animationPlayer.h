#pragma once
#include "Timer.h"
#include "Skeleton.h"
#include "Skin.h"
#include <vector>

#define ANIM_ATTACK 0
//#define ANIM_WALK 2
#define ANIM_RUN 1
#define ANIM_IDLE 2
#define ANIM_JUMP 3
#define ANIM_FALL 4

class Game;
class animationPlayer
{
public:
	animationPlayer(void);
	animationPlayer(bool state);
	~animationPlayer(void);

	/*List of all animations*/
	static Skeleton* walkCyclePlayer;
	static Skeleton* runCyclePlayer;
	static Skeleton* idleAnimPlayer;
	static Skeleton* attackAnimPlayer;
	static Skeleton* jumpAnimPlayer;
	static Skeleton* fallAnimPlayer;

	static Skeleton* runCycleSword;
	static Skeleton* idleAnimSword;
	static Skeleton* attackAnimSword;
	static Skeleton* bindPoseSword;
	static Skeleton* jumpAnimSword;
	static Skeleton* fallAnimSword;

	static Skeleton* attackAnimArcher;

	//NS means not static
	Skeleton runCycleNS;
	Skeleton idleAnimNS;
	Skeleton attackAnimNS;
	Skeleton jumpAnimNS;
	Skeleton fallAnimNS;
	

	Skeleton* currentClip;

	float animationSpeed;


	//Skin* skin;
	Skin skin;

	/*Level pointer*/
	Game *currentLevel; 
	
	void init(Game *theLevel) //Create current game instance and make everything available to current AI state
	{
		currentLevel = theLevel;	
	}

	virtual void bindSkeleton(float *indices, unsigned int size);
	virtual void animationReset();
	virtual void animationUpdate(); //Virtual function for update
	void setSkin(Skin &theSkin);
	void makeIntoSword();
	void makeIntoSoldier(bool sword);
	void makeIntoArcher(bool crossbow);
	void makeIntoHeavy(bool club);

	float hardcodeSpeed; //Hard coded value for speed if any animations need to be sped up/down specifically
	bool isSword;
	bool isWeapon;
	bool isArcher;
};

class playerAnimations:public animationPlayer
{
public:
	playerAnimations();
	~playerAnimations();

	virtual void bindSkeleton(float *indices, unsigned int size);
	virtual void animationReset();
	virtual void animationUpdate();
	
	void setAnimation(short num);
	short getAnimation();

	float currentTime;
	Timer *animTimer;
	Timer *swordTimer;
	float tempTime;
	float swordTempTime;
	float currentSwordTime;
	short animState;
	short swapState;

protected:
	short start;
	
};

class enemyAnimations:public animationPlayer
{
public:
	enemyAnimations();
	~enemyAnimations();

	virtual void bindSkeleton(float *indices, unsigned int size);
	virtual void animationReset();
	virtual void animationUpdate();
	

protected:
	Timer *animTimer;
	float currentTime;
};



