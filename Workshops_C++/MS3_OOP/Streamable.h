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

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include<iostream>


namespace sdds
{
	class Streamable
	{
	public:
		virtual std::ostream& write(std::ostream& os)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual bool conIO(std::ios& iosObj) const = 0;
		virtual operator bool()const = 0;
		virtual ~Streamable();
		
	};
	std::ostream& operator<<(std::ostream& os, const Streamable& obj);
	std::istream& operator>>(std::istream& is, Streamable& obj);



}
#endif 

