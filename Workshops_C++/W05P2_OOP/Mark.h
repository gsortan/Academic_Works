/*****************************************************************************
< Workshop - #5 (Part - 2)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-17-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_MARK_H_
#define SDDS_MARK_H_

namespace sdds {
	class Mark {
		int m_mark;
		//Set mark to an invalid empty state
		void setEmpty();
	public:
		//Default constructor if no value is provided mark is 0
		Mark();
		//One argument constructor to set the mark with
		Mark(int markSet);
		//Casting mark into integer type, if it's not valid return 0 else return the mark value
		operator int() const;
		//Do a double cast for mark into a GPA 
		operator double() const;
		//casting operation for conversion of mark into a letter grade
		operator char() const;
		//Assignment operator used to assign an integer value to mark object 
		//and return reference to currenct object
		Mark& operator=(const int& markNum);
		//Adds an integer value to the mark with += overloaded operator 
		//and return reference to current object
		Mark& operator+=(int mAdd);
		
	};

	//Helper functions 
	//+= operator overload where you can add the mark to the integer value and return integer value
	int operator+=(int& left, const Mark& right);

}
#endif // SDDS_MARK_H_