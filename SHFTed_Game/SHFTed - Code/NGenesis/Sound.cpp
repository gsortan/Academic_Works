#include "Sound.h"

FmodSystem Sound::_fmod;
FMOD_RESULT Sound::_result;
bool Sound::_isInitialized = false;

void errorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
    {
		std::cout << "FMOD ERROR: " << result << " " << FMOD_ErrorString(result) << std::endl;
    }
}

//FmodSystem stuff ------------------------------

FmodSystem::FmodSystem()
{
	listenerPos.x = 0;
	listenerPos.y = 0;
	listenerPos.z = 0;
}

FmodSystem::~FmodSystem()
{
	release();
}

void FmodSystem::init()
{
	char name[256];

	Sound::setResult(FMOD::System_Create(&system));
	errorCheck(Sound::getResult());

	Sound::setResult(system ->getVersion(&version));
	errorCheck(Sound::getResult());

	if (version < FMOD_VERSION) //Checks version information
	{
		std::cout << "ERROR: You are using an old version of Fmod. This program requires " << version << FMOD_VERSION << std::endl;
	}

	Sound::setResult(system ->getNumDrivers(&numDrivers));
	errorCheck(Sound::getResult());

	if (numDrivers == 0)
	{
		Sound::setResult(system ->setOutput(FMOD_OUTPUTTYPE_NOSOUND));
		errorCheck(Sound::getResult());
	}
	else
	{
		Sound::setResult(system ->getDriverCaps(0, &caps, 0, 0, &speakerMode));
		errorCheck(Sound::getResult());

		Sound::setResult(system ->setSpeakerMode(speakerMode)); //Set the user selected speaker mode
		errorCheck(Sound::getResult());

		if (caps & FMOD_CAPS_HARDWARE_EMULATED) 
		{
			Sound::setResult(system ->setDSPBufferSize(1024, 10));
			errorCheck(Sound::getResult());

			std::cout << "ERROR: Apparently your acceleration slider is set to off, this is apparently bad." << std::endl;
		}

		Sound::setResult(system ->getDriverInfo(0, name, 256, 0));
		errorCheck(Sound::getResult());

		if (strstr(name, "SigmaTel")) //Apparently SigmaTel devices crackle if the format is PCM 16 bit. PCM floating point solves it (Apparently)
		{
			Sound::setResult(system ->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR));
			errorCheck(Sound::getResult());
		}
	}

	Sound::setResult(system ->init(100, FMOD_INIT_NORMAL, 0));

	if (Sound::getResult() == FMOD_ERR_OUTPUT_CREATEBUFFER) //If the speaker mode isnt supported by this sound card..
	{
		Sound::setResult(system ->setSpeakerMode(FMOD_SPEAKERMODE_STEREO)); //Set it back to stereo
		errorCheck(Sound::getResult());

		Sound::setResult(system ->init(100, FMOD_INIT_NORMAL, 0)); // Re-initialize it
		errorCheck(Sound::getResult());
	}

	Sound::setResult(system ->set3DSettings(1.0, 1.0, 0.3f)); //Sets the distance units
	errorCheck(Sound::getResult());
}

void FmodSystem::release()
{
	Sound::setResult(system ->close());
	errorCheck(Sound::getResult());

	Sound::setResult(system ->release());
	errorCheck(Sound::getResult());
}

//Sound stuff ------------------------------

Sound::Sound()
{
	if (_isInitialized == false) //Inits if not init'd
	{
		_fmod.init();
		_isInitialized = true;
	}

	_position.x = 0;
	_position.y = 0;
	_position.z = 0;

	_velocity.x = 0;
	_velocity.y = 0;
	_velocity.z = 0;

	_volume = 1.0f;

	_is3D = false;
	_isPlaying = false;
}

Sound::~Sound()
{
	_result = _sound ->release(); //Delete sound from memory
	errorCheck(_result);
}

bool Sound::load(const char* fileName, bool is3D, bool loop, unsigned int rollOff)
{
	std::cout << "Loading Sound: " << fileName << "." << std::endl;

	this ->_is3D = is3D;

	if (_is3D) //If it's a 3D sound
	{
		if (rollOff == NG_LINEAR_ROLLOFF)
		{
			_result = _fmod.system ->createSound(fileName, FMOD_3D | FMOD_3D_LINEARROLLOFF, 0, &_sound);
		}
		else
		{
			_result = _fmod.system ->createSound(fileName, FMOD_3D | FMOD_3D_LOGROLLOFF, 0, &_sound);
		}

		_sound ->set3DMinMaxDistance(0.5f, 20.0f); //How far away the sound can be heard
	}
	else //If 2D
	{
		_result = _fmod.system ->createSound(fileName, FMOD_2D, 0, &_sound);
	}

	errorCheck(_result);

	if (_result != FMOD_OK) //If not ok
	{
		return false;
	}

	if (loop) //If looping
	{
		_result = _sound ->setMode(FMOD_LOOP_NORMAL);
		errorCheck(_result);
	}

	return true;
}

