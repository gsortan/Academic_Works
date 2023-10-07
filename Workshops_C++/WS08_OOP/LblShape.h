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

#ifndef SDDS_LBLSHAPE_H
#define SDDS_LBLSHAPE_H
#include "Shape.h"

namespace sdds
{
	class LblShape :public Shape
	{
		char* m_label;
	public:
		LblShape();
		LblShape(const char* content);
		LblShape(const LblShape& otherShape) = delete;
		LblShape& operator=(const LblShape& otherShape) = delete;
		virtual void getSpecs(std::istream& istr);
		virtual ~LblShape();
		
	protected:
		const char * label()const;
	};

}
#endif

