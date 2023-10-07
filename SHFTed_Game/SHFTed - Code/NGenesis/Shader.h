#pragma once

#include "Include.h"

#include <iostream>
#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <string.h>

#define NG_VERTEX_SHADER 0
#define NG_FRAGMENT_SHADER 1

class Shader
{
public:
	Shader();
	Shader(const char* shaderFileName, const char* shaderName);
	~Shader();

	void checkForCgError(const char* situation);
	void initCg();
	void bindAndEnableShaders();
	void disableShaders();
	void initAndSetParameters();
	const char* getFileName();
	const char* getShaderName();

	void setLightMatrix();

	
	CGparameter color;
	CGparameter rotationRow0, rotationRow1, rotationRow2; //Rotations
	CGparameter texture0, texture1, texture2, texture3; //Textures
	CGparameter shadowMap;
	CGparameter on0, on1, on2, on3; //Represent four toggles that can be toggled on/off
	CGparameter modelViewMatrix, lightViewMatrix, textureMatrix; //Modelview Matrix
	CGparameter globalAmbient, eyePosition, ke, ka, ks, kd, shininess, globalLightIntensity; //Lighting info
	CGparameter lightColor[4], lightPosition[4], numOfLights; //Light info
	//CGparameter lightColorArray, lightPositionArray;

	CGparameter translation, velocity, acceleration, t; //Particle variables

	CGparameter offset; //The UV offset for stuff like water

	CGparameter playerPos;

	CGparameter vortexPosition[3], numOfVorticies, size, intensity, emitterPos; //TEMP

	CGparameter magic0, magic1;

	//Mesh Skinning 
	CGparameter weights, jointIndices, boneMatricies;

	static GLfloat shadowBias[16];

private:
	CGcontext _context;
	CGprofile _profile;
	CGprogram _program;

	const char* _programName;
	const char* _fileName;
	const char* _funcName;
};