FMOD::Channel* Sound::play()
{
	_result = _fmod.system ->playSound(FMOD_CHANNEL_FREE, _sound, false, &_channel);
	errorCheck(_result);

	if (_result != FMOD_OK)
	{
		return NULL; 
	}

	if (_is3D)
	{
		_result = _channel ->set3DAttributes(&_position, &_velocity);
	}

	_isPlaying = true;

	_channel ->setVolume(_volume);

	return _channel;
}

void Sound::stop()
{
	_isPlaying = false;
	_channel ->stop();
}

bool Sound::getPaused() //Essentially just returns true or false depending on current state
{
	bool paused;
	_channel ->getPaused(&paused);

	return paused;
}

void Sound::setSound(FMOD::Sound* sound)
{
	_sound = sound;
}

void Sound::setChannel(FMOD::Channel* channel)
{
	_channel = channel;
}

FMOD::Sound* Sound::getSound()
{
	return _sound;
}

FMOD::Channel* Sound::getChannel()
{
	return _channel;
}

void Sound::setResult(FMOD_RESULT result)
{
	_result = result;
}

FMOD_RESULT Sound::getResult()
{
	return _result;
}

void Sound::setPosition(Vector3f position)
{
	_position.x = position.getX();
	_position.y = position.getY();
	_position.z = position.getZ();

	bool playing;
	_channel ->isPlaying(&playing);

	if (playing && _is3D)
	{
		_result = _channel ->set3DAttributes(&_position, &_velocity);
		errorCheck(_result);
	}
}

void Sound::setVelocity(Vector3f velocity)
{
	_velocity.x = velocity.getX();
	_velocity.y = velocity.getY();
	_velocity.z = velocity.getZ();

	bool playing;
	_channel ->isPlaying(&playing);

	if (playing && _is3D)
	{
		_result = _channel ->set3DAttributes(&_position, &_velocity);
		errorCheck(_result);
	}
}

FMOD_VECTOR Sound::getPos()
{
	return _position;
}

FMOD_VECTOR Sound::getVel()
{
	return _velocity;
}

void Sound::setVolume(float volume)
{
	if (volume <= 0) //Range is 0 to 1
	{
		_volume = 0;
	}
	else if (volume >= 1.0f)
	{
		_volume = 1.0f;
	}
	else
	{
		_volume = volume;
	}

	_channel ->setVolume(_volume);
}

float Sound::getVolume()
{
	return _volume;
}

void Sound::setRolloff(unsigned int state)
{
	if (state == NG_LOG_ROLLOFF)
	{		
		_sound ->setMode(FMOD_3D_LOGROLLOFF);		
	}
	else
	{
		_sound ->setMode(FMOD_3D_LINEARROLLOFF);		
	}
}

bool Sound::getIsPlaying()
{
	return _isPlaying;
}

FMOD_VECTOR Sound::getListenerPos()
{
	return _fmod.listenerPos;
}

void Sound::setListenerPos(Vector3f position)
{
	_fmod.listenerPos.x = position.getX();
	_fmod.listenerPos.y = position.getY();
	_fmod.listenerPos.z = position.getZ();
}

void Sound::setListenerVel(Vector3f velocity)
{
	_fmod.listenerVel.x = velocity.getX();
	_fmod.listenerVel.y = velocity.getY();
	_fmod.listenerVel.z = velocity.getZ();
}

void Sound::setListenerForward(Vector3f forward)
{
	_fmod.listenerForward.x = forward.getX();
	_fmod.listenerForward.y = forward.getY();
	_fmod.listenerForward.z = forward.getZ();
}

void Sound::setListenerUp(Vector3f up)
{
	_fmod.listenerUp.x = up.getX();
	_fmod.listenerUp.y = up.getY();
	_fmod.listenerUp.z = up.getZ();
}

void Sound::update()
{
	_result = _fmod.system ->set3DListenerAttributes(0, &_fmod.listenerPos, &_fmod.listenerVel, &_fmod.listenerForward, &_fmod.listenerUp);
	errorCheck(_result);

	_fmod.system ->update();
}