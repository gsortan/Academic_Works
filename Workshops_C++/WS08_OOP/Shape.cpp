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

#include "Shape.h"

namespace sdds
{
	Shape::~Shape()
	{

	}

	std::ostream& operator<<(std::ostream& os, const Shape& shape)
	{
		shape.draw(os);
		return os;
	}

	std::istream& operator>>(std::istream& istr, Shape& shape)
	{
		shape.getSpecs(istr);
		return istr;
	}
}