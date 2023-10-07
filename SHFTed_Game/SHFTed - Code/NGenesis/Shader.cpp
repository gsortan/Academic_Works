/*

SHADER COMBOS
Plain Color: vColor, fColor
Texture - Replace: vColor, fTextureReplace
Texture - Modulate: vColor, fTextureModulate
Displacement Map - vDisplacementMap, fColor
Vertex Lighting: vLighting, fColor
Fragment Lighting: vFragLighting, fLighting
Normal Map: vColor, fNormalMap
Toon Shading: vFragLighting, fToon
Multi Fragment Lighting: vFragLighting, fMultiLighting
Depth Rendering: vFragLighting, fDepth
Multi Texturing: vColor, fMultiTexture

*/

#include "Shader.h"

GLfloat Shader::shadowBias[] = {0.5f, 0.0f, 0.0f, 0.5f, 
								0.0f, 0.5f, 0.0f, 0.5f,
								0.0f, 0.0f, 0.5f, 0.5f,
								0.0f, 0.0f, 0.0f, 1.0f};

Shader::Shader()
{

}

Shader::Shader(const char* shaderFileName, const char* shaderName)
{
	_programName = "NGenesis"; 
	_fileName = shaderFileName;
	_funcName = shaderName;

	initCg();
}

Shader::~Shader()
{

}

void Shader::checkForCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		printf("%s: %s: %s\n", _programName, situation, string);

		if (error == CG_COMPILER_ERROR) 
		{
			printf("%s\n", cgGetLastListing(_context));
		}

		system("Pause");
		exit(1);
	}
}

void Shader::initCg() //Initializes the shaders. The first section is when you create the context, and then the vertex and then fragments
{
	_context = cgCreateContext(); //Contexts are containers for Cg programs
	checkForCgError("creating context");
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(_context, CG_DEFERRED_PARAMETER_SETTING);
	
	if (_fileName == "Vertex_Easy.cg" 
		|| _fileName == "Vertex_Medium.cg" 
		|| _fileName == "Vertex_Blur.cg" 
		|| _fileName == "GPU_Skinning.cg"
		|| _fileName == "Vertex_Shadow.cg") 
	{
		_profile = cgGLGetLatestProfile(CG_GL_VERTEX);
	}
	else if (_fileName == "Fragment_Easy.cg" || _fileName == "Fragment_Medium.cg" || _fileName == "Fragment_Blur.cg") //OIT WILL CAUSE ISSUES OTHERWISE
	{
		_profile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	}

	cgGLSetOptimalOptions(_profile);
	checkForCgError("selecting shader profile");

	_program = cgCreateProgramFromFile(_context, CG_SOURCE, _fileName, _profile, _funcName, NULL);

	checkForCgError("creating shader program from file");

	initAndSetParameters();

	cgGLLoadProgram(_program);
	checkForCgError("loading shader program");	
}

void Shader::bindAndEnableShaders() //Binds the shader programs to the main program
{
	cgGLBindProgram(_program);
	checkForCgError("binding program");

	cgGLEnableProfile(_profile);
	checkForCgError("enabling profile");
}

void Shader::disableShaders() //Disables the shaders
{
	cgGLDisableProfile(_profile);
	checkForCgError("disabling profile");
}

