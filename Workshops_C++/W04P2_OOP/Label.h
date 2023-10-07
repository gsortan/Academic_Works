/*****************************************************************************
< Workshop - #4 (Part - 2)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-10-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/


#ifndef SDDS_LABEL_H 
#define SDDS_LABEL_H
#include <iostream>
#define MAX_SIZE 70 + 1 //label maximum size

namespace sdds {
	class Label
	{
		char* labelText;
		char labelFrame[9];

	public:

		//Default label constructor for empty label
		Label();
		//one argument constructor to make label out of frame argument 
		Label(const char* frameArg);
		//two argument constructor using the frame arg and content of label
		Label(const char* frameArg, const char* content);
		//Clean up dynamically allocated memory
		~Label();

		//return cout object of ostream and print this label out
		std::ostream& printLabel()const;
		//Read in user input for the labelled text 
		void readLabel();

	};
}
#endif