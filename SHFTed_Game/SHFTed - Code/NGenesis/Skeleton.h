
#pragma once

#include "Bone.h"
#include "Quaternion.h"
#include "Include.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define NG_Z_ROTATION 0
#define NG_X_ROTATION 1
#define NG_Y_ROTATION 2
#define NG_X_POSITION 3
#define NG_Y_POSITION 4
#define NG_Z_POSITION 5

#define NG_ROOT_INDEX 0

class Skeleton
{
public:
	Skeleton();
	Skeleton(const std::string fileName);
	~Skeleton();

	void initVariables();

	std::vector<Bone> getBoneList();
	std::vector<Bone>* getBones();

	Bone getMiddleOfRightHand();

	void playAnimation(float t);
	void drawSkeleton();

	void setupQuaternions();
	void setBindingPose();
	void setBindPoseAdvance(float t);
	void blendAnimation(float t,Skeleton *otherAnimation);

	void pushEndJoint();	
	void setSkeletonMatrix();
	void allocateSkeletonMatrix();

	unsigned int getNumFrames();
	float getFrameTime();

	void load(const std::string fileName);
	void printInfo();

	Vector3f rotation; 

	std::vector<std::vector<float>> motionData; //A vector holding a vector of data

	std::vector<std::vector<Quaternion>> orientations;
	 //Vector of a vector of quaternion orientations for animation 
	std::vector<Bone> boneList;

	std::vector<float> tempBoneList;
	int maxMsize;
	float *skeletonMatrix;

private:

	std::string _SKELETON_PATH;

	//HIERARCHY
	std::vector<Vector3f> _endSiteList; 

	//MOTION
	unsigned int _numFrames;
	float _frameTime;
	float _frame; 

	Quaternion _slerpPose;
};