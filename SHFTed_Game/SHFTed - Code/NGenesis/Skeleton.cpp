#include "Skeleton.h"

Skeleton::Skeleton()
{
	initVariables();
}

Skeleton::Skeleton(const std::string fileName)
{
	_frame = 0.0f;
	initVariables();
	load(fileName);
}

Skeleton::~Skeleton()
{
}

void Skeleton::initVariables()
{
	_SKELETON_PATH = "Skeletons/";

	_numFrames = 0;
	_frameTime = 0.0f;
}

std::vector<Bone> Skeleton::getBoneList()
{
	return boneList;
}

std::vector<Bone>* Skeleton::getBones()
{
	return &boneList; 
}

Bone Skeleton::getMiddleOfRightHand()
{
	for (unsigned int i = 0; i < boneList.size(); ++i)
	{
		if (std::string::npos != boneList[i].name.find("RightHandMiddle1"))
		{
			return boneList[i];
		}
	}
}

void Skeleton::playAnimation(float t)
{	
	Matrix tempMatrix;
	float tempAngle;

	float originalFrame = t * _frameTime;

	//Frame interpolating from
	_frame = floor(t * _frameTime); 

	float interpolationValue = originalFrame - _frame;

	//Sets up motion data in ZYX rotation order for hip joint
	rotation.set(motionData.at(_frame).at(4), motionData.at(_frame).at(2), motionData.at(_frame).at(3));
	boneList.at(0).offset.set(motionData.at(_frame).at(0), motionData.at(_frame).at(1), motionData.at(_frame).at(2));

	boneList.at(0).setLocalMatrix(rotation);
	boneList.at(0).worldMatrix = boneList.at(0).localMatrix; 

	//set local rotationValues 
	for (unsigned int i = 1; i < boneList.size(); ++i)
	{
		tempMatrix.setIdentity();

		//Quaternion interpolation 
		tempAngle = orientations.at(_frame).at(i).dot(orientations.at(_frame + 1).at(i));
		_slerpPose = orientations.at(_frame).at(i).slerp(tempAngle, orientations.at(_frame + 1).at(i), interpolationValue);
	
		tempMatrix = Conversion::quaternionToMatrix(_slerpPose);

		boneList.at(i).setLocalMatrixV2(tempMatrix);	
	}

	boneList.at(0).worldMatrix = boneList.at(0).localMatrix; 
	//compute global positions for world matrix

	for (unsigned int i = 1; i < boneList.size(); ++i) /*don't need to -1 since I need world matrix*/
	{
		if (boneList.at(i).getParent() != -1)
		{
			boneList.at(i).setWorldMatrix(boneList.at(boneList.at(i).getParent()).worldMatrix);
		}
	}
}

/*Draws skeleton for debugging purposes*/
void Skeleton::drawSkeleton()
{
	int parentBone = 0;
	int bone = 0;
	int parentIndex;

	Vector3f translational;
	Vector3f pos2;

	glPushMatrix();
	glLineWidth(30.0f);

	while (bone < boneList.size())
	{
		parentBone = bone;

		while (parentBone != 0)
		{
			glBegin(GL_LINES);

			glColor3f(1.0f, 0.0f, 0.0f);
			pos2 = boneList.at(parentBone).worldMatrix.getTranslationVector();
			parentIndex = boneList.at(parentBone).getParent();

			translational = boneList.at(parentIndex).worldMatrix.getTranslationVector();
			glVertex3f(pos2.getX(), pos2.getY(), pos2.getZ());
			glVertex3f(translational.getX(), translational.getY(), translational.getZ());

			parentBone = boneList.at(parentBone).getParent();
		}

		glEnd();
		++bone;
	}

	glPopMatrix();
}

