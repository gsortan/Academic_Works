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

#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include "Streamable.h"
#include "Date.h"

namespace sdds
{
	class Publication: public Streamable
	{

		char* m_title{};
		char m_shelfId[5]{}; //c_string
		int m_membership{};
		int m_libRef{};
		Date m_date;
		std::ostream& prnTitle(std::ostream& ostr)const;
	public:
		Publication();
		Publication (const Publication& other);
		Publication& operator=(const Publication& other);
		~Publication();

		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		void setEmpty();

		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 
		bool conIO(std::ios& io) const;

		operator bool() const;

		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& istr);

		
	};
}
#endif // !PUBLICATION_H
