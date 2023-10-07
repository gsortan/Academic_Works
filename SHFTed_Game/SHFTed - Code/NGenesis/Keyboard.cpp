#include "Keyboard.h"

Keyboard::Keyboard()
{
	//Ascii values representing the sequences we want
	_ALPHA_BEGIN = 97;
	_ALPHA_END = 122;
	_DIGIT_BEGIN = 48;
	_DIGIT_END = 57;

	//The number of each
	_NUM_ARROW = 4;
	_NUM_ALPHA = 26;
	_NUM_DIGIT = 10;

	for (unsigned int i = 0; i < _NUM_ARROW; ++i)
	{
		_arrow[i] = false;
	}

	for (unsigned int i = 0; i < _NUM_ALPHA; ++i)
	{
		_alphabet[i] = false;
	}

	for (unsigned int i = 0; i < _NUM_DIGIT; ++i)
	{
		_digit[i] = false;
	}

	_esc = false;
	_plus = false;
	_minus = false;

	_alreadyPressed = false;
}

Keyboard::~Keyboard()
{

}

void Keyboard::update(unsigned char &key, unsigned int state) //Regular keys
{
	if (key >= _ALPHA_BEGIN && key <= _ALPHA_END) //Checks if its within the alphabet range
	{
		for (unsigned int i = _ALPHA_BEGIN; i <= _ALPHA_END; ++i)
		{
			if (key == i)
			{
				_alphabet[i - _ALPHA_BEGIN] = state;
				break;
			}
		}
	}
	else if (key >= _DIGIT_BEGIN && key <= _DIGIT_BEGIN) //Checks if within digit range
	{
		for (unsigned int i = _DIGIT_BEGIN; i <= _DIGIT_END; ++i)
		{
			if (key == i)
			{
				_digit[i - _DIGIT_BEGIN] = state;
				break;
			}
		}
	}
	else
	{
		if (key == 27) //Esc
		{
			_esc = state;
		}
		else if (key == 61) //"Equals"
		{
			_plus = state;
		}
		else if (key == 45) //Subtract
		{
			_minus = state;
		}
	}
}

void Keyboard::update(int &key, unsigned int state) //Special keys
{
	switch (key)
	{
	case (GLUT_KEY_UP):
		_arrow[0] = state;
		break;
	case (GLUT_KEY_LEFT):
		_arrow[1] = state;
		break;
	case (GLUT_KEY_DOWN):
		_arrow[2] = state;
		break;
	case (GLUT_KEY_RIGHT):
		_arrow[3] = state;
		break;
	}
}

bool Keyboard::getArrow(unsigned int index)
{
	return _arrow[index];
}

bool Keyboard::getKey(unsigned char key)
{
	if (key >= _ALPHA_BEGIN && key <= _ALPHA_END) //Checks if its within the alphabet range
	{
		return _alphabet[key - _ALPHA_BEGIN];
	}
	else if (key >= _DIGIT_BEGIN && key <= _DIGIT_END) //Checks if within digit range
	{
		return _digit[key - _DIGIT_BEGIN];
	}
	else
	{
		if (key == 27) //Esc
		{
			return _esc;
		}
		else if (key == 61) //"Equals"
		{
			return _plus;
		}
		else if (key == 45) //Subtract
		{
			return _minus;
		}
	}

	std::cout << "INVALID KEY" << std::endl;
	return false;
}

void Keyboard::setAlreadyPressed(bool status)
{
	_alreadyPressed = status;
}

bool Keyboard::getAlreadyPressed()
{
	return _alreadyPressed;
}