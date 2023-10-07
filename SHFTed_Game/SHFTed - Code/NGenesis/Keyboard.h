#pragma once

#include <iostream>

#include "Include.h"

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void update(unsigned char &key, unsigned int state);
	void update(int &key, unsigned int state);

	bool getArrow(unsigned int index);
	bool getKey(unsigned char key);

	void setAlreadyPressed(bool status);
	bool getAlreadyPressed();

	unsigned int modifierKey; //Modifier keys like ctrl and alt

private:	
	//States whether or not the key is up or down
	unsigned int _KEY_UP;
	unsigned int _KEY_DOWN;

	//Ascii values representing the sequences we want
	unsigned int _ALPHA_BEGIN;
	unsigned int _ALPHA_END;
	unsigned int _DIGIT_BEGIN;
	unsigned int _DIGIT_END;

	//The number of each
	unsigned int _NUM_ARROW;
	unsigned int _NUM_ALPHA;
	unsigned int _NUM_DIGIT;

	bool _arrow[4];	
	bool _alphabet[26];
	bool _digit[10];

	bool _esc;
	bool _plus;
	bool _minus;

	bool _alreadyPressed;
};