void Skeleton::setBindingPose()
{
	Matrix identityM;
	Matrix tempRot;
	identityM.setIdentity();

	for (unsigned int i = 0; i < boneList.size(); ++i)
	{
		boneList.at(i).localMatrix.setIdentity();
		boneList.at(i).localMatrix.setElement(3, boneList.at(i).offset.getX());
		boneList.at(i).localMatrix.setElement(7, boneList.at(i).offset.getY());
		boneList.at(i).localMatrix.setElement(11, boneList.at(i).offset.getZ());
	}

	boneList.at(0).worldMatrix = boneList.at(0).localMatrix;
	boneList.at(0).bindMatrix = boneList.at(0).worldMatrix;

	for (int i = 1; i < boneList.size(); ++i)
	{
		if (boneList.at(i).getParent() != -1)
		{
			boneList.at(i).setWorldMatrix(boneList.at(boneList.at(i).getParent()).worldMatrix);
			boneList.at(i).bindMatrix.setIdentity();
			boneList.at(i).bindMatrix = boneList.at(i).worldMatrix;
		}
	}

	for (unsigned int i = 1; i < boneList.size(); ++i)
	{
		if (boneList.at(i).getParent() != -1)
		{
			boneList.at(i).setWorldMatrix(boneList.at(boneList.at(i).getParent()).worldMatrix);
		}
	}
}

void Skeleton::blendAnimation(float t,Skeleton *otherAnimation)
{
	int inc = 1;// incremental value
	Matrix tempMatrix;
	float tempAngle;

	float originalFrame = t * _frameTime;

	//Frame interpolating from
	_frame = floor(t * _frameTime); 

	float interpolationValue = originalFrame - _frame;

	//Sets up motion data in ZYX rotation order for hip joint
	rotation.set(motionData.at(_frame).at(4), motionData.at(_frame).at(2), motionData.at(_frame).at(3));
	boneList.at(0).offset.set(motionData.at(_frame).at(0), motionData.at(_frame).at(1), motionData.at(_frame).at(2));
	boneList.at(0).setLocalMatrix(rotation);
	boneList.at(0).worldMatrix = boneList.at(0).localMatrix; 

	//set local rotationValues 
	for (int i = 1; i < boneList.size() - 1; ++i)//Added extra joint hence - 1
	{
		tempMatrix.setIdentity();
		//Quaternion interpolation 
		tempAngle = orientations.at(_frame).at(i).dot(otherAnimation ->orientations.at(_frame).at(i));
		_slerpPose = orientations.at(_frame).at(i).slerp(tempAngle,otherAnimation ->orientations.at(_frame).at(i), interpolationValue);
		_slerpPose.normalize();
		tempMatrix = Conversion::quaternionToMatrix(_slerpPose);

		boneList.at(i).setLocalMatrixV2(tempMatrix);
	}

	boneList.at(0).worldMatrix = boneList.at(0).localMatrix; 
	//compute global positions for world matrix
	for (unsigned int i = 1; i < boneList.size(); ++i) /*don't need to -1 since I need world matrix*/
	{
		if (boneList.at(i).getParent() != -1)
		{
			boneList.at(i).setWorldMatrix(boneList.at(boneList.at(i).getParent()).worldMatrix);
		}
	}
}

void Skeleton::setupQuaternions()
{
	int inc = 1;
	Quaternion rotateX;
	Quaternion rotateY;
	Quaternion rotateZ;
	Quaternion result;

	for (unsigned int j = 0; j < _numFrames; j++)
	{
		std::vector<Quaternion> tempOrientation;

		for (unsigned int i = 0; i < boneList.size(); i++)
		{
			rotateZ.createRotationQ(motionData.at(j).at(2 + inc), 2);
			rotateX.createRotationQ(motionData.at(j).at(4 + inc), 1);
			rotateY.createRotationQ(motionData.at(j).at(3 + inc), 0);

			result = rotateZ.multiply(rotateY);
			result = result.multiply(rotateX);

			result.normalize();
		    inc += 6;

			tempOrientation.push_back(result);		
		}

		orientations.push_back(tempOrientation);
		inc = 1;
	}
}

