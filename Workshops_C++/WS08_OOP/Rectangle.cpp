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

#include <iostream>
#include "Rectangle.h"
#include <cstring>

using namespace std;
namespace sdds
{
	Rectangle::Rectangle()
	{
		m_width = 0;
		m_height = 0;
	}

	Rectangle::Rectangle(const char* content, int w, int h) :LblShape(content)
	{
		int widthMin = strlen(label()) + 2;

		if (h >= 3 && w >= widthMin)
		{
		
			m_width = w;
			m_height = h;
		}
		else
		{
			m_width = 0;
			m_height = 0;
		}
	}

	void Rectangle::getSpecs(istream& istr)
	{
		char comma = ',';
		LblShape::getSpecs(istr);
		istr >> m_width;
		istr >> comma;
		istr >> m_height;
		istr.ignore(1000, '\n');
	}

	void Rectangle::draw(ostream& os)const
	{
		if (m_width != 0)
		{
			os << "+";

			for (int i = 0; i < m_width - 2; i++)
			{
				os << "-";
			}
			os << "+" << endl;
			os << "|";
			os.unsetf(ios::right);
			os.setf(ios::left);

			os.width(m_width - 2);
			os << label();
			
			os.setf(ios::right);
			os << '|' << endl;
			
			
			for (int i = 0; i < m_height - 3; i++)
			{
				os << '|';
				os.width(m_width - 1);
				os << '|' << endl;
			}
			os << "+";

			for (int i = 0; i < m_width - 2; i++)
			{
				os << "-";
			}
			os << "+";

		}
	}
}
