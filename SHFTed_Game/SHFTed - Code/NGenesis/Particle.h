
#pragma once

#include "Vector3f.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h" //Get rid of htis later
#include "Camera.h"

#include "Include.h"
#include <vector>

#define NG_WEATHER_SNOW 0
#define NG_WEATHER_RAIN 1
#define NG_PARTICLE_FIREBLAST 2
#define NG_PARTICLE_ICEBLAST 3
#define NG_PARTICLE_DEATH 4
#define NG_PARTICLE_HIT 5

#define NG_RED 0
#define NG_GREEN 1
#define NG_BLUE 2
#define NG_ALPHA 3

#define NG_GRAVITY -5


#define NG_MAX_WEATHER_PARTICLES 1000 //Used for vector size checking

class Particle
{
public:
	Particle();
	~Particle();

	void initVariables();
	void initParticle(unsigned int type, Vector3f position);
	void draw();
	void update();	
	void shaderParameterHandler(Shader* shader);

	void setColor(float r, float g, float b, float a);
	void setPosition(Vector3f &position);
	void setVelocity(Vector3f &velocity);
	void setWeight(float weight);
	void setWind(Vector3f &wind);
	void setSize(float size);
	void setTexture(Texture &texture);

	Vector3f getPosition();
	Vector3f getVelocity();
	Vector3f getAcceleration();
	float getColor(unsigned int num);	
	float getWeight();
	float getSize();
	float getDecay();
	float getLifetime();

	bool getActive();

	Vector3f getWind();	

private:
	struct colorInfo //Four "colors"
	{
		float r;
		float g;
		float b;
		float a;
	} _color;

	Vector3f _position;
	Vector3f _velocity;
	Vector3f _acceleration;
	Vector3f _wind;

	Shader* _vShader;
	Shader* _fShader;

	Texture _texture;

	float _decay, _lifetime;	
	float _weight, _size;	
	bool _active;
	int _type;	

	float _attenuationFactor;
};