/*****************************************************************************
< Workshop - #6 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-09-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "TextFile.h"
#include "cstring.h"
class TextFile;
using namespace std;
namespace sdds {
	Line::operator const char* () const {
		return (const char*)m_value;
	}
	Line& Line::operator=(const char* lineValue) {
		delete[] m_value;
		m_value = new char[strLen(lineValue) + 1];
		strCpy(m_value, lineValue);
		return *this;
	}
	Line::~Line() {
		delete[] m_value;
	}

	//Set a safe empty state
	void TextFile::setEmpty()
	{
		
		delete[] m_textLines;
		m_textLines = nullptr;
		
		delete[] m_filename;
		m_filename = nullptr;
		m_noOfLines = 0;
	}


	void TextFile::setFilename(const char* fname, bool isCopy)
	{
		//Check if it's a copy before allocating chunk of memory for file name and using arg to set it
		//if it is a copy attach the prefix of C_ to it
		if (!isCopy)
		{
			m_filename = new char[strLen(fname) + 1];
			strCpy(m_filename, fname);
		}
		else
		{
			char prefix[3] = "C_";
			m_filename = new char[strLen(fname) + 3];
			strCpy(m_filename, prefix);
			strCat(m_filename, fname);
		}
	}

	//Count the number of lines from the file
	void TextFile::setNoOfLines()
	{
		ifstream fileReader(m_filename);

		char fileChar;

		if (fileReader.is_open())
		{
			//Loop and obtain every char from file and increment line count appropriately
			while (fileReader.get(fileChar))
			{
				if (fileChar == '\n')
				{
					m_noOfLines++;
				}
			}
			fileReader.close();
		}

		if (m_noOfLines > 0)
		{
			m_noOfLines++;
		}

		
		if (m_noOfLines == 0)
		{
			delete[] m_filename;
			m_filename = nullptr;
		}
	}
	
	void TextFile::loadText()
	{
		int index = 0;
		int numLines = 0;

		//Check if file name isn't a null pointer than  allocate memory for lines 
		//Read line by line for file and store everything in lines list
		if (m_filename != nullptr)
		{
			m_textLines = new Line[m_noOfLines];
			ifstream fileReader(m_filename);
			string fStr;

			if (fileReader.is_open())
			{
				while (getline(fileReader, fStr))
				{
					m_textLines[index].m_value = new char[strLen(fStr.c_str()) + 1];
					strCpy(m_textLines[index].m_value, fStr.c_str());
					numLines++;
					index++;
				}
				m_noOfLines = numLines;
				fileReader.close();
			}
		}
	}

	//Save and write out content to file under this arg name
	void TextFile::saveAs(const char* fileName)const
	{
		ofstream os(fileName);

		for (unsigned int i = 0; i < m_noOfLines; i++)
		{
			os << m_textLines[i] << endl;
		}
	}

	//Set to safe empty state with object creation 
	TextFile::TextFile(unsigned pageSize)
	{
		setEmpty();
		m_pageSize = pageSize;
	}

	//Set to safe empty sate with constructor and load the text in with assigned file name
	TextFile::TextFile(const char* filename, unsigned pageSize)
	{
		setEmpty();
		m_pageSize = pageSize;

		if (filename != NULL)
		{
			setFilename(filename);
			setNoOfLines();
			loadText();
		}
	}

	TextFile::TextFile(const TextFile& txtCopy)
	{
		m_pageSize = txtCopy.m_pageSize;
		m_textLines = nullptr;
		m_filename = nullptr;
		m_noOfLines = 0;

		//Ensure the incoming text file is valid then perform a deep and shallow copy of data
		//Then save file under new name of incoming file
		if (txtCopy)
		{
			setFilename(txtCopy.m_filename, true);
			m_noOfLines = txtCopy.lines();
			m_textLines = new Line[m_noOfLines];

			for (unsigned int i = 0; i < m_noOfLines; i++)
			{
				m_textLines[i].m_value = new char[strLen(txtCopy.m_textLines[i].m_value) + 1];
				strCpy(m_textLines[i].m_value, txtCopy.m_textLines[i].m_value);
			}

			saveAs(m_filename);
		}

	}


	TextFile& TextFile::operator=(const TextFile& txtCopy)
	{
		//Ensure the incoming text file is valid then perform a deep and do a self-reference check
		// perform a deep and shallow copy of data
		//Then save file under current name 
		if (txtCopy && this != &txtCopy)
		{
			delete[] m_textLines;
			m_textLines = nullptr;
			m_noOfLines = txtCopy.lines();
			m_textLines = new Line[m_noOfLines];

			for (unsigned int i = 0; i < m_noOfLines; i++)
			{
				m_textLines[i].m_value = new char[strLen(txtCopy.m_textLines[i].m_value) + 1];
				strCpy(m_textLines[i].m_value, txtCopy.m_textLines[i].m_value);
			}

			saveAs(m_filename);
		}

		return *this;
	}


	TextFile::operator bool()const
	{
		bool validFlag = true;
		//Check if this is a valid state
		if (!m_noOfLines)
		{
			validFlag = false;
		}
		return validFlag;
	}

	//Clean up dynamic memory in destructor
	TextFile::~TextFile()
	{
		delete[] m_textLines;
		m_textLines = nullptr;
		delete[] m_filename;
		m_filename = nullptr;
	}

	unsigned TextFile::lines()const
	{
		return m_noOfLines;
	}

	//View the file content
	ostream& TextFile::view(std::ostream& ostr)const
	{
		//Check if this file's state is valid before printing
		if (*this)
		{
			ostr << m_filename << endl;

			for (int i = 0; i < strLen(m_filename); i++)
			{
				ostr << "=";
			}
			ostr << endl;

			unsigned pSizeCount = 0;

			for (unsigned int i = 0; i < m_noOfLines; i++)
			{
				ostr << m_textLines[i].m_value << endl;
				pSizeCount++;

				//when looping through lines to print this will check if it's hit the page size limit
				//then pause the program for user input
				if (pSizeCount == m_pageSize)
				{
					cout << "Hit ENTER to continue...";
					string enterInput;
					getline(std::cin, enterInput);
					pSizeCount = 0;
				}
			}

		}
		return ostr;
	}

	//Get input from the user and load appropriate file
	istream& TextFile::getFile(istream& istr)
	{
		string fileStr;

		getline(istr, fileStr);
		setFilename(fileStr.c_str());
		setNoOfLines();
		loadText();

		return istr;
	}


	const char* TextFile::operator[](unsigned index)const
	{
		char* returnCharPtr = nullptr;
		//Check if state is valid and return null if it's not
		if (*this)
		{
			//Use modulus division to ensure the index loops back to the start from 0
			index %= m_noOfLines;
			returnCharPtr = new char[strLen(m_textLines[index].m_value) + 1];
			strCpy(returnCharPtr, m_textLines[index].m_value);
		}
	
		return returnCharPtr;
		
	}

	const char* TextFile::name()const
	{
		return m_filename;
	}

	ostream& operator<<(std::ostream& ostr, const TextFile& text)
	{
		return text.view(ostr);

	}
	std::istream& operator>>(std::istream& istr, TextFile& text)
	{
		return text.getFile(istr);
	}
}