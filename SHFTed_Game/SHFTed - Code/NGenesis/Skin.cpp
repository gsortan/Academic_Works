#include "Skin.h"

Skin::Skin()
{
	initVariables();
}

Skin::Skin(const std::string fileName)
{
	initVariables();
	load(fileName);
}

Skin::~Skin()
{
}

void Skin::initVariables()
{
	_SKIN_PATH = "Skin Weights/";

	_counter = 0;
}

void Skin::setJointIndices(const std::vector<Bone> &boneList) //Maps the joints to their Indices. Holy inefficient batman.
{
	std::vector<int> tempIntV;

	for (unsigned int a = 0; a < jointListControl.size(); ++a)
	{
		tempIntV.clear();

		for (unsigned int b = 0; b < jointListControl[a].size(); ++b)
		{
			if (jointListControl[a].at(b) != "gg")
			{
				for (unsigned int c = 0; c < boneList.size(); ++c)
				{
					if (jointListControl[a].at(b) == boneList[c].name)
					{
						tempIntV.push_back(c);
						break;
					}
				}
			}	
			else
			{
				tempIntV.push_back(-1);
			}
		}

		jointIndexListControl.push_back(tempIntV);
	}
}

void Skin::setWeightAndJointPointers()
{

	for (unsigned int j = 0; j < skinWeightList.size(); ++j)
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			sortedSkinWeightList.push_back(skinWeightList.at(j).at(i));
		}
	}

	int maxSize = sortedSkinWeightList.size();
	weightPtr = new float[maxSize];

	for (unsigned int i = 0; i < maxSize; ++i)
	{
		weightPtr[i] = sortedSkinWeightList.at(i);
	}

	for (unsigned int j = 0; j < jointIndexList.size(); ++j)
	{
		for (unsigned int i = 0; i < jointIndexList[j].size(); ++i)
		{			
			sortedJointIndexList.push_back(jointIndexList.at(j).at(i));
		}
	}

	int maxSize2 = sortedJointIndexList.size();
	indexPtr = new int[maxSize2];

	for (unsigned int i = 0; i < maxSize2; ++i)
	{
		indexPtr[i] = sortedJointIndexList.at(i);

	}
}

void Skin::setAndSortMeshIndices(const float* indices, const unsigned int &size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		vertexList.push_back(vertexListControl[indices[i]]);		
		jointIndexList.push_back(jointIndexListControl[indices[i]]);
		skinWeightList.push_back(skinWeightListControl[indices[i]]);
	}
}

bool Skin::isDigit(char &character)
{
	if (character >= 48 && character <= 57)
	{
		return true;
	}

	return false;
}

bool Skin::isAlpha(char &character)
{
	if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
	{
		return true;
	}

	return false;
}

void Skin::load(const std::string fileName)
{
	std::cout << "Loading Skin: " << fileName << "." << std::endl;
	
	std::string keyword; //Keyword used for comparisons
	std::ifstream file; //Creates an input stream of the file
	file.open(_SKIN_PATH + fileName); //If found, stores information in the ifstream

	char tempChar;
	unsigned int tempUInt;
	float tempFloat;
	std::vector<unsigned int> tempUIntV;
	std::vector<float> tempFloatV;
	std::vector<std::string> tempStringV;
	std::string tempString; //Temp string to hold current line
	std::string temp; //Temp string to hold current line

	if (!file.fail())
	{
		while (file.good() && !file.eof())
		{
			std::getline(file, temp);
			std::stringstream line(temp); //Creates a variable line that has the value of temp
			
			if ((temp.size() >= 3) && (temp[1] == '.')) //If the number is a float. The second one is always a . because it's between 0 - 1. Lowest it can be is 1.0, so three.
			{
				tempFloatV.clear();

				while (line.good())
				{
					line >> tempFloat;
					line >> tempChar; 
					tempFloatV.push_back(tempFloat);
				}

				while (tempFloatV.size() != 4) //Pads the internal array so theres always four
				{
					tempFloatV.push_back(-1);
				}

				skinWeightListControl.push_back(tempFloatV);
			}
			else if (isAlpha(temp[0])) //If alphabet character, then it must be a name
			{
				tempStringV.clear();

				while (line.good())
				{
					line >> tempString;
					tempStringV.push_back(tempString);
				}

				while (tempStringV.size() != 4) //Pads the internal array so theres always four
				{
					tempStringV.push_back("gg");
				}

				jointListControl.push_back(tempStringV);
			}
			else //Everything else
			{
				line >> tempUInt;
				vertexListControl.push_back(tempUInt);
			}
		}
	}
	else //I like exiting the program if we cant load something in
	{
		std::cerr << "ERROR - CANNOT OPEN SKIN: " << fileName << "." << std::endl;
		system("pause");
		exit(1);
	}

	file.close();	
}

void Skin::printInfo()
{
	for (unsigned int i = 0; i < jointIndexListControl.size(); ++i)
	{
		for (unsigned int a = 0; a < jointIndexListControl[i].size(); ++a)
		{
			std::cout << jointIndexListControl[i].at(a) << " ";
		}

		std::cout << std::endl;
	}
}