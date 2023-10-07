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

#include <fstream>
#include "Text.h"
#include "cstring.h"

using namespace std;
namespace sdds {


	Text::Text(const char* filename)
	{
		if (filename)
		{
			m_filename = new char[strLen(filename) + 1];
			strCpy(m_filename, filename);
			read();
		}
	}

	Text::Text(const Text& copyText)
	{

		if (copyText.m_filename)
		{
			m_filename = new char[strLen(copyText.m_filename) + 1];
			strCpy(m_filename, copyText.m_filename);
		}

		if (copyText.m_content)
		{
			m_content = new char[strLen(copyText.m_content) + 1];
			strCpy(m_content, copyText.m_content);
		}
	}

	Text& Text::operator=(const Text& copyText)
	{
		if (this != &copyText)
		{
			delete[] m_filename;
			m_filename = nullptr;

			if (copyText.m_filename)
			{

				m_filename = new char[strLen(copyText.m_filename) + 1];
				strCpy(m_filename, copyText.m_filename);
			}


			delete[] m_content;
			m_content = nullptr;

			if (copyText.m_content)
			{
				m_content = new char[strLen(copyText.m_content) + 1];
				strCpy(m_content, copyText.m_content);
			}

		}

		return *this;
	}

	Text::~Text()
	{
		delete[] m_content;
		delete[] m_filename;
	}

	int Text::getFileLength() const {
		int len = 0;
		ifstream fin(m_filename);
		while (fin) {
			fin.get();
			len += !!fin;
		}
		return len;
	}

	const char& Text::operator[](int index)const
	{
		return m_content[index];
	}

	void Text::read()
	{
		char c;
		int i = 0;
		int fileLen = getFileLength();
		if (fileLen != 0)
		{
			m_content = new char[fileLen + 1];
			ifstream fileInput(m_filename);
			while (fileInput.get(c))
			{
				m_content[i] = c;
				i++;
			}

			m_content[fileLen] = '\0';

		}

	}

	void Text::write(ostream& os)const
	{
		if (m_content != nullptr)
		{
			os << m_content;
		}
	}

	ostream& operator<<(ostream& os, const Text& textObj)
	{
		textObj.write(os);

		return os;
	}

}