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

#ifndef SDDS_RECTANGLE_H
#define SDDS_RECTANGLE_H


#include "LblShape.h"

namespace sdds
{
	class Rectangle:public LblShape
	{
		int m_width;
		int m_height;
		
	public:
		Rectangle();
		Rectangle(const char* content, int w, int h);

		void getSpecs(std::istream& istr);
		void draw(std::ostream& os)const;
	};
}

#endif // !RECTANGLE_H