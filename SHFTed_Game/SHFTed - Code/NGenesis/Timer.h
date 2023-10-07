#pragma once

#include "Include.h"

#define NG_TIMER_SECONDS 0 
#define NG_TIMER_MILLISECONDS 1

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void reset();
	float get(unsigned int type);
	bool isRunning();

	//These guys might just be static
	float getElapsedTime();
	float getFPS();

private:
	//For regular
	float _timerCount;
	float _timeStarted;
	bool _running;

	//For elapsed time
	float _previousTime;
	float _currentTime;
	float _elapsedTime;

	//For FPS
	float _time;
	unsigned int _frame; //Used for fps calculation. Keeps track of which frame were on
	unsigned int _timebase; //Int used to compare for fps
	float _fps; //Used to keep track of fps
};