//Initializes skeleton matrix
void Skeleton::setSkeletonMatrix()
{
	Matrix combined;
	Matrix inverseBindMatrix;
	tempBoneList.clear();
	
	for (unsigned int j = 0; j < boneList.size(); j++)
	{
		combined.setIdentity();
		inverseBindMatrix.setIdentity();
		inverseBindMatrix = boneList.at(j).bindMatrix.getInverse();
		
		combined = boneList.at(j).worldMatrix.multiply(inverseBindMatrix);

		for (unsigned int i = 0; i < 16; i++)
		{
			tempBoneList.push_back(combined.getElement(i));
		}
	}

	maxMsize = tempBoneList.size();
	this ->skeletonMatrix = new float[maxMsize];

	for (unsigned int i = 0; i < maxMsize; i++)
	{
		this ->skeletonMatrix[i] = tempBoneList.at(i);
	}
}

void Skeleton::pushEndJoint()
{
	Bone dummy;
	dummy = getMiddleOfRightHand();
	boneList.push_back(dummy);
}

/*Used to update full skeleton matrix*/
void Skeleton::allocateSkeletonMatrix()
{
	tempBoneList.clear();
	Matrix combined;
	Matrix inverseBindMatrix;

	for (unsigned int j = 0; j < boneList.size(); j++)
	{
		combined.setIdentity();
		inverseBindMatrix.setIdentity();
		inverseBindMatrix = boneList.at(j).bindMatrix.getInverse();
		combined = inverseBindMatrix.multiply(boneList.at(j).worldMatrix);
		combined = boneList.at(j).worldMatrix.multiply(inverseBindMatrix);

		for (int i = 0; i < 16; i++)
		{
			tempBoneList.push_back(combined.getElement(i));
		}
	}

	for (unsigned int i = 0; i < maxMsize; i++)
	{
		this ->skeletonMatrix[i] = tempBoneList.at(i);
	}
}

unsigned int Skeleton::getNumFrames()
{
	return _numFrames;
}

float Skeleton::getFrameTime()
{
	return _frameTime;
}

