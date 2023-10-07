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

#ifndef SDDS_LABEL_MAKER_H 
#define SDDS_LABEL_MAKER_H
#include "Label.h"

namespace sdds
{
	class LabelMaker
	{
		Label* labels;
		int numOfLabels;

	public:
		//Label maker constructor that passes in number of labels to make
		LabelMaker(int noOfLabels);
		//Take in user input for every label in the list
		void readLabels();
		//Actually print out all the labels defined in the label list
		void printLabels();
		//Destructor to clean up any dangling dynamic allocated memory
		~LabelMaker();

	};
}
#endif
