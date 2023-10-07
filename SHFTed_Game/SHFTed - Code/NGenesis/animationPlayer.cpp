#include "animationPlayer.h"
#include "Game.h"

Skeleton* animationPlayer::walkCyclePlayer = new Skeleton("MB_Walk_Cycle_A_Take_001.bvh");
Skeleton* animationPlayer::runCyclePlayer = new Skeleton("MB_Run_Cycle_A_Take_001.bvh");
Skeleton* animationPlayer::idleAnimPlayer = new Skeleton("MB_Idle_A_Take_001.bvh");
Skeleton* animationPlayer::attackAnimPlayer = new Skeleton("Attack1_Take_001.bvh"); //Nothing yet.
Skeleton* animationPlayer::jumpAnimPlayer = new Skeleton("Jump-UP_Take_001.bvh");
Skeleton* animationPlayer::fallAnimPlayer = new Skeleton("Jump-Fall_Take_001.bvh");

Skeleton* animationPlayer::runCycleSword = new Skeleton("Sword_run_no_joint_3_Take_001.bvh");
Skeleton* animationPlayer::idleAnimSword = new Skeleton("Sword_Idle_Take_001.bvh");
Skeleton* animationPlayer::attackAnimSword = new Skeleton("Sword_Attack_1_Finished_Take_001.bvh");
Skeleton* animationPlayer::bindPoseSword = new Skeleton("Sword_bindpose_fixed_Take_001.bvh");
Skeleton* animationPlayer::jumpAnimSword = new Skeleton("Sword_Jump_UP_Take_001.bvh");
Skeleton* animationPlayer::fallAnimSword = new Skeleton("Sword_Jump_FALL_Take_001_Take_001.bvh");

Skeleton* animationPlayer::attackAnimArcher = new Skeleton("Archer_Attack_Take_001.bvh");

animationPlayer::animationPlayer(void)
{


	runCycleNS = *runCyclePlayer;
	idleAnimNS = *idleAnimPlayer;
	attackAnimNS = *attackAnimPlayer;
	jumpAnimNS = *jumpAnimPlayer;
	fallAnimNS = *fallAnimPlayer;

	isSword = false;
	isWeapon = false;
	isArcher = false;
}

animationPlayer::~animationPlayer(void)
{
}

void animationPlayer::bindSkeleton(float *indices, unsigned int size)
{
}

void animationPlayer::animationReset()
{
}

void animationPlayer::animationUpdate()
{
}

void animationPlayer::setSkin(Skin &theSkin)
{
	skin = theSkin;
	skin.setJointIndices(*runCycleNS.getBones()); //Defaults to this thing
}

void animationPlayer::makeIntoSword()
{
	runCycleNS = *runCycleSword;
	idleAnimNS = *idleAnimSword;
	attackAnimNS = *attackAnimSword;
	jumpAnimNS = *jumpAnimSword;
	fallAnimNS = *fallAnimSword;

	isSword = true;
	isWeapon = true;
}

void animationPlayer::makeIntoSoldier(bool sword)
{
	if (sword)
	{
		isWeapon = true;
	}
}

void animationPlayer::makeIntoArcher(bool crossbow)
{
	attackAnimNS = *attackAnimArcher;

	if (crossbow)
	{
		isWeapon = true;
	}
	else
	{
		isArcher = true;
	}
}

void animationPlayer::makeIntoHeavy(bool club)
{
	runCycleNS = *walkCyclePlayer;

	if (club)
	{
		isWeapon = true;
	}
}

void playerAnimations::setAnimation(short num)
{
	if (animState != num)
	{
		animState = num;
		swapState = 0;
	}
}

short playerAnimations::getAnimation()
{
	return animState;
}

playerAnimations::playerAnimations()
{
	swapState = 0;
	currentTime = 0;
	tempTime = 0;
	animState = 2;
	animTimer = new Timer();
	swordTimer = new Timer();
}

playerAnimations::~playerAnimations()
{
}

