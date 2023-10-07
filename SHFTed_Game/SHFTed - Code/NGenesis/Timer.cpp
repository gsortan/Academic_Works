#include "Timer.h"

Timer::Timer()
{
	_running = false;
	_timerCount = -1.0f;
	_timeStarted = 0.0f;

	_previousTime = 0;
	_currentTime = 0;
	_elapsedTime = 0;

	_frame = 0; //Used for fps calculation. Keeps track of which frame were on
	_timebase = 0; //Int used to compare for fps
	_fps = 0.0f; //Used to keep track of fps
}

Timer::~Timer()
{
}

void Timer::start()
{
	_running = true;
	_timeStarted = (float) glutGet(GLUT_ELAPSED_TIME); //Gets total running time of program
}

void Timer::stop()
{
	_running = false;
}

void Timer::reset()
{
	_timeStarted = (float) glutGet(GLUT_ELAPSED_TIME); //Gets total running time of program
	_timerCount = 0;
}

float Timer::get(unsigned int type)
{
	_timerCount = (float) glutGet(GLUT_ELAPSED_TIME) - _timeStarted; //Gets total running time of program

	if (type == NG_TIMER_SECONDS)
	{
		return _timerCount / 1000;
	}
	else
	{
		return _timerCount; //Milliseconds
	}
}

bool Timer::isRunning()
{
	return _running;
}

float Timer::getElapsedTime() //Returns time in seconds
{
	_currentTime = (float) glutGet(GLUT_ELAPSED_TIME); //Gets total running time of program
	_elapsedTime = _currentTime - _previousTime;
	_previousTime = _currentTime;

	if (_elapsedTime / 1000 > 0.0285714286) //1 / 35 fps
	{
		//return 1.0f;
		return 0.0285714286;
	}
	else
	{
		return _elapsedTime / 1000;
	}
}

float Timer::getFPS()
{
	_time = (float) glutGet(GLUT_ELAPSED_TIME); //Gets total running time of program
	++_frame; //Increments frame

	if (_time - _timebase > 1000)
	{
		_fps = _frame * 1000 / (_time - _timebase); //Multiplies total frames entered by time elapsed since last update
		_timebase = _time; //Sets timebase to current time
		_frame = 0; //Sets frame to 0
	}

	return _fps;
}