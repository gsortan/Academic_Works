
#include "Sprite.h"

/* THE SPRITE CLASS DEFINITION */
Sprite::Sprite(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimation, int layerIDValue)
{
	this ->loadSpriteSheet(spriteSheetFilename.c_str());
	currentAnimation = 0;
	layerID = 0;
	theta = 0;
	mirrorX = 1;
	centerX = centerY = 0;

	setSpriteFrameSize(frameX, frameY);
	setLayerID(layerIDValue);
	setNumberOfAnimations(numOfAnimation);
	addSpriteAnimFrame(0, 0, 0);

	_vShader = new Shader("Vertex_Easy.cg", "vColor");
	//_fShader = new Shader("Fragment_Easy.cg", "fTextureReplace");
	_fShader = new Shader("Fragment_Blur.cg", "nonEdgeDetection"); //For some gay reason this is being gay

	_scale = Vector3f(1.0f, 1.0f, 1.0f);
}

Sprite::~Sprite(void)
{

}

void Sprite::loadSpriteSheet(const char *filename)
{
	char spritePath[99] = "Sprites/"; //Creates a character array of size 99 and stores path
	strcat_s(spritePath, filename); //Adds textureName to texturePath to give full path

	std::cout << "Loading Sprite: " << filename << "." << std::endl;

	sheet.textureID = ilutGLLoadImage((char*) spritePath);
	sheet.width = ilGetInteger(IL_IMAGE_WIDTH);
	sheet.height = ilGetInteger(IL_IMAGE_HEIGHT);
}

void Sprite::setSpriteFrameSize(int width, int height)
{
	sz.width = width;
	sz.height = height;
	sz.normalizedWidth = (float) width / (float) sheet.width;
	sz.normalizedHeight = (float) height / (float) sheet.height;

	centerX = sz.width / 2;
	centerY = sz.height / 2;

	initSizeX = width;
	initSizeY = height;
}

void Sprite::setNumberOfAnimations(int num)
{
	numberOfAnimations = num;
	animations.reserve(num);

	for(int i = 0; i < num; ++i)
	{
		SpriteAnimation *anim = new SpriteAnimation();
		animations.push_back(anim);
	}
}

/*
 * addSpriteAnimFrame()
 *  - this adds a sprite animation frame to the end of the particular animation list
 *  - (x,y) specify the pixel values of the bottom left corner of the frame
 *  - animationNumber specifies which animation (i.e. JUMP, RUN, etc)
 *    you could use enum's for easier coding 
 */
void Sprite::addSpriteAnimFrame(int animationNumber, int x, int y)
{
	float u, v;
	u = (float) x / sheet.width;
	v = (float) y / sheet.height;

	XY_Coordinate *xy = new XY_Coordinate(x, y, u, v);
	animations[animationNumber] ->coords.push_back(xy);
}

void Sprite::addSpriteAnimRow(int animationNumber, float startX, float startY, float spacingX, float spacingY, int numFrames)
{
	float x, y;
	x = startX;
	y = startY;

	for (int i = 0; i < numFrames; ++i)
	{
		x += spacingX;
		y += spacingY;
		addSpriteAnimFrame(animationNumber, x, y);
	}
}

/*
 * draw()
 * - this draws the sprite texture at its current frame of its current animation
 * - it positions the sprite based on the transformation formula:
 *    v' = RotationMatrix*(v-center) + position
 * where position is the bottom left corner of the sprite
 * and v is each corner of the sprite rectangle, v' is the transformed corner
 * and RotationMatrix is defined by the sprite's theta value (counter clockwise)
 */
void Sprite::draw()
{
	/* draw the sprite */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	/* get the texture coordinate from the sprite so we know which frame to draw */
	SpriteAnimation *anim = animations[currentAnimation];
	int currentFrame = anim ->currentFrame;
	float u = anim ->coords[currentFrame] ->u;
	float v = anim ->coords[currentFrame] ->v;

	_vShader ->bindAndEnableShaders();
	_fShader ->bindAndEnableShaders();

	shaderParameterHandler(_vShader);
	shaderParameterHandler(_fShader);

		glBegin(GL_QUADS);
		    glTexCoord2f(u, v);
			glVertex3f(0, 0, 0);
			
			glTexCoord2f(u, v + sz.normalizedHeight);
			glVertex3f(0, sz.height, 0);
			
			glTexCoord2f(u + sz.normalizedWidth, v + sz.normalizedHeight);
			glVertex3f(sz.width, sz.height, 0);
			
			glTexCoord2f(u + sz.normalizedWidth, v);
			glVertex3f(sz.width, 0, 0);
		glEnd();
	
	_vShader ->disableShaders();
	_fShader ->disableShaders();

	glPopMatrix();
	glDisable(GL_BLEND);
}

void Sprite::update()
{
	positionX += 5;
	if (positionX > 800) 
		positionX = 0;
	theta += 1; // increment orientation
}

void Sprite::shaderParameterHandler(Shader* shader)
{
	if (shader ->getFileName() == "Vertex_Easy.cg" 
		|| shader ->getFileName() == "Vertex_Medium.cg"
		|| shader ->getFileName() == "Vertex_Blur.cg") //Vertex Shaders
	{
		cgSetParameter4f(shader ->color, 1.0f, 1.0f, 1.0f, 1.0f); //Hard coding color to white
		cgSetParameter4f(shader ->rotationRow0, _scale.getX(), 0.0f, 0.0f, positionX);
		cgSetParameter4f(shader ->rotationRow1, 0.0f, _scale.getY(), 0.0f, positionY);
		cgSetParameter4f(shader ->rotationRow2, 0.0f, 0.0f, _scale.getZ(), 0.0f);
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

		if (shader ->getShaderName() == "vColor")
		{
		}
		else if (shader ->getShaderName() == "main")
		{
		}
	}
		
	else if (shader ->getFileName() == "Fragment_Easy.cg"
			|| shader ->getFileName() == "Fragment_Medium.cg"
			|| shader ->getFileName() == "Fragment_Blur.cg")
	{
		if (shader ->getShaderName() == "fTextureReplace")
		{
			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sheet.textureID); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, sheet.textureID);	
			cgGLEnableTextureParameter(shader ->texture0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fTextureModulate")
		{
			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sheet.textureID); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, sheet.textureID);	
			cgGLEnableTextureParameter(shader ->texture0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "main" || shader ->getShaderName() == "nonEdgeDetection")
		{
			cgSetParameter1f(shader ->intensity, 1.0f);
			cgSetParameter1f(shader ->size, 1.0f);

			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, sheet.textureID); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, sheet.textureID);	
			cgGLEnableTextureParameter(shader ->texture0);

			glActiveTextureARB(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, sheet.textureID); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture1, sheet.textureID);		
			cgGLEnableTextureParameter(shader ->texture1);			

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	shader ->checkForCgError("enable decal texture");	
}