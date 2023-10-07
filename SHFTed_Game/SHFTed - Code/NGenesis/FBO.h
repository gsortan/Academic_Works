//Frame Buffer Objects

#pragma once

#include "Texture.h"
#include "Include.h"

#define WIDTH 0
#define HEIGHT 1

#define NG_RGBA_TEXTURE 0
#define NG_DEPTH_TEXTURE 1

class FBO
{
public:
	FBO();
	~FBO();

	void setTextureSize(int width, int height);
	int getTextureSize(int choice);

	void initFrameBuffer();
	void initRenderBuffer();
	void initTexture();
	void initDepthTexture();
	void bind(unsigned int type);
	void unbind(unsigned int type);

	void initFakeFBO();
	void renderFakeFBO();

	Texture* get();

private:
	unsigned int _bufferWidth;
	unsigned int _bufferHeight;

	unsigned int _textureWidth;
	unsigned int _textureHeight;

	GLuint _frameBuffer;
	GLuint _depthBuffer;

	//Used for fake stuff	
	GLuint* _colorTexture;
	GLuint* _depthTexture;
	Texture* _texture;
};