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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Publication.h"
#include "Lib.h"
#include "Date.h"
#include <cstring>


using namespace std;
namespace sdds
{
	Publication::Publication()
	{
		setEmpty();
	}

	Publication::Publication(const Publication& copy)
	{
		m_title = new char[SDDS_TITLE_WIDTH];

		if (copy.m_title != nullptr)
		{
			strcpy(m_title, copy.m_title);
		}

		strcpy(m_shelfId, copy.m_shelfId);
		m_membership = copy.m_membership;
		m_libRef = copy.m_libRef;
		m_date = copy.m_date;
	}

	Publication& Publication::operator=(const Publication& copy)
	{
		if (this != &copy)
		{
			delete[] m_title;
			m_title = new char[SDDS_TITLE_WIDTH];

			if (copy.m_title != nullptr)
			{
				strcpy(m_title, copy.m_title);
			}
			strcpy(m_shelfId, copy.m_shelfId);
			m_membership = copy.m_membership;
			m_libRef = copy.m_libRef;
			m_date = copy.m_date;

		}

		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
	}

	void Publication::setEmpty()
	{

		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
	}

	void Publication::set(int member_id)
	{
		m_membership = member_id;
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date = Date();
	}

	char Publication::type()const
	{
		return 'P';
	}

	bool Publication::onLoan()const
	{
		bool checkedOut = false;

		if (m_membership != 0)
		{
			checkedOut = true;
		}

		return checkedOut;
	}

	Date Publication::checkoutDate()const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title)const
	{
		bool inTitle = false;

		if (strstr(m_title, title) != nullptr)
		{
			inTitle = true;
		}
		return inTitle;
	}

	Publication::operator const char* ()const
	{
		return m_title;
	}

	int Publication::getRef()const
	{
		return m_libRef;
	}

	bool Publication::conIO(ios& io) const
	{
		bool addressMatches = false;

		if (&io == &cin || &io == &cout)
		{
			addressMatches = true;
		}

		return addressMatches;
	}

	ostream& Publication::write(ostream& os) const
	{
		if (conIO(os))
		{
			os << "| " << m_shelfId << " | ";
			os.unsetf(ios::right);
			os.setf(ios::left);
			os.width(30);
			os.fill('.');
			os << m_title;
			os.unsetf(ios::left);
			os.setf(ios::right);
			os.fill(' ');
			if (m_membership != 0)
			{
				os << " | " << m_membership << " | " << m_date << " |";
			}
			else
			{
				os << " |  " << "N/A" << "  | " << m_date << " |";
			}
		}
		else
		{
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" <<
				m_membership << "\t" << m_date;

		}
		return os;
	}

	istream& Publication::read(istream& istr)
	{
		setEmpty();
		string inputStr;

		char* l_title = new char[SDDS_TITLE_WIDTH];
		l_title[0] = '\0';

		char l_shelfId[4 + 1];
		l_shelfId[0] = '\0';

		int l_membership = 0;
		int l_libRef = -1;
		Date l_date;

		if (conIO(istr))
		{
			cout << "Shelf No: ";
			char input[5 + 1] = {};
			istr.get(input, 6);
			if (strlen(input) != SDDS_SHELF_ID_LEN)
			{
				istr.setstate(ios::failbit);
			}
			else
			{
				strcpy(l_shelfId, input);
			}

			cout << "Title: ";
			istr.ignore(1000, '\n');

			getline(istr, inputStr);
			strcpy(l_title, inputStr.c_str());

			cout << "Date: ";

			istr >> l_date;

		}
		else
		{
			getline(istr, inputStr, '\t');
			if (!inputStr.empty())
			{
				l_libRef = stoi(inputStr.c_str());
				getline(istr, inputStr, '\t');
				strcpy(l_shelfId, inputStr.c_str());
				getline(istr, inputStr, '\t');
				strcpy(l_title, inputStr.c_str());
				getline(istr, inputStr, '\t');
				l_membership = stoi(inputStr.c_str());
				istr >> l_date;
			}
		}

		if (!l_date)
		{
			istr.setstate(ios::failbit);
		}

		if (!istr.fail())
		{
			m_title = new char[SDDS_TITLE_WIDTH];
			strcpy(m_title, l_title);

			strcpy(m_shelfId, l_shelfId);

			set(l_membership);
			m_date = l_date;
			m_libRef = l_libRef;
		}

		delete[] l_title;

		return istr;
	}

	Publication::operator bool() const
	{
		bool flag = false;
		if (m_title != nullptr && strcmp(m_shelfId, "") != 0)
		{
			flag = true;
		}

		return flag;
	}
}
