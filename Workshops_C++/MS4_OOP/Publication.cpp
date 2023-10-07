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
#include <cstring>
#include <string>
#include "Publication.h"
#include "Lib.h"
#include "Date.h"


using namespace std;
namespace sdds
{
	std::ostream& Publication::prnTitle(ostream& ostr)const
	{
		int i;
		for(i = 0; m_title[i] && i < SDDS_TITLE_WIDTH; i++) {
			ostr << m_title[i];
		}
		for(; i < SDDS_TITLE_WIDTH; i++) {
			ostr << ".";
		}
		return ostr;
	}
	Publication::Publication()
	{
		setEmpty();
	}

	Publication::Publication(const Publication& copy)
	{
		if (copy.m_title) // != nullptr
		{
			m_title = new char[strlen(copy.m_title) + 1]; // c_string
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
			m_title = nullptr;
			if (copy.m_title )
			{
				m_title = new char[strlen( copy.m_title ) + 1]; // c_string
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

		if (strstr(m_title, title)) // if found
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
			prnTitle(os);
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

		char l_title[256]{};

		char l_shelfId[5]{};
		l_shelfId[0] = '\0';

		int l_membership = 0;
		int l_libRef = -1;
		Date l_date;

		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr.getline(l_shelfId, SDDS_SHELF_ID_LEN +1);
			cout << "Title: ";
			istr.getline(l_title, 256);
			cout << "Date: ";
			istr >> l_date;
		}
		else
		{
				istr >> l_libRef;
				istr.ignore( );
				istr.getline(l_shelfId, 5,'\t');
				istr.getline(l_title, 256,'\t');
				istr >> l_membership;
				istr.ignore();
				istr >> l_date;
		}

		if (!l_date)
		{
			istr.setstate(ios::failbit);
		}

		if (istr)
		{
			m_title = new char[strlen(l_title)+1];
			strcpy(m_title, l_title);
			strcpy(m_shelfId, l_shelfId);
			set(l_membership);
			m_date = l_date;
			m_libRef = l_libRef;
		}

		return istr;
	}

	Publication::operator bool() const
	{
		bool flag = false;
		if (m_title && strcmp(m_shelfId, "") != 0)
		{
			flag = true;
		}

		return flag;
	}
}
