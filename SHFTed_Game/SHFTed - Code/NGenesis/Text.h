#pragma once

#include "Vector3f.h"
#include "Shader.h"
#include "Include.h"
#include <string>

#define NG_TEXT_DEFAULT 0 //No effects
#define NG_TEXT_FADE 1 //Text fades in and out
#define NG_TEXT_TYPE 2 //Text is "typed" int. One character at a time

class Text
{
public:
	Text();
	Text(std::string text, Vector3f position, Vector3f color);
	~Text();

	void initVariables();

	void set(std::string text, Vector3f position, Vector3f color);
	void setText(std::string text);
	void setPosition(Vector3f position);
	void setColor(Vector3f color);
	void setEffect(unsigned int type);

	std::string getText();
	bool getPrinting();

	void shaderParameterHandler(Shader* shader);
	void update();
	void draw();

private:
	std::string _drawText; //The text actually to be drawn
	std::string _text; //The full text
	Vector3f _position;
	Vector3f _color;

	unsigned int _effect;
	unsigned int _currentChar; //Character for text printing
	unsigned int _printSpeed; //Speed for printing
	unsigned int _printCounter; //Counted used to keep track of print speed
	bool _printing; //If text is being printed, it's false when it's done

	Shader* _fShader;
};