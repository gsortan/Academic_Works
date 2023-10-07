#pragma once

#include "Shader.h"
#include "FBO.h"
#include "Timer.h"

class Quad
{
public:
	Quad();
	~Quad();

	void initFBO();
	void draw();
	void draw(Texture &texture);
	void draw(Texture &texture0, Texture &texture1);
	void bindFBO(unsigned int type);
	void unbindFBO(unsigned int type);
	Texture* getTexture();
	Texture getCurrentTexture();

	void setShader(int shader, const char* shaderFile, const char* newShader);

	void shake(unsigned int time, int range, float intensity);

	void shaderParameterHandler(Shader* shader);

	float intensity;

private:
	
	Texture _currentTexture[2];

	FBO* _fbo;
	Shader* _vShader;
	Shader* _fShader;

	bool _isShaking;
	unsigned int _shakeTime;
	Timer* _shakeTimer;
	int _shakeRange;
	float _shakeIntensity;

	float _offsetX;
	float _offsetY;
};