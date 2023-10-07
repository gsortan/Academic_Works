
#pragma once

#include "Vector3f.h"
#include "Conversion.h"
#include <vector>

#define NG_SQUASH_AND_STRETCH 0

class Animation
{
public:
	Animation();
	~Animation();

	void initVariables();
	void addNewAnimation(unsigned int animation, float weight);

	Vector3f getScaleModifier();

	void squashAndStretch();

	void update();
	void weightAnimations();

private:
	std::vector<unsigned int> _animations;
	std::vector<float> _animationWeights;

	float _squashAndStretchAmount;
	float _squashAndStretchSpeed;
	float _squashAndStretchTimer;

	Vector3f _scaleModifier;
};