void Skeleton::load(const std::string fileName)
{
	std::cout << "Loading Skeleton: " << fileName << "." << std::endl;
	
	std::string keyword; //Keyword used for comparisons
	std::ifstream file; //Creates an input stream of the file
	file.open(_SKELETON_PATH + fileName); //If found, stores information in the ifstream

	bool loadingHierarchy = true; //If this is true it's in skeleton mode, otherwise it's in animation mode
	bool isEndSite = false; //Checks if the current offset is an endSite
	unsigned int currentDepth = 0;

	Bone* tempBone;	
	float tempFloat;
	std::string tempString;
	Vector3f tempEndSite;

	if (!file.fail())
	{
		while (file.good())
		{
			if ((loadingHierarchy) && (file >> keyword))
			{
				if (keyword == "ROOT")
				{
					tempBone = new Bone();
					file >> tempBone ->name;
					tempBone ->setDepth(0); //Root is always depth 0
				}
				else if (keyword == "JOINT")
				{
					boneList.push_back(*tempBone); //Stores previous bone before moving on
					++currentDepth; //We are one level lower now

					tempBone = new Bone(); //Clears the bone
					file >> tempBone ->name; //Stores name
					tempBone ->setDepth(currentDepth);

					for (int i = boneList.size() - 1; i >= 0; --i)
					{
						if (boneList[i].getDepth() == currentDepth - 1) //Looks for the closest bone that is one level above
						{
							tempBone ->setParent(i); //That bone is now the parent
							boneList[i].setNewChild(boneList.size()); //That bone now has a new child
							break;
						}
					}
				}
				else if (keyword == "OFFSET")
				{
					if (isEndSite == false)
					{
						file >> tempFloat;
						tempBone ->offset.setX(tempFloat);

						file >> tempFloat;
						tempBone ->offset.setY(tempFloat);

						file >> tempFloat;
						tempBone ->offset.setZ(tempFloat);
					}
					else
					{
						file >> tempFloat;
						tempEndSite.setX(tempFloat);

						file >> tempFloat;
						tempEndSite.setY(tempFloat);

						file >> tempFloat;
						tempEndSite.setZ(tempFloat);
						
						_endSiteList.push_back(tempEndSite);
						isEndSite = false; //Done with the endSite
					}
				}
				else if (keyword == "CHANNELS")
				{
					file >> tempBone ->numChannels;

					std::string temp; //Temp string to hold current line
					std::getline(file, temp); //Stores info in temp
					std::stringstream line(temp); //Creates a variable line that has the value of temp

					while (line.good()) //As long as the line is fine
					{
						line >> tempString; //Stores whatever channel it's called and deals with it
						
						if (tempString == "Xposition") //Dealing with it, one if statement at a time
						{
							tempBone ->channelsActive[NG_X_POSITION] = true;
						}
						else if (tempString == "Yposition")
						{
							tempBone ->channelsActive[NG_Y_POSITION] = true;
						}
						else if (tempString == "Zposition")
						{
							tempBone ->channelsActive[NG_Z_POSITION] = true;
						}
						else if (tempString == "Zrotation")
						{
							tempBone ->channelsActive[NG_Z_ROTATION] = true;
						}
						else if (tempString == "Yrotation")
						{
							tempBone ->channelsActive[NG_Y_ROTATION] = true;
						}
						else if (tempString == "Xrotation")
						{
							tempBone ->channelsActive[NG_X_ROTATION] = true;
						}
					}
				}
				else if (keyword == "End") //For "End Site"
				{
					++currentDepth; //We have to go forward one in depth because the end site has brackets too
					isEndSite = true;
				}
				else if (keyword == "}") //If it sees a closing bracket, we're going back up the levels
				{
					--currentDepth;
				}
				else if (keyword == "MOTION")
				{
					boneList.push_back(*tempBone); //Stores previous bone before moving on

					for (int i = boneList.size() - 1; i >= 0; --i)
					{
						if (boneList[i].getDepth() == currentDepth - 1) //Looks for the closest bone that is one level above
						{
							tempBone ->setParent(i); //That bone is now the parent
							boneList[i].setNewChild(boneList.size()); //That bone now has a new child
						}
					}

					loadingHierarchy = false; //Moving onto animations now

					file >> tempString; //"Frames:"
					file >> _numFrames;

					file >> tempString; //"Frame"
					file >> tempString; //"Time:"
					file >> _frameTime;
				}
			}
			else //Motion
			{
				std::string temp; //Temp string to hold current line
				std::getline(file, temp); //Stores info in temp
				std::stringstream line(temp); //Creates a variable line that has the value of temp

				std::vector<float> tempMotion;

				while (line.good())
				{
					line >> tempFloat;
					tempMotion.push_back(tempFloat);
				}

				if (tempMotion.size() > 3) //Store only if the size is greater than 3. Arbitary number is arbitary.
				{
					motionData.push_back(tempMotion); //Stores the motion data
				}
			}
		}
	}
	else //I like exiting the program if we cant load something in
	{
		std::cerr << "ERROR - CANNOT OPEN SKELETON: " << fileName << "." << std::endl;
		system("pause");
		exit(1);
	}

	file.close();	
	setupQuaternions();
}

void Skeleton::printInfo() 
{
	std::cout << "Skeleton with root name: " << boneList[NG_ROOT_INDEX].name << std::endl;
	std::cout << "Contains " << boneList.size() << " bones." << std::endl;

	for (unsigned int i = 0; i < boneList.size(); ++i) //Prints every bone's name
	{
		std::cout << i << ") " << boneList[i].name;

		if (boneList[i].getNumChildren() != 0)
		{
			std::cout << " with child ";

			for (unsigned int a = 0; a < boneList[i].getNumChildren(); ++a) //Finds out how many children it has
			{
				std::cout << boneList[boneList[i].getChildrenIndex(a)].name; //Prints every child's name

				if (a != boneList[i].getNumChildren() - 1)
				{
					std::cout << ", ";
				}
			}
		}

		std::cout << std::endl;
	}
}