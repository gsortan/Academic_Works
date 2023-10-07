#include "Animation.h"

Animation::Animation()
{
	initVariables();
}

Animation::~Animation()
{
}

void Animation::initVariables()
{
	_scaleModifier = Vector3f(0.0f, 0.0f, 0.0f);
	_squashAndStretchAmount = 0.1f;
	_squashAndStretchSpeed = 0.5f;
	_squashAndStretchTimer = 0.0f;
}

void Animation::addNewAnimation(unsigned int animation, float weight)
{
	_animations.push_back(animation);
	_animationWeights.push_back(weight);
}

Vector3f Animation::getScaleModifier()
{
	return _scaleModifier;
}

void Animation::squashAndStretch() 
{
	_scaleModifier.setX(sin(_squashAndStretchTimer) * _squashAndStretchAmount);
	_scaleModifier.setY(_squashAndStretchAmount - _scaleModifier.getX());
	_scaleModifier.setZ(_scaleModifier.getX());

	_squashAndStretchTimer += _squashAndStretchSpeed;
}

void Animation::update()
{
	for (unsigned int i = 0; i < _animations.size(); ++i)
	{
		switch (_animations[i])
		{
		case (NG_SQUASH_AND_STRETCH):
			squashAndStretch();
			break;
		}
	}
}

void Animation::weightAnimations() //Supposed to weight animations. Right now not doing that
{
}