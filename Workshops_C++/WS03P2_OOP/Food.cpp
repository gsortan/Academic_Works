/*****************************************************************************
< Workshop - #3 (Part - 2)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-03-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include <iostream>
#include "Food.h"
#include "cstring.h"

using namespace std;

namespace sdds {

	//Set name of food item using a string copy
	void Food::setName(const char* name)
	{
		strCpy(m_foodName, name);
		m_foodName[30] = '\0'; //Guard against buffer overflow happening by inserting a null terminator character
	}

	//Set food item to safe empty state
	void Food::setEmpty()
	{
		m_foodName[0] = '\0';
		calories = 0;
		timeOfConsumption = 0;
	}

	//Set the food item with arguments passed in for the name, calories and time of consumption
	void Food::set(const char* name, int cal, int timeOfCons)
	{
		//Check if arguments are valid otherwise set to an empty state
		if (name != nullptr && cal > 0 && cal <= 3000 && timeOfCons >= 1 && timeOfCons <= 4)
		{
			setName(name);
			calories = cal;
			timeOfConsumption = timeOfCons;
		}
		else
		{
			setEmpty();
		}
	}

	//Return boolean value if the food item is not in an empty state
	bool Food::isValid()const
	{
		if (m_foodName[0] != '\0' && calories > 0 && calories <= 3000
			&& timeOfConsumption <= 4 && timeOfConsumption >= 1)
		{
			return true;
		}

		return false;
	}

	//Return calorie count for food item
	int Food::getCalories()const
	{
		return calories;
	}

	//Display the food item information with proper formatting 
	void Food::display()const
	{
		if (isValid()) //Check if it's a valid food item to print information else display invalid message
		{
			cout << "| ";
			cout << m_foodName;
			int paddingLength = 30 - strLen(m_foodName) + 3;//Calculation for the correct padding with the width 
			cout.width(paddingLength);
			cout.fill('.');
			cout << " | ";

			cout.fill(' ');
			cout.width(4);
			cout << calories;

			switch (timeOfConsumption)//Display correct time of consumption
			{
			case 1:
				cout << " | " << "Breakfast" << "  |" << endl;
				break;
			case 2:
				cout << " | " << "Lunch" << "      |" << endl;
				break;
			case 3:
				cout << " | " << "Dinner" << "     |" << endl;
				break;
			case 4:
				cout << " | " << "Snack" << "      |" << endl;
				break;

			}
		}

		if (!isValid())
		{
			cout << "| xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx | xxxx | xxxxxxxxxx |" << endl;
		}
	}
}