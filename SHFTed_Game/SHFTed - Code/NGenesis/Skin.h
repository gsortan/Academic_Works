//Parses and stores skin weights from skin weight files

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Bone.h"
#include "Conversion.h"
#include "Include.h"

#define NG_CHARACTER_SKIN 0
#define NG_CLUB_SKIN 1
#define NG_CROSSBOW_SKIN 2
#define NG_ARCHER_SKIN 3
#define NG_SOLDIER_SKIN 4
#define NG_ENEMYSWORD_SKIN 5
#define NG_HEAVY_SKIN 6
#define NG_SWORD_SKIN 7

class Skin
{
public:
	Skin();
	Skin(const std::string fileName);
	~Skin();

	void initVariables();

	void setJointIndices(const std::vector<Bone> &boneList);
	void setWeightAndJointPointers();
	void setAndSortMeshIndices(const float* indices, const unsigned int &size);

	//MAKE SEPARATE CLASS
	bool isDigit(char &character);
	bool isAlpha(char &character);
	//MAKE SEPARATE CLASS
	
	void load(const std::string fileName);
	void printInfo();

	int *indexPtr;
	GLfloat *weightPtr;

	//Control data is data that is read in directly from the skin weight file
	std::vector<unsigned int> vertexListControl;
	std::vector<std::vector<std::string>> jointListControl;
	std::vector<std::vector<int>> jointIndexListControl; //A vector storing a vector of the joints affecting the vertex
	std::vector<std::vector<float>> skinWeightListControl; //A vector storing a vector of skin weights

	//These are the actual ones we want
	
	std::vector<unsigned int> vertexList;
	std::vector<std::vector<std::string>> jointList;
	std::vector<std::vector<int>> jointIndexList; //A vector storing a vector of the joints affecting the vertex
	std::vector<std::vector<float>> skinWeightList; //A vector storing a vector of skin weights
	std::vector<int> sortedJointIndexList; //A vector storing a vector of the joints affecting the vertex
	std::vector<float> sortedSkinWeightList;

private:
	std::string _SKIN_PATH;

	/*//Control data is data that is read in directly from the skin weight file
	std::vector<unsigned int> _vertexListControl;
	std::vector<std::vector<std::string>> _jointListControl;
	std::vector<std::vector<int>> _jointIndexListControl; //A vector storing a vector of the joints affecting the vertex
	std::vector<std::vector<float>> _skinWeightListControl; //A vector storing a vector of skin weights

	//These are the actual ones we want
	std::vector<unsigned int> _vertexList;
	std::vector<std::vector<std::string>> _jointList;
	std::vector<std::vector<int>> _jointIndexList; //A vector storing a vector of the joints affecting the vertex
	std::vector<std::vector<float>> _skinWeightList; //A vector storing a vector of skin weights*/

	unsigned int _counter;
};