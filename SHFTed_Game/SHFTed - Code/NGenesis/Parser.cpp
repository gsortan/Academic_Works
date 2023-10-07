#include "Parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

void Parser::parseModels(std::vector<Model> &vector, const char* directory)
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (strstr(ent ->d_name, ".obj") != NULL//Checks whether or not the file name contains .obj
			{
				Model tempModel = Model(directory, ent ->d_name, NG_OBJ); //Creates a temporary model
				vector.push_back(tempModel); //Adds to model list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}

void Parser::parseModels(std::vector<Model*> &vector, const char* directory)
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (strstr(ent ->d_name, ".obj") != NULL) //Checks whether or not the file name contains .obj
			{
				Model* tempModel = new Model(directory, ent ->d_name, NG_OBJ); //Creates a temporary model
				vector.push_back(tempModel); //Adds to model list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}

void Parser::parseTextures(std::vector<Texture> &vector, const char* directory)
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (strstr(ent ->d_name, ".jpg") != NULL || strstr(ent ->d_name, ".png") != NULL || strstr(ent ->d_name, ".tif") != NULL) //Checks whether or not it's a png or jpg
			{
				Texture tempTexture = Texture(ent ->d_name); //Creates a temporary texture
				vector.push_back(tempTexture); //Adds to texture list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}

void Parser::parseSkeletons(std::vector<Skeleton> &vector, const char* directory)
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (strstr(ent ->d_name, ".bvh") != NULL) //Checks whether or not it's a bvh file
			{
				Skeleton tempSkeleton = Skeleton(ent ->d_name); //Creates a temporary skeleton
				vector.push_back(tempSkeleton); //Adds to list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}

void Parser::parseDialogue(std::vector<std::string> &vector) //Parses the dialogue
{
	std::ifstream file; //Creates an input stream of the file
	file.open("Dialogue/Dialogue.txt"); //If found, stores information in the ifstream

	do
	{
		std::string temp; //Temp string to hold current line
		std::getline(file, temp); //Stores info in temp
		vector.push_back(temp);
	} while (!file.eof());

	file.close();
}

void Parser::parseSkins(std::vector<Skin> &vector, const char* directory) //Parses all the skin weights
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (strstr(ent ->d_name, ".txt") != NULL) //Checks whether or not it's a text file
			{
				Skin tempSkin = Skin(ent ->d_name); //Creates a temporary skin
				vector.push_back(tempSkin); //Adds to list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}

void Parser::parseSprites(std::vector<Sprite> &vector, const char* directory)
{
	DIR *dir; //DIR is a dirent file. See the readme in the Dirent folder
	struct dirent *ent;
	dir = opendir(directory);

	if (dir != NULL) //If the directory exists
	{
		while ((ent = readdir (dir)) != NULL) //Not exactly sure. Looks like it's check to see if a file exists
		{
			if (strstr(ent ->d_name, ".jpg") != NULL || strstr(ent ->d_name, ".png") != NULL) //Checks whether or not it's an image file
			{
				Sprite tempSprite = Sprite(ent ->d_name, 21, 20, 1, 0); //Creates a temporary skin
				vector.push_back(tempSprite); //Adds to list
			}
		}

		closedir (dir); //Closes the directory
	} 
	else 
	{
		std::cerr << "ERROR - COULD NOT OPEN DIRECTORY" << std::endl;
	}
}