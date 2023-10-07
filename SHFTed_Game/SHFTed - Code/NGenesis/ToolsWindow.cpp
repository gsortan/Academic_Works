#include "ToolsWindow.h"

ToolsWindow::ToolsWindow()
{
	MAIN_WINDOW_INDEX = 0;

	LEVEL_BUTTON_INDEX = 1;
	ENV_BUTTON_INDEX = 2;
	ENEMIES_BUTTON_INDEX = 3;
	FRIENDLIES_BUTTON_INDEX = 4;
	RIGHT_BUTTON_INDEX = 5;
	LEFT_BUTTON_INDEX = 6;
	PLUS_BUTTON_INDEX = 7;
	MINUS_BUTTON_INDEX = 8;
	RESET_BUTTON_INDEX = 9;

	LEVEL_CAPTION_INDEX = 10;
	ENV_CAPTION_INDEX = 11;
	ENEMIES_CAPTION_INDEX = 12;
	FRIENDLIES_CAPTION_INDEX = 13;

	SIZE_LABEL_INDEX = 14;
	TEXTURE_LABEL_INDEX = 15;

	DISPLAY_LEVEL = 0;
	DISPLAY_ENV = 1;
	DISPLAY_ENEMIES = 2;
	DISPLAY_FRIENDLIES = 3;

	currentDisplay = DISPLAY_LEVEL;

	displayed = false;

	loadSprites();
}

ToolsWindow::~ToolsWindow()
{
}

void ToolsWindow::update() //Updates the stuff drawn on the screen by clearing the draw list and reloading it
{
	clearDrawList(); //Clears the draw list
	addToDrawList(_spriteList[MAIN_WINDOW_INDEX], MAIN_WINDOW_INDEX);
	addToDrawList(_spriteList[LEVEL_BUTTON_INDEX], LEVEL_BUTTON_INDEX);
	addToDrawList(_spriteList[ENV_BUTTON_INDEX], ENV_BUTTON_INDEX);
	addToDrawList(_spriteList[ENEMIES_BUTTON_INDEX], ENEMIES_BUTTON_INDEX);
	addToDrawList(_spriteList[FRIENDLIES_BUTTON_INDEX], FRIENDLIES_BUTTON_INDEX);
	addToDrawList(_spriteList[RESET_BUTTON_INDEX], RESET_BUTTON_INDEX);

	addToDrawList(_spriteList[SIZE_LABEL_INDEX], SIZE_LABEL_INDEX);
	addToDrawList(_spriteList[TEXTURE_LABEL_INDEX], TEXTURE_LABEL_INDEX);
	addToDrawList(_spriteList[RIGHT_BUTTON_INDEX], RIGHT_BUTTON_INDEX);
	addToDrawList(_spriteList[LEFT_BUTTON_INDEX], LEFT_BUTTON_INDEX);
	addToDrawList(_spriteList[PLUS_BUTTON_INDEX], PLUS_BUTTON_INDEX);
	addToDrawList(_spriteList[MINUS_BUTTON_INDEX], MINUS_BUTTON_INDEX);

	if (currentDisplay == DISPLAY_LEVEL)
	{	
		addToDrawList(_spriteList[LEVEL_CAPTION_INDEX], LEVEL_CAPTION_INDEX);		
	}
	else if (currentDisplay == DISPLAY_ENV)
	{
		addToDrawList(_spriteList[ENV_CAPTION_INDEX], ENV_CAPTION_INDEX);	
	}
	else if (currentDisplay == DISPLAY_ENEMIES)
	{
		addToDrawList(_spriteList[ENEMIES_CAPTION_INDEX], ENEMIES_CAPTION_INDEX);	
	}
	else if (currentDisplay == DISPLAY_FRIENDLIES)
	{
		addToDrawList(_spriteList[FRIENDLIES_CAPTION_INDEX], FRIENDLIES_CAPTION_INDEX);	
	}
}