void Shader::initAndSetParameters() 
{
	if (_fileName == "Fragment_Easy.cg")
	{
		if (_funcName == "fColor")
		{

		}
		else if (_funcName == "fTextureReplace" 
			|| _funcName == "fTextureModulate")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
		}
		else if (_funcName == "fLighting")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");

			offset = cgGetNamedParameter(_program, "offset");
		}
		else if (_funcName == "fLightingGooch")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");

			color = cgGetNamedParameter(_program, "statusColour");
			globalLightIntensity = cgGetNamedParameter(_program, "globalIntensity");

			offset = cgGetNamedParameter(_program, "offset");
		}
		else if (_funcName == "fLightingGoochWithShadow")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
			shadowMap = cgGetNamedParameter(_program, "shadowMap");

			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");

			color = cgGetNamedParameter(_program, "statusColour");
			globalLightIntensity = cgGetNamedParameter(_program, "globalIntensity");

			offset = cgGetNamedParameter(_program, "offset");
		}
		else if (_funcName == "fMultiTexture")
		{
			on0 = cgGetNamedParameter(_program, "on0");
			on1 = cgGetNamedParameter(_program, "on1");
			on2 = cgGetNamedParameter(_program, "on2");
			on3 = cgGetNamedParameter(_program, "on3");

			texture0 = cgGetNamedParameter(_program, "decal0");
			texture1 = cgGetNamedParameter(_program, "decal1");
			texture2 = cgGetNamedParameter(_program, "decal2");
			texture3 = cgGetNamedParameter(_program, "decal3");	
		}		
	}
	else if (_fileName == "Fragment_Medium.cg")
	{
		if (_funcName == "fNormalMap")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");

			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");
			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");
		}
		else if (_funcName == "fToon")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");

			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");
		}
		else if (_funcName == "fToonNoLighting")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
		}
		else if (_funcName == "fMultiLighting")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");

			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor0");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition0");
			lightColor[1] = cgGetNamedParameter(_program, "lightColor1");
			lightPosition[1] = cgGetNamedParameter(_program, "lightPosition1");
			lightColor[2] = cgGetNamedParameter(_program, "lightColor2");
			lightPosition[2] = cgGetNamedParameter(_program, "lightPosition2");
			lightColor[3] = cgGetNamedParameter(_program, "lightColor3");
			lightPosition[3] = cgGetNamedParameter(_program, "lightPosition3");

			numOfLights = cgGetNamedParameter(_program, "numOfLights");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");
		}
		else if (_funcName == "fDepth")
		{
			eyePosition = cgGetNamedParameter(_program, "eyePosition");
		}
	}
	else if (_fileName == "Fragment_Blur.cg")
	{
		if (_funcName == "main")
		{
			size = cgGetNamedParameter(_program, "size");
			intensity = cgGetNamedParameter(_program, "intensity");
			texture0 = cgGetNamedParameter(_program, "blurred");
			texture1 = cgGetNamedParameter(_program, "original");
		}
		if (_funcName == "nonEdgeDetection")
		{
			size = cgGetNamedParameter(_program, "size");
			intensity = cgGetNamedParameter(_program, "intensity");
			texture0 = cgGetNamedParameter(_program, "blurred");
			texture1 = cgGetNamedParameter(_program, "original");
		}
	}
	else if (_fileName == "Vertex_Easy.cg")
	{
		color = cgGetNamedParameter(_program, "newColor");
		
		rotationRow0 = cgGetNamedParameter(_program, "rotationRow0");
		rotationRow1 = cgGetNamedParameter(_program, "rotationRow1");
		rotationRow2 = cgGetNamedParameter(_program, "rotationRow2");
		modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");

		if (_funcName == "vColor")
		{			

		}
		else if (_funcName == "vDisplacementMap")
		{
			texture0 = cgGetNamedParameter(_program, "decal0");
		}
		else if (_funcName == "vLighting")
		{
			globalAmbient = cgGetNamedParameter(_program, "globalAmbient");

			lightColor[0] = cgGetNamedParameter(_program, "lightColor");
			lightPosition[0] = cgGetNamedParameter(_program, "lightPosition");

			eyePosition = cgGetNamedParameter(_program, "eyePosition");
			ke = cgGetNamedParameter(_program, "ke");
			ka = cgGetNamedParameter(_program, "ka");
			ks = cgGetNamedParameter(_program, "ks");
			kd = cgGetNamedParameter(_program, "kd");
			shininess = cgGetNamedParameter(_program, "shininess");
		}
		else if (_funcName == "vFragLighting")
		{

		}
		else if (_funcName == "vFragLightingShadow")
		{
			textureMatrix = cgGetNamedParameter(_program, "textureMatrix");
			lightViewMatrix = cgGetNamedParameter(_program, "lightViewMatrix");
		}
		else if (_funcName == "vParticle")
		{
			translation = cgGetNamedParameter(_program, "translation");
			velocity = cgGetNamedParameter(_program, "velocity");
			acceleration = cgGetNamedParameter(_program, "acceleration");
			t = cgGetNamedParameter(_program, "t");
		}
		else if (_funcName == "vParticle2")
		{
			translation = cgGetNamedParameter(_program, "translation");
			emitterPos = cgGetNamedParameter(_program, "emitterPos");
			velocity = cgGetNamedParameter(_program, "velocity");
			acceleration = cgGetNamedParameter(_program, "acceleration");
			t = cgGetNamedParameter(_program, "t");

			vortexPosition[0] = cgGetNamedParameter(_program, "vortexPosition0");
			vortexPosition[1] = cgGetNamedParameter(_program, "vortexPosition1");
			vortexPosition[2] = cgGetNamedParameter(_program, "vortexPosition2");

			numOfVorticies = cgGetNamedParameter(_program, "numOfVorticies");
		}
	}
	else if (_fileName == "Vertex_Medium.cg" || _fileName == "Vertex_Blur.cg")
	{
		color = cgGetNamedParameter(_program, "newColor");
		rotationRow0 = cgGetNamedParameter(_program, "rotationRow0");
		rotationRow1 = cgGetNamedParameter(_program, "rotationRow1");
		rotationRow2 = cgGetNamedParameter(_program, "rotationRow2");
		modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");
	}
	else if (_fileName == "GPU_Skinning.cg")
	{
		if (_funcName == "skinMeshWithLightingAndShadows")
		{
			rotationRow0 = cgGetNamedParameter(_program, "rotationRow0");
			rotationRow1 = cgGetNamedParameter(_program, "rotationRow1");
			rotationRow2 = cgGetNamedParameter(_program, "rotationRow2");

			weights = cgGetNamedParameter(_program, "weights");
			jointIndices = cgGetNamedParameter(_program, "jointIndices");
			boneMatricies = cgGetNamedParameter(_program, "boneMatrices");
			modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");

			textureMatrix = cgGetNamedParameter(_program, "textureMatrix");
			lightViewMatrix = cgGetNamedParameter(_program, "lightViewMatrix");
		}
		if (_funcName == "skinMeshWithLighting")
		{
			rotationRow0 = cgGetNamedParameter(_program, "rotationRow0");
			rotationRow1 = cgGetNamedParameter(_program, "rotationRow1");
			rotationRow2 = cgGetNamedParameter(_program, "rotationRow2");

			weights = cgGetNamedParameter(_program, "weights");
			jointIndices = cgGetNamedParameter(_program, "jointIndices");
			boneMatricies = cgGetNamedParameter(_program, "boneMatrices");
			modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");
		}
		else if (_funcName == "skinMesh")
		{
			rotationRow0 = cgGetNamedParameter(_program, "rotationRow0");
			rotationRow1 = cgGetNamedParameter(_program, "rotationRow1");
			rotationRow2 = cgGetNamedParameter(_program, "rotationRow2");

			weights = cgGetNamedParameter(_program, "weights");
			jointIndices = cgGetNamedParameter(_program, "jointIndices");
			boneMatricies = cgGetNamedParameter(_program, "boneMatrices");
			modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");
		}
	}
	else if (_fileName == "Vertex_Shadow.cg")
	{
		modelViewMatrix = cgGetNamedParameter(_program, "modelViewMatrix");
		lightViewMatrix = cgGetNamedParameter(_program, "lightViewMatrix");
		textureMatrix = cgGetNamedParameter(_program, "textureMatrix");
	}
	else if (_fileName == "Fragment_Shadow.cg")
	{
		lightViewMatrix = cgGetNamedParameter(_program, "lightViewMatrix");
	}
}

const char* Shader::getFileName()
{
	return _fileName;
}

const char* Shader::getShaderName()
{
	return _funcName;
}

void Shader::setLightMatrix()
{
	
}