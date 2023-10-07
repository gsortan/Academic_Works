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

#include <iostream>
#include "LabelMaker.h"

using namespace std;
namespace sdds
{
	//Constructor for the label maker taking in one argument of the number of labels to be created
	LabelMaker::LabelMaker(int noOfLabels)
	{
		//check if valid number and then dynamically allocate list of labels and set label number
		//otherwise set to empty state with no labels 
		if (noOfLabels > 0)
		{
			labels = new Label[noOfLabels];
			numOfLabels = noOfLabels;
		}
		else
		{
			labels = nullptr;
			numOfLabels = 0;
		}
	}

	//Take in user input for each label in the label list for what text it will display
	void LabelMaker::readLabels()
	{
		if (numOfLabels != 0)//Check if there's at least one label
		{
			cout << "Enter " << numOfLabels << " labels:" << endl;

			for (int i = 0; i < numOfLabels; i++) //Loop through label list 
			{
				cout << "Enter label number " << i + 1 << endl;
				labels[i].readLabel();
			}
		}
	}

	//Print out the entire list of labels to console
	void LabelMaker::printLabels()
	{
		if (numOfLabels != 0)//Check if there is at least one label
		{
			for (int i = 0; i < numOfLabels; i++) //Loop through entire list of labels specified
			{
				labels[i].printLabel();
				cout << endl;
			}
		}
	}

	//Delete and clean up dynamically allocated array of labels an set to null pointer for safety 
	LabelMaker::~LabelMaker()
	{
		delete[] labels;
		labels = nullptr;
	}
}