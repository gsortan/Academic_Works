
#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Shader.h"
#include "Include.h"
#include "Vector3f.h"


#include <string>

class XY_Coordinate
{
public:
	XY_Coordinate(float _x, float _y, float _u, float _v)
	{ 
		x = _x; 
		y = _y; 
		u = _u; 
		v = _v;
	}

	~XY_Coordinate()
	{
	
	}

	float x, y;
	float u, v;
};

class SpriteAnimation 
{
public:
	SpriteAnimation(void)
	{
		currentFrame = 0;
		doesLoop = true;
	}

	~SpriteAnimation(void)
	{

	}
	
	void nextFrame()
	{
		int numFrames = coords.size();
		++currentFrame;
		if (currentFrame >= numFrames)
		{
			if (doesLoop) 
				currentFrame = 0;
			else currentFrame = numFrames - 1;
		}
	}

	void setLooping(bool loop)
	{
		doesLoop = loop;
	}

	/* each animation has a list of x,y coordinates
	   that can be cycled through */
	std::vector<XY_Coordinate*> coords;
	bool doesLoop;
	int currentFrame;
};

typedef struct _SpriteSheetInfo
{
	unsigned int textureID;
	float width,height;
} SpriteSheetInfo;

typedef struct _SpriteSize
{
	float width, height;
	float normalizedWidth, normalizedHeight;
} SpriteSize;

/* Sprite class
 * - this class takes care of everything
     related to sprites 
	 loading/drawing/setting states etc.
 */ 
class Sprite
{
public:
	Sprite(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimations, int layerIDValue);
	~Sprite(void);

	void loadSpriteSheet(const char *filename);
	void setSpriteFrameSize(int width, int height);
	void setNumberOfAnimations(int num);
	void addSpriteAnimFrame(int animationNumber, int x, int y);
	void addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames);

	GLuint loadImage(const char* theFileName);

	void setInitPos(float x, float y)
	{
		initPosX = x;
		initPosY = y;

		positionX = x;
		positionY = y;
	}

	void setLayerID(int value) 
	{
		layerID = value;
	}

	void setCenter(float x, float y) 
	{
		centerX = x; 
		centerY = y;
	}

	void setPosition(float x, float y) 
	{
		positionX = x; 
		positionY = y;
	}

	void setScale(Vector3f scale)
	{
		_scale = scale;
	}

	void setOrientation(float _theta) 
	{
		theta = _theta;
	}

	float getOrientation() 
	{
		return theta;
	}

	/* drawing */
	virtual void draw();

	void setCurrentAnimation(int anim) 
	{
		currentAnimation = anim;
		if (currentAnimation >= animations.size()) 
			currentAnimation = 0;
	}
	/* update */
	virtual void update();

	void nextFrame()
	{
		animations[currentAnimation] ->nextFrame();
	}

	//Shader stuff
	void shaderParameterHandler(Shader* shader);

	/* sprite info */
	SpriteSize sz;
	float initSizeX;
	float initSizeY;
	SpriteSheetInfo sheet;
	int numberOfAnimations;
	unsigned int currentAnimation;

	/* position/center/orientation */
	float initPosX, initPosY;
	float positionX,positionY;
	float centerX,centerY;
	float theta;

	int mirrorX;

	// which layer this sprite is on, lower is further away, 
	// background is 0, foreground > 0
	int layerID; 

	/* list of animations */
	std::vector<SpriteAnimation*> animations;

private:
	Shader* _vShader;
	Shader* _fShader;

	Vector3f _scale;
};
