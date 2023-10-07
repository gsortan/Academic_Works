/*****************************************************************************
< Workshop - #8 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-24-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "LblShape.h"
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
namespace sdds
{
	LblShape::LblShape()
	{
		m_label = nullptr;
	}

	LblShape::LblShape(const char* content)
	{
	
		m_label = new char[strlen(content) + 1];
		strcpy(m_label, content);
	}


	const char* LblShape::label()const
	{
		return m_label;
	}

	void LblShape::getSpecs(std::istream& istr)
	{
		//Dynamically allocating new memory every time with this function
		//so the delete has to be called to free the pointer
		//resource if something already exists or else there will be a memory leak
		delete[] m_label; 
		std::string input;
		getline(istr,input, ',');
		int size = strlen(input.c_str());
		m_label = new char[size + 1];
		strcpy(m_label, input.c_str());
	}



	LblShape::~LblShape()
	{
		
	delete[] m_label;
		
	}
}