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

#include <limits>
#include "Label.h"
#include "cstring.h"

using namespace std;
namespace sdds
{
	//Default constructor to make object
	Label::Label()
	{
		//allocate memory for the label text and make a blank label with default frame
		labelText = new char[MAX_SIZE];
		strCpy(labelFrame, "+-+|+-+|");
		strCpy(labelText, "");
	}

	//One argument constructor with frame argument to make object
	Label::Label(const char* frameArg)
	{
		//Check if frame argument is valid and the correct numbr of characters or else make an empty default label
		if (frameArg != nullptr && strLen(frameArg) == 8)
		{
			//Allocate memory and make new label plus frame provided by param
			labelText = new char[MAX_SIZE];
			strCpy(labelFrame, frameArg);
			strCpy(labelText, "");
		}
		else
		{
			*this = Label();
		}
	}

	//2 argument constructor that sets both the frame argument and the content of the label
	Label::Label(const char* frameArg, const char* content)
	{
		//Check if valid frame and content label within the right size to set values else make an empty label
		if (frameArg != NULL && strLen(frameArg) == 8 && content != NULL && strLen(content) <= 70)
		{
			//Allocate dynamic memory and use params passed in
			labelText = new char[MAX_SIZE];
			strCpy(labelFrame, frameArg);
			strCpy(labelText, content);
		}
		else
		{
			*this = Label();
		}
	}

	//Read user input for what is on label
	void Label::readLabel()
	{
		cout << "> ";
		//Only read up to the maximum size in the buffer which is up to 70 chars
		cin.get(labelText, MAX_SIZE);
		//ensure the new line character left in input buffer doesn't skip over a line 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	//prints the label with the correct formatting 
	std::ostream& Label::printLabel() const
	{
		//Calculation for label size
		int szOfLabel = strLen(labelText) + 2;

		//Make sure the label text is not an empty one and then draw the entire frame of the label
		//based on calculated size for text 
		if (strCmp(labelText, "") != 0)
		{
			cout << labelFrame[0];

			for (int i = 0; i < szOfLabel; i++)
			{
				cout << labelFrame[1];
			}

			cout << labelFrame[2] << endl;

			for (int i = 0; i < 3; i++)
			{
				cout << labelFrame[7];

				if (i == 1)
				{
					cout << " " << labelText;
					cout.width(2);
				}

				if (i != 1)
				{
					cout.width(szOfLabel + 1);
				}
				cout << labelFrame[3] << endl;
			}

			cout << labelFrame[6];

			for (int i = 0; i < szOfLabel; i++)
			{
				cout << labelFrame[5];
			}

			cout << labelFrame[4];
		}

		return cout;

	}

	//Delete dynamically allocated memory of the label text and set pointer to null 
	Label::~Label()
	{
		delete[] labelText;
		labelText = nullptr;
	}

}