void ToolsWindow::draw()
{
	for (unsigned int i = 0; i < _spriteDrawList.size(); ++i)
	{
		_spriteDrawList[i] ->draw();
	}
}

void ToolsWindow::loadSprites() //Loads the sprites we need. God this function is so damn dirty.
{
	loadSprite("Tools Window/blank.png", 400, 720, 1, 0, 0, 0);

	loadSprite("Tools Window/levelButton.jpg", 64, 64, 1, 1, 0, 720 - 64); //The 720 is the height of the stage
	loadSprite("Tools Window/envButton.jpg", 64, 64, 1, 1, 0, 720 - 64 * 2); //The 64 is the height of the button
	loadSprite("Tools Window/enemiesButton.jpg", 64, 64, 1, 1, 0, 720 - 64 * 3); //The * 3 represents how far down it is
	loadSprite("Tools Window/friendliesButton.jpg", 64, 64, 1, 1, 0, 720 - 64 * 4);
	loadSprite("Tools Window/rightButton.jpg", 64, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX + 128 / 2, 64 * 2); //128 is size of the labels
	loadSprite("Tools Window/leftButton.jpg", 64, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 128 / 2 - 64, 64 * 2);
	loadSprite("Tools Window/plusButton.jpg", 64, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX + 128 / 2, 64);
	loadSprite("Tools Window/minusButton.jpg", 64, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 128 / 2 - 64, 64);
	loadSprite("Tools Window/resetButton.jpg", 64, 64, 1, 1, 0, 0);

	loadSprite("Tools Window/levelCaption.jpg", 256, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 256 / 2, 720 - 64 * 2); //The 256 is the length of this sprite
	loadSprite("Tools Window/envCaption.jpg", 256, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 256 / 2, 720 - 64 * 2);
	loadSprite("Tools Window/enemiesCaption.jpg", 256, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 256 / 2, 720 - 64 * 2);
	loadSprite("Tools Window/friendliesCaption.jpg", 256, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 256 / 2, 720 - 64 * 2);

	loadSprite("Tools Window/sizeLabel.jpg", 128, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 128 / 2, 64);
	loadSprite("Tools Window/textureLabel.jpg", 128, 64, 1, 1, _spriteList[MAIN_WINDOW_INDEX].centerX - 128 / 2, 64 * 2);
}

void ToolsWindow::loadSprite(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimations, int layerIDValue, float posX, float posY) //This function is kinda dirty.
{
	Sprite* sprite = new Sprite(spriteSheetFilename, frameX, frameY, numOfAnimations, layerIDValue);
	sprite ->setInitPos(posX, posY);
	_spriteList.push_back(*sprite);
}

int ToolsWindow::clickHandler(float mouseX, float mouseY) //Essentially checks whether or not something is being clicked and returns the index if it is, or -1 if its not
{
	//This is going to assume that nothing overlaps except for obviously the main window and it's elements
	//It is essentially going to go down the list and when it finds something, it will return
	//It goes down the list since the main window will be element 0, and everything is placed on top of it

	mouseY = abs(mouseY - 720); //Needs to make sure we switch the origin of the y to bottom instead of top

	for (int i = _spriteDrawList.size() - 1; i >= 0; --i)
	{
		if ((_spriteDrawList[i] ->positionX <= mouseX) && (_spriteDrawList[i] ->positionX + _spriteDrawList[i] ->sz.width >= mouseX)) //Checks for X collision
		{
			if ((_spriteDrawList[i] ->positionY <= mouseY) && (_spriteDrawList[i] ->positionY + _spriteDrawList[i] ->sz.height >= mouseY)) //Checks for Y collision
			{
				return *_spriteIndexDrawList[i];
			}
		}
	}

	return -1;
}

void ToolsWindow::addToDrawList(Sprite &sprite, unsigned int &index)
{
	_spriteDrawList.push_back(&sprite);
	_spriteIndexDrawList.push_back(&index);
}

void ToolsWindow::clearDrawList()
{
	_spriteDrawList.clear();
	_spriteIndexDrawList.clear();
}