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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
#define AUTHOR_MAX_SZ 256

namespace sdds
{
	class Book :public Publication
	{
		char* m_authorName{};

	public:
		Book() = default;
		Book(const Book& other);
		Book& operator=(const Book& other);
		~Book();
		char type() const;
		std::ostream& write(std::ostream& os)const;
		std::istream& read(std::istream& is);
		void set(int member_id);
		operator bool()const;

	};

}
#endif