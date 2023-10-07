//Pretty much just the environments and enemies

#pragma once

#include "Model.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();

	void reloadLevel();
	void loadNextlevel();
	void unloadLevel();
	void loadLevel();

	void draw(); //Draws all the stuff in the level

private:
	unsigned int _currentLevel;
	std::vector<Model> _platformList; //Vector storing the platforms used for collision detection in our level
	std::vector<Model> _interactablesList; //Vector containing the stuff we can interact with, like potions
};