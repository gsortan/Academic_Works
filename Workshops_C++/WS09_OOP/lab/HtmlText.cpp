/*****************************************************************************
< Workshop - #9 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-31-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include "HtmlText.h"
#include "cstring.h"

using namespace std;
namespace sdds {

	HtmlText::HtmlText(const char* filename, const char* title) :Text(filename)
	{
		if (title)
		{
			m_title = new char[strLen(title) + 1];
			strCpy(m_title, title);
		}
	}

	HtmlText::HtmlText(const HtmlText& copy) :Text(copy)
	{
		if (copy.m_title)
		{
			m_title = new char[strLen(copy.m_title) + 1];
			strCpy(m_title, copy.m_title);
		}
	}

	HtmlText& HtmlText::operator=(const HtmlText& copy)
	{
		Text::operator=(copy);
		if (this != &copy)
		{
			delete[] m_title;
			m_title = nullptr;

			if (copy.m_title)
			{
				m_title = new char[strLen(copy.m_title) + 1];
				strCpy(m_title, copy.m_title);
			}
		}

		return *this;
	}

	HtmlText::~HtmlText()
	{
		delete[] m_title;
	}

	void HtmlText::write(ostream& os)const
	{
		bool MS = false;

		os << "<html><head><title>";

		if (m_title)
		{
			os << m_title;
		}
		else
		{
			os << "No Title";
		}
		os << "</title></head>\n<body>\n";

		if (m_title)
		{
			os << "<h1>" << m_title << "</h1>\n";
		}

		int i = 0;

		//Use overloaded operator[] to access characters from m_content in Text class
		//And loop through the entire thing for html parsing till it hits the null terminator
		while ((*this)[i] != '\0')
		{
			if ((*this)[i] == '<')
			{
				os << "&lt;";
				MS = false;
			}
			else if ((*this)[i] == '>')
			{
				os << "&gt;";
				MS = false;
			}

			else if ((*this)[i] == '\n')
			{
				os << "<br />\n";
				MS = false;
			}
			else if ((*this)[i] == ' ' && MS)
			{
				os << "&nbsp;";

			}
			else if ((*this)[i] == ' ' && !MS)
			{
				os << (*this)[i];
				MS = true;
			}
			else
			{
				os << (*this)[i];
				MS = false;
			}
			i++;
		}
		os << "</body>\n</html>";
	}
}