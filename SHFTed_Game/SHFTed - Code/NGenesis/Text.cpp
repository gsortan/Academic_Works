#include "Text.h"

Text::Text()
{
	initVariables();
}

Text::Text(std::string text, Vector3f position, Vector3f color)
{
	initVariables();

	set(text, position, color);
}

Text::~Text()
{
}

void Text::initVariables()
{
	_text = "";
	_position = Vector3f(0.0f, 0.0f, 0.0f);
	_color = Vector3f(0.0f, 0.0f, 0.0f);

	_effect = NG_TEXT_DEFAULT;
	_currentChar = 0;
	_printSpeed = 2.0f;
	_printCounter = 0;
	_printing = false;

	_fShader = new Shader("Fragment_Easy.cg", "fColor");
}

void Text::set(std::string text, Vector3f position, Vector3f color)
{
	_drawText = "";
	_text = text;
	_position = position;
	_color = color;

	_printing = true;
}

void Text::setText(std::string text)
{
	_drawText = ""; //Clears draw text
	_text = text;

	_currentChar = 0;
	_printCounter = 0;

	_printing = true;
}

void Text::setPosition(Vector3f position)
{
	_position = position;
}

void Text::setColor(Vector3f color)
{
	_color = color;
}

void Text::setEffect(unsigned int type)
{
	_effect = type;
}

std::string Text::getText() //This function is so bad
{
	return _text;
}

bool Text::getPrinting()
{
	return _printing;
}

void Text::shaderParameterHandler(Shader* shader)
{
	if (shader ->getFileName() == "Fragment_Easy.cg"
			|| shader ->getFileName() == "Fragment_Medium.cg"
			|| shader ->getFileName() == "Fragment_Blur.cg")
	{
		if (shader ->getShaderName() == "fColor")
		{
			
		}
	}

	shader ->checkForCgError("enable decal texture");	
}

void Text::update() //Updates only the effects
{
	if (_effect != NG_TEXT_DEFAULT) //Regular ones don't need effects
	{
		if (_effect == NG_TEXT_FADE)
		{
			//Fades out based on alpha
		}
		else if (_effect == NG_TEXT_TYPE)
		{
			if (_currentChar < _text.size()) //Only updates if there are new characters to push in
			{
					

				if (_printCounter == 0) //If 0
				{
					_drawText.push_back(_text[_currentChar]); //Add new character
					++_currentChar;
				}

				++_printCounter;

				if (_printCounter == _printSpeed)
				{
					_printCounter = 0;
				}			
			}
			else
			{
				_printing = false;
			}
		}
	}
	else //But we still need to push the text into the drawText
	{
		_drawText = _text;
	}
}

void Text::draw()
{
	glPushMatrix();

	glColor3f(_color.getX(), _color.getY(), _color.getZ());
	glRasterPos2f(_position.getX(), _position.getY());

	_fShader ->bindAndEnableShaders();
	shaderParameterHandler(_fShader);

	for (unsigned int i = 0; i < _drawText.size(); ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, _drawText[i]);
	}

	_fShader ->disableShaders();

	glPopMatrix();
}