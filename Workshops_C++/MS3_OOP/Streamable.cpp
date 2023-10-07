/*****************************************************************************
< Final Project Milestone #3 >
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-21-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include "Streamable.h"

using namespace std;

namespace sdds
{
	Streamable::~Streamable()
	{

	}

	ostream& operator<<(ostream& os, const Streamable& streamObj)
	{
		if (streamObj)
		{
			streamObj.write(os);
		}
		return os;
	}

	istream& operator>>(istream& is, Streamable& streamObj)
	{
		streamObj.read(is);
		return is;
	}

}