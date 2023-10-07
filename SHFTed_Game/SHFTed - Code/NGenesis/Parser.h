//Handles the parsing of directories

#pragma once

#include "Model.h"
#include "Skeleton.h"
#include "Skin.h"
#include "Sprite.h"
#include "Character.h"
#include "Include.h"

#include <vector>

class Parser
{
public:
	Parser();
	~Parser();

	void parseModels(std::vector<Model> &vector, const char* directory);
	void parseModels(std::vector<Model*> &vector, const char* directory);
	void parseTextures(std::vector<Texture> &vector, const char* directory);
	void parseSkeletons(std::vector<Skeleton> &vector, const char* directory);
	void parseDialogue(std::vector<std::string> &vector);
	void parseSkins(std::vector<Skin> &vector, const char* directory);
	void parseSprites(std::vector<Sprite> &vector, const char* directory);

private:
	
};