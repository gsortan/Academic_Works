#include "Quad.h"

Quad::Quad()
{
	initFBO();
}

Quad::~Quad()
{

}

void Quad::initFBO()
{
	_fbo = new FBO();
	_fbo ->initFrameBuffer();


	_vShader = new Shader("Vertex_Easy.cg", "vColor");
	_fShader = new Shader("Fragment_Blur.cg", "main");

	intensity = 1.0f;

	_isShaking = false;
	_shakeTime = 0;
	_shakeTimer = new Timer();
	_offsetX = 0;
	_offsetY = 0;
}

void Quad::setShader(int shader, const char* shaderFile, const char* shaderName)
{
	if (shader == NG_VERTEX_SHADER)
	{
		_vShader = new Shader(shaderFile, shaderName);
	}
	else
	{
		_fShader = new Shader(shaderFile, shaderName);
	}
}

void Quad::shake(unsigned int time, int range, float intensity)
{
	_isShaking = true;
	_shakeTime = time;
	_shakeRange = range;
	_shakeIntensity = intensity;

	_shakeTimer ->start();
}

void Quad::draw()
{
	glMatrixMode(GL_PROJECTION); //Switch it back to camera cause we use the near and far plane
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Enables alpha blending	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //Modulate multiplies color of model with texture
	
	_vShader ->bindAndEnableShaders();
	_fShader ->bindAndEnableShaders();

	shaderParameterHandler(_vShader);
	shaderParameterHandler(_fShader);

	if (_isShaking == true) //Are you shaking?
	{
		if (_shakeTimer ->get(NG_TIMER_SECONDS) < _shakeTime) //If time is not up
		{
			_offsetX = rand() % (_shakeRange * 2) - _shakeRange; //Generates number between -_shakeRange and _shakeRange
			_offsetX *= _shakeIntensity; //Normalizes to make it a smaller number

			_offsetY = rand() % (_shakeRange * 2) - _shakeRange; //Generates number between -2 and 2
			_offsetY *= _shakeIntensity; //Normalizes to make it a smaller number
		}
		else //Time is up
		{
			_isShaking = false;
			_offsetX = 0;
			_offsetY = 0;
		}
	}
	else
	{
		_offsetX = 0;
		_offsetY = 0;
	}

	glBegin(GL_QUADS); //Fuuu glBegin
	glTexCoord2f(0 + _offsetX, 0 + _offsetY);
	glVertex3i(-1, -1, -1); //The z = -1 indicates that it should be mapped to the near plane
	glTexCoord2f(1 + _offsetX, 0 + _offsetY);
	glVertex3i(1, -1, -1); //Z at 1 indicates the far plane
	glTexCoord2f(1 + _offsetX, 1 + _offsetY);
	glVertex3i(1, 1, -1);
	glTexCoord2f(0 + _offsetX, 1 + _offsetY);
	glVertex3i(-1, 1, -1);
	glEnd();

	_vShader ->disableShaders();
	_fShader ->disableShaders();

	glDisable(GL_BLEND);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Quad::draw(Texture &texture)
{	
	_currentTexture[0] = texture;

	draw();	
}

void Quad::draw(Texture &texture0, Texture &texture1)
{	
	_currentTexture[0] = texture0;
	_currentTexture[1] = texture1;

	draw();	
}

void Quad::bindFBO(unsigned int type)
{
	_fbo ->bind(type);
}

void Quad::unbindFBO(unsigned int type)
{
	_fbo ->unbind(type);
}

Texture* Quad::getTexture() //Returns the FBO texture
{
	return _fbo ->get();
}

Texture Quad::getCurrentTexture() //Returns the current texture thats on the quad
{
	return _currentTexture[0];
}

void Quad::shaderParameterHandler(Shader* shader)
{
	if (shader ->getFileName() == "Vertex_Easy.cg" 
		|| shader ->getFileName() == "Vertex_Medium.cg"
		|| shader ->getFileName() == "Vertex_Blur.cg") //Vertex Shaders
	{
		cgSetParameter4f(shader ->color, 1.0f, 1.0f, 1.0f, 1.0f); //Hard coding color to white
		cgSetParameter4f(shader ->rotationRow0, 1.0f, 0.0f, 0.0f, 0.0f); //Hard code to identity
		cgSetParameter4f(shader ->rotationRow1, 0.0f, 1.0f, 0.0f, 0.0f);
		cgSetParameter4f(shader ->rotationRow2, 0.0f, 0.0f, 1.0f, 0.0f);
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	}
		
	else if (shader ->getFileName() == "Fragment_Easy.cg"
			|| shader ->getFileName() == "Fragment_Medium.cg"
			|| shader ->getFileName() == "Fragment_Blur.cg")
	{
		if (shader ->getShaderName() == "fTextureReplace")
		{
			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _fbo ->get() ->get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _currentTexture[0].get());	
			cgGLEnableTextureParameter(shader ->texture0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fTextureModulate")
		{
			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _fbo ->get() ->get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _currentTexture[0].get());	
			cgGLEnableTextureParameter(shader ->texture0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "main" || shader ->getShaderName() == "nonEdgeDetection")
		{
			cgSetParameter1f(shader ->intensity, intensity);
			cgSetParameter1f(shader ->size, 1.0f);

			glActiveTextureARB(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _currentTexture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _currentTexture[0].get());	
			cgGLEnableTextureParameter(shader ->texture0);

			glActiveTextureARB(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _currentTexture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture1, _currentTexture[0].get());		
			cgGLEnableTextureParameter(shader ->texture1);			

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	shader ->checkForCgError("enable decal texture");	
}