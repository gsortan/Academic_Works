#include "FBO.h"


FBO::FBO()
{
	_bufferWidth = 1280; //Hard coding the viewport size
	_bufferHeight = 720;

	_textureWidth = 1280;
	_textureHeight = 720;

	_colorTexture = new GLuint();
	_depthTexture = new GLuint();
	_texture = new Texture();
}

FBO::~FBO()
{
	glDeleteFramebuffersEXT(1, &_frameBuffer); //Deletes frame buffer
	glDeleteRenderbuffersEXT(1, &_depthBuffer); //Deletes render buffer
}

void FBO::setTextureSize(int width, int height)
{
	_textureWidth = width;
	_textureHeight = height;
}

int FBO::getTextureSize(int choice)
{
	if (choice == WIDTH)
	{
		return _textureWidth;
	}
	else
	{
		return _textureHeight;
	}
}

void FBO::initFrameBuffer(void) 
{  
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	initTexture(); // Initialize our frame buffer texture  	  
	initDepthTexture();
  
	glGenFramebuffersEXT(1, &_frameBuffer); // Generate one frame buffer and store the ID in fbo  
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _frameBuffer); // Bind our frame buffer  
  
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, *_colorTexture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer. to our frame buffer  	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, *_depthTexture, 0);


	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT); // Check that status of our generated frame buffer  

	if (status != GL_FRAMEBUFFER_COMPLETE_EXT) //Checks if frame buffer is good
	{
		std::cerr << "ERROR: FRAME BUFFER IS NOT GOOD" << std::endl;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::initRenderBuffer(void) 
{    
	glGenRenderbuffersEXT(1, &_depthBuffer); // Generate one render buffer and store the ID in fbo_depth  
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _depthBuffer); // Bind the fbo_depth render buffer  
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, _bufferWidth, _bufferHeight); // Set the render buffer storage to be a depth component, with a width and height of the window  
	
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _depthBuffer); // Set the render buffer of this buffer to the depth buffer
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0); // Unbind the render buffer  
}  

void FBO::initTexture(void) 
{ 
	glGenTextures(1, _colorTexture); // Generate one texture  
	glBindTexture(GL_TEXTURE_2D, *_colorTexture); // Bind the texture fbo_texture  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _bufferWidth, _bufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window  

	// Setup the basic texture parameters  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
  
	// Unbind the texture  
	glBindTexture(GL_TEXTURE_2D, 0);  
}  

void FBO::initDepthTexture(void) 
{ 
	glGenTextures(1, _depthTexture); // Generate one texture  
	glBindTexture(GL_TEXTURE_2D, *_depthTexture); // Bind the texture fbo_texture  
  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _bufferWidth, _bufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL); // Create a depth texture with the width and height of our window  

	// Setup the basic texture parameters  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
  
	// Unbind the texture  
	glBindTexture(GL_TEXTURE_2D, 0);  
} 

void FBO::bind(unsigned int type)
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _frameBuffer);
	glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (type == NG_RGBA_TEXTURE)
	{
		glBindTexture(GL_TEXTURE_2D, *_colorTexture);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, *_depthTexture);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void FBO::unbind(unsigned int type)
{	
	if (type == NG_RGBA_TEXTURE)
	{
		_texture ->set(*_colorTexture);
		_texture ->setTextureName("RGBA_FBO"); //You need to adjust nearplane and farplane for this to work
	}
	else
	{
		_texture ->set(*_depthTexture);
		_texture ->setTextureName("DEPTH_FBO"); //You need to adjust nearplane and farplane for this to work
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopAttrib();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBO::initFakeFBO()	
{
	unsigned int* data;		

	data = (unsigned int*) new GLuint[((_bufferWidth * _bufferHeight) * 4 * sizeof(unsigned int))]; //Allocates memory for w x h ints, which are 4 bits
	ZeroMemory(data, ((_textureWidth * _textureHeight) * 4 * sizeof(unsigned int)));	//Clear Storage Memory

	glGenTextures(1, _colorTexture);				
	glBindTexture(GL_TEXTURE_2D, *_colorTexture);			
	glTexImage2D(GL_TEXTURE_2D, GL_DEPTH_COMPONENT24, 4, _bufferWidth, _bufferHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete [] data;
}

void FBO::renderFakeFBO() //Renders To A Texture
{
	glBindTexture(GL_TEXTURE_2D, *_colorTexture);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, _textureWidth, _textureHeight, 0);
	_texture ->set(*_colorTexture);
	_texture ->setTextureName("Frame_Buffer_Texture"); //You need to adjust nearplane and farplane for this to work
}

Texture* FBO::get()
{
	return _texture;
}