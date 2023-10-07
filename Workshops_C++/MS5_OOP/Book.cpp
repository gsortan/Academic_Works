/*****************************************************************************
< Final Project Milestone #5 >
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: August-6th-2023
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
	Book::Book(const Book& other):Publication(other)
	{
		
		if (other.m_authorName)
		{
			m_authorName = new char[AUTHOR_MAX_SZ];
			strcpy(m_authorName, other.m_authorName);
		}
	}

	Book& Book::operator=(const Book& other)
	{
		Publication::operator=(other);
		if (this != &other)
		{
			if (other.m_authorName)
			{
				delete[] m_authorName;
				m_authorName = new char[AUTHOR_MAX_SZ];
				strcpy(m_authorName, other.m_authorName);
			}
		}

		return *this;
	}

	Book::~Book()
	{
		delete[] m_authorName;
	}

	char Book::type() const
	{
		return 'B';
	}

	ostream& Book::write(ostream& os)const
	{
		Publication::write(os);

		char subString[16]{};

		if (conIO(os))
		{
			os << " ";
			prnInWidth(os, SDDS_AUTHOR_WIDTH, m_authorName);
			os << " |";
		}
		else
		{
			os << "\t" << m_authorName;
		}

		return os;

	}

	istream& Book::read(istream& is)
	{
		Publication::read(is);

		delete[] m_authorName;
		m_authorName = nullptr;
		
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
		}

		if (!is.fail())
		{
			m_authorName = new char[AUTHOR_MAX_SZ];
			strcpy(m_authorName, l_authorName);
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

		if (m_authorName)
		{
			if (m_authorName[0] != '\0' && Publication::operator bool())
			{
				flag = true; 
			}

		}
		return flag;
	}
}