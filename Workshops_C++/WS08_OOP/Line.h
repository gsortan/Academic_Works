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

#ifndef SDDS_LINE_H
#define SDDS_LINE_H
#include"LblShape.h"

namespace sdds
{
	class Line :public LblShape
	{
		int m_length;
	public:
		Line();
		Line(const char * label, int length);

	
		void getSpecs(std::istream& istr);
		void draw(std::ostream& os)const;
	};
}
#endif

