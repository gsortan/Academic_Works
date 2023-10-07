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


#include "Mark.h"

using namespace std;
namespace sdds {

	//Set mark to an invalid empty state
	void Mark::setEmpty() {
		
		m_mark = -1;
	}
	//Default constructor if no value is provided mark is 0
	Mark::Mark() {
		m_mark = 0;
	}

	//One argument constructor to set the mark with
	Mark::Mark(int markSet)
	{
		//Check if it's within the correct range else set mark to empty state
		if (markSet >= 0 && markSet <= 100)
		{
			m_mark = markSet;
		}
		else
		{
			setEmpty();
		}
	}

	//Casting mark into integer type, if it's not valid return 0 else return the mark value
	Mark::operator int() const
	{
		if (m_mark == -1)
		{
			return 0;
		}

		return m_mark;
	}

	//Do a double cast for mark into a GPA 
	Mark::operator double() const
	{
		double gpa = 0.0;
		//If it's an invalid mark, return zero for fpa
		if (m_mark == -1)
		{
			return gpa;
		}

		//Check range of mark to assign appropriate gpa to return
		if (m_mark >= 80 && m_mark <= 100)
		{
			gpa = 4.0;
		}
		else if (m_mark >= 70 && m_mark < 80)
		{
			gpa = 3.0;
		}
		else if (m_mark >= 60 && m_mark < 70)
		{
			gpa = 2.0;
		}

		else if (m_mark >= 50 && m_mark < 60)
		{
			gpa = 1.0;
		}

		return gpa;
	}

	//casting operation for conversion of mark into a letter grade
	Mark::operator char() const
	{
		char letterGrade = 'X';

		//If mark is not valid just return an 'X' grade
		if (m_mark == -1)
		{
			return letterGrade;
		}

		//Check the range of mark to give appropriate letter grade to return
		if (m_mark >= 80 && m_mark <= 100)
		{
			letterGrade = 'A';
		}
		else if (m_mark >= 70 && m_mark < 80)
		{
			letterGrade = 'B';
		}
		else if (m_mark >= 60 && m_mark < 70)
		{
			letterGrade = 'C';
		}

		else if (m_mark >= 50 && m_mark < 60)
		{
			letterGrade = 'D';
		}

		else if (m_mark < 50)
		{
			letterGrade = 'F';
		}

		return letterGrade;
	}

	//Assignment operator used to assign an integer value to mark object 
	//and return reference to currenct object
	Mark& Mark::operator=(const int& markNum)
	{
		//If it's within the right range, assign passed down mark value otherwise set to invalid empty state
		if (markNum >= 0 && markNum <= 100)
		{
			m_mark = markNum;
		}
		else
		{
			setEmpty();
		}

		return *this;
	}



	//Adds an integer value to the mark with += overloaded operator and return reference to current object
	Mark& Mark::operator+=(int mAdd) {
		//Check if mark is valid and then add to mark
		if (m_mark != -1) {
			m_mark += mAdd;
		}

		//If the mark gets out of range after adding, set to invalid empty state
		if (m_mark > 100)
		{
			setEmpty();
		}
	
		return *this;
	}


	//+= operator overload where you can add the mark to the integer value and return integer value
	int operator+=(int& left, const Mark& right)
	{
		//left side int adds right side Mark's mark with casting operator and does validity check
		//returning zero if invalid mark
		left += int(right);
		return left;
	}

}