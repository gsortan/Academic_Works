
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <iostream>

#pragma comment(lib, "Include/fmod/lib/fmodex_vc.lib")

#include "Vector3f.h"

#include "Include\fmod\inc\fmod.hpp"
#include "Include\fmod\inc\fmod_errors.h"

#define NG_LINEAR_ROLLOFF 0
#define NG_LOG_ROLLOFF 1

void errorCheck(FMOD_RESULT result);

class FmodSystem //Holds listener settings and other fmod classes
{
public:
	FmodSystem();
	~FmodSystem();

	void init();
	void release();

	FMOD::System* system;

	int numDrivers;

	FMOD_VECTOR listenerPos;
	FMOD_VECTOR listenerVel;
	FMOD_VECTOR listenerForward;
	FMOD_VECTOR listenerUp;

	unsigned int version;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;

private:
};

class Sound
{
public:
	Sound();
	~Sound();

	bool load(const char* fileName, bool is3D, bool loop, unsigned int rollOff);
	FMOD::Channel* play();

	void stop();

	bool getPaused();

	void setSound(FMOD::Sound* sound);
	void setChannel(FMOD::Channel* channel);
	FMOD::Sound* getSound();
	FMOD::Channel* getChannel();

	static void setResult(FMOD_RESULT result);
	static FMOD_RESULT getResult();

	void setPosition(Vector3f position);
	void setVelocity(Vector3f velocity);
	FMOD_VECTOR getPos();
	FMOD_VECTOR getVel();

	void setVolume(float volume);
	float getVolume();

	void setRolloff(unsigned int state);

	bool getIsPlaying();

	static FMOD_VECTOR getListenerPos();
	static void setListenerPos(Vector3f position);
	static void setListenerVel(Vector3f velocity);
	static void setListenerForward(Vector3f forward);
	static void setListenerUp(Vector3f up);

	static void update();

private:
	FMOD_VECTOR _position;
	FMOD_VECTOR _velocity;

	FMOD::Sound* _sound;
	FMOD::Channel* _channel;

	static FmodSystem _fmod;
	static FMOD_RESULT _result;

	float _volume;

	bool _is3D;
	bool _isPlaying; //Only useful for looped sounds
	static bool _isInitialized;
};