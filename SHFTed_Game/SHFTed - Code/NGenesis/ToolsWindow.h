//This class is used to control the tools window and determine what needs to be displayed and where

#pragma once
#include "Sprite.h"
#include <math.h>
#include <vector>
#include <string>

#define PI 3.145159 //Pie

class ToolsWindow
{
public:
	ToolsWindow();
	~ToolsWindow();
	void update();
	void draw();
	void loadSprites();
	void loadSprite(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimations, int layerIDValue, float posX, float posY);
	int clickHandler(float mouseX, float mouseY);
	void addToDrawList(Sprite &sprite, unsigned int &index);
	void clearDrawList();

	unsigned int MAIN_WINDOW_INDEX;

	unsigned int LEVEL_BUTTON_INDEX;
	unsigned int ENV_BUTTON_INDEX;
	unsigned int ENEMIES_BUTTON_INDEX;
	unsigned int FRIENDLIES_BUTTON_INDEX;
	unsigned int RIGHT_BUTTON_INDEX;
	unsigned int LEFT_BUTTON_INDEX;
	unsigned int PLUS_BUTTON_INDEX;
	unsigned int MINUS_BUTTON_INDEX;
	unsigned int RESET_BUTTON_INDEX;

	unsigned int LEVEL_CAPTION_INDEX;
	unsigned int ENV_CAPTION_INDEX;
	unsigned int ENEMIES_CAPTION_INDEX;
	unsigned int FRIENDLIES_CAPTION_INDEX;

	unsigned int SIZE_LABEL_INDEX;
	unsigned int TEXTURE_LABEL_INDEX;

	unsigned int DISPLAY_LEVEL;
	unsigned int DISPLAY_ENV;
	unsigned int DISPLAY_ENEMIES;
	unsigned int DISPLAY_FRIENDLIES;

	unsigned int currentDisplay;
	bool displayed;
	
private:
	std::vector<Sprite*> _spriteDrawList; //Vector containing sprites to be drawn
	std::vector<unsigned int*> _spriteIndexDrawList; //Vector holding the indicies of the spirtes being drawn
	std::vector<Sprite> _spriteList; //Vector containing all our sprites
};
