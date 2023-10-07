/*****************************************************************************
< Final Project Milestone #4 >
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "Book.h"
#include "Lib.h"

using namespace std;
namespace sdds
{

	Book::Book()
	{
		
	}

	Book::Book(const Book& other):Publication(other)
	{
		
		if (other.authorName)
		{
			authorName = new char[AUTHOR_MAX_SZ];
			strcpy(authorName, other.authorName);
		}
	}

	Book& Book::operator=(const Book& other)
	{
		Publication::operator=(other);
		if (this != &other)
		{
			if (other.authorName)
			{
				delete[] authorName;
				authorName = new char[AUTHOR_MAX_SZ];
				strcpy(authorName, other.authorName);
			}
		}

		return *this;
	}

	Book::~Book()
	{
		delete[] authorName;
	}

	char Book::type() const
	{
		return 'B';
	}

	ostream& Book::write(ostream& os)const
	{
		Publication::write(os);

		char subString[16];

		if (conIO(os))
		{
			os << " ";
			strncpy(subString, authorName, SDDS_AUTHOR_WIDTH);
			subString[15] = '\0';
			os << subString;
			os.width(SDDS_AUTHOR_WIDTH - strlen(subString)+2);
			os << " |";
		}
		else
		{
			os << "\t" << authorName;
		}

		return os;

	}

	istream& Book::read(istream& is)
	{
		Publication::read(is);

		delete[] authorName;
		authorName = nullptr;
		//string input;
		char l_authorName[AUTHOR_MAX_SZ];

		if (conIO(is))
		{
			is.ignore();
			cout << "Author: ";
			is.getline(l_authorName, AUTHOR_MAX_SZ);
		}
		else
		{
			is.ignore();
			is.getline(l_authorName, AUTHOR_MAX_SZ);
			is.putback('\n'); //This is so it doesn't skip every other line in the file
		}

		if (!is.fail())
		{
			authorName = new char[AUTHOR_MAX_SZ];
			strcpy(authorName, l_authorName);
		}

		return is;
	}


	void Book::set(int member_id)
	{
		Publication::set(member_id);
		resetDate();
	}

	Book::operator bool() const
	{
		bool flag = false; 

		if (authorName)
		{
			if (authorName[0] != '\0' && Publication::operator bool())
			{
				flag = true; 
			}

		}
		return flag;
	}
}