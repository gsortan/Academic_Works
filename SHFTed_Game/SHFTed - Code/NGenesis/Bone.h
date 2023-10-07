#pragma once

#include "Vector3f.h"
#include "Matrix.h"
#include <string>
#include <vector>

class Bone
{
public:
	Bone();
	~Bone();

	void initVariables();

	void setNewChild(unsigned int index);
	void setParent(unsigned int index);
	void setDepth(unsigned int depth);
	void setEndsite(unsigned int index);

	void setLocalMatrix(Vector3f rotationVector);
	void setWorldMatrix(Matrix parentWorld);
	void setLocalMatrixV2(Matrix rotMatrix);
	void setBindingMatrix(Matrix parentWorld);

	unsigned int getDepth();	
	unsigned int getNumChildren();
	unsigned int getChildrenIndex(unsigned int index);
	int getParent();
	int getEndsite();

	
	std::string name;

	Vector3f offset;

	Matrix localMatrix;
	Matrix worldMatrix;
	Matrix bindMatrix; 
	Matrix bindLMatrix;

	unsigned int numChannels;
	bool channelsActive[6]; //True or false depending on if that joint has that degree of freedom

private:
	unsigned int _numChildren;
	std::vector<unsigned int> _childrenIndex; //Vector to store index of child/children. -1 denotes leaf
	int _parentIndex; //Index of parent. -1 denotes root
	int _endsiteIndex; //-1 means no end site, anything else means it is currently a "parent" of the respective endsite

	unsigned int _depth; //Deals with how far down the chain it is
};