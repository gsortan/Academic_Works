#include "Bone.h"

Bone::Bone()
{
	initVariables();
}

Bone::~Bone()
{
}

void Bone::initVariables()
{
	name = "I_HAVE_NO_NAME";

	offset = Vector3f(0.0f, 0.0f, 0.0f);

	numChannels = 0;
	
	for (unsigned int i = 0; i < 6; ++i)
	{
		channelsActive[i] = false; //True or false depending on if that joint has that degree of freedom
	}	

	_numChildren = 0;
	_parentIndex = -1; //Index of parent. -1 denotes root

	_depth = 0;
	_endsiteIndex = -1;
}

void Bone::setNewChild(unsigned int index)
{
	++_numChildren;
	_childrenIndex.push_back(index);
}

void Bone::setParent(unsigned int index)
{
	_parentIndex = index;
}

void Bone::setDepth(unsigned int depth)
{
	_depth = depth;
}

void Bone::setEndsite(unsigned int index)
{
	_endsiteIndex = index;
}

void Bone::setLocalMatrix(Vector3f rotationVector)
{
	Vector3f scaleVec(1.0f, 1.0f, 1.0f);
	
	localMatrix.makeHomogenous(rotationVector, offset, scaleVec);
}

void Bone::setLocalMatrixV2(Matrix rotMatrix)
{
	Vector3f scaleVec(1.0f, 1.0f, 1.0f);
	localMatrix.makeHomogenousV2(rotMatrix, offset, scaleVec);
}

void Bone::setWorldMatrix(Matrix parentWorld)
{
	worldMatrix = parentWorld.multiply(localMatrix);
}

void Bone::setBindingMatrix(Matrix parentWorld)
{
	bindMatrix = parentWorld.multiply(localMatrix);
}

unsigned int Bone::getDepth()
{
	return _depth;
}

unsigned int Bone::getNumChildren()
{
	return _numChildren;
}

unsigned int Bone::getChildrenIndex(unsigned int index)
{
	return _childrenIndex[index];
}

int Bone::getParent()
{
	return _parentIndex;
}

int Bone::getEndsite()
{
	return _endsiteIndex;
}