void playerAnimations::bindSkeleton(float *indices, unsigned int size)
{
	/*Bind skin*/

	skin.setAndSortMeshIndices(indices, size);
	skin.setWeightAndJointPointers(); 


	runCycleNS.setBindingPose();	
	idleAnimNS.setBindingPose();	
	attackAnimNS.setBindingPose();	
	jumpAnimNS.setBindingPose();
	fallAnimNS.setBindingPose();

	if (isSword) 
	{
		bindPoseSword ->setBindingPose(); //Set the binding pose for the bind pose

		for (unsigned int i = 0; i < bindPoseSword ->getBoneList().size(); ++i) //Take the above bind pose and make that the bind pose for these animations
		{
			runCycleNS.boneList.at(i).bindMatrix = bindPoseSword ->boneList.at(i).bindMatrix;
			idleAnimNS.boneList.at(i).bindMatrix = bindPoseSword ->boneList.at(i).bindMatrix;
			attackAnimNS.boneList.at(i).bindMatrix = bindPoseSword ->boneList.at(i).bindMatrix;
			jumpAnimNS.boneList.at(i).bindMatrix = bindPoseSword ->boneList.at(i).bindMatrix;
			fallAnimNS.boneList.at(i).bindMatrix = bindPoseSword ->boneList.at(i).bindMatrix;
		}
	}

	runCycleNS.setSkeletonMatrix();
	idleAnimNS.setSkeletonMatrix();
	attackAnimNS.setSkeletonMatrix();
	jumpAnimNS.setSkeletonMatrix();
	fallAnimNS.setSkeletonMatrix();

	animationSpeed = 3.2;

	/*Start timer*/
	animTimer ->start();
	animationUpdate();
}

void playerAnimations::animationReset()
{
	animTimer ->reset();
	animTimer ->start();
	tempTime = 0;
}


void playerAnimations::animationUpdate()
{	
	hardcodeSpeed = 1;

	switch (animState)
	{
	case ANIM_ATTACK:
		if (swapState == 0)
		{
			currentClip = &attackAnimNS;
			swapState = 1;
			animationReset();
		}
		break;
	case ANIM_RUN:
		if (swapState == 0)
		{
			currentClip = &runCycleNS;
			swapState = 1;
			animationReset();
		}
		break;
	case ANIM_IDLE:
		if (swapState == 0)
		{
			currentClip = &idleAnimNS;
			swapState = 1;
			animationReset();
		}
		break;
	case ANIM_JUMP:
		if (swapState == 0)
		{
			currentClip = &jumpAnimNS;		
			swapState = 1;
			hardcodeSpeed = 0.5;
			animationReset();
		}
		break;
	case ANIM_FALL:
		if (swapState == 0)
		{		
			currentClip = &fallAnimNS;
			swapState = 1;
			animationReset();
		}
		break;
	default:
		break;
	}

	/*Start timer for all animations*/
	tempTime = animTimer ->get(NG_TIMER_MILLISECONDS);

	currentTime = tempTime * currentClip ->getFrameTime();

	if (currentTime * animationSpeed * hardcodeSpeed > currentClip ->getNumFrames() - 1) //If you are currently over the animation time
	{
		if (!isWeapon)
		{
			if (animState == ANIM_JUMP || animState == ANIM_FALL)
			{
				
				tempTime = currentClip ->getNumFrames() - 1;
			}
			else
			{
				animationReset();
				currentClip ->playAnimation(tempTime * animationSpeed * hardcodeSpeed);
			}
		}
		else
		{
			animationReset();
			currentClip ->playAnimation(tempTime * animationSpeed * hardcodeSpeed);
		}
	}
	else
	{
		currentClip ->playAnimation(tempTime * animationSpeed * hardcodeSpeed);
	}

	currentClip ->allocateSkeletonMatrix();	
}

enemyAnimations::enemyAnimations()
{
	animTimer = new Timer();
	animTimer ->start();
	currentTime = 0;
}

enemyAnimations::~enemyAnimations()
{
}

void enemyAnimations::bindSkeleton(float *indices, unsigned int size)
{
}

void enemyAnimations::animationReset()
{

}

void enemyAnimations::animationUpdate()
{
	currentTime = animTimer ->get(NG_TIMER_MILLISECONDS);
}




