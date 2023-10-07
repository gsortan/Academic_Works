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

#include "Line.h"

using namespace std;
namespace sdds
{
	Line::Line():LblShape()
	{
		m_length = 0;
	}

	Line::Line(const char* label, int length) :LblShape(label)
	{
		m_length = length;
	}

	void Line::getSpecs(std::istream& istr)
	{
		LblShape::getSpecs(istr);
		istr >> m_length;
		istr.ignore(1000, '\n');
	}

	void Line::draw(std::ostream& os)const
	{
		if (m_length > 0 && label() != nullptr)
		{
			os << label() << endl;
			for (int i = 0; i < m_length; i++)
			{
				os << "=";
			}

		}
	}

}