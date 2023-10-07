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
#include <iomanip>
#include "CalorieList.h"
#include "cstring.h"

using namespace std;

namespace sdds {

	//Set a safe empty state here
	void CalorieList::setEmpty()
	{
		m_title[0] = '\0';
		food_items = nullptr;
	}

	//Initialize calorie list 
	void CalorieList::init(int size)
	{
		if (size > 0)//Only if a valid size is passed in otherwise set to empty state
		{
			m_noOfItems = size;
			m_addedItems = 0;
			food_items = new Food[m_noOfItems]; //dynamically allocate memory for food list based on size passed in

			for (int i = 0; i < m_noOfItems; i++)
			{
				food_items[i].setEmpty();//set food items to safe empty state 
			}
		}
		else
		{
			setEmpty();
		}
	}

	//Add food items to list with arguments passed in or return false if it fails to add item
	bool CalorieList::add(const char* item_name, int calories, int when)
	{
		//Ensure that the added items is not bigger than the list otherwise don't add anything 
		if (m_addedItems < m_noOfItems)
		{
			food_items[m_addedItems].set(item_name, calories, when); //set food item accordingly with values
			m_addedItems += 1; //increment number of items added by 1

			return true;
		}
		return false;
	}

	//Prints out the title 
	void CalorieList::Title()const
	{
		int totalPadding = 0;

		cout << "+----------------------------------------------------+" << endl;

		//Check if it's a valid calorie list
		if (isValid())
		{
			totalPadding = 49 - strLen(m_title) + 2; //Calculate required correct padding for formatting of text
			cout << "|  ";
			cout << m_title;

			cout.width(totalPadding);
			cout << "|" << endl;

			cout << "+--------------------------------+------+------------+" << endl;
			cout << "| Food name                      | Cals | When       |" << endl;
			cout << "+--------------------------------+------+------------+" << endl;
		}
		else
		{
			cout << "| Invalid Calorie Consumption list                   |" << endl;
			cout << "+--------------------------------+------+------------+" << endl;
			cout << "| Food name                      | Cals | When       |" << endl;
			cout << "+--------------------------------+------+------------+" << endl;
		}

	}

	//print out the footer 
	void CalorieList::footer()const
	{
		cout << "+--------------------------------+------+------------+" << endl;
	}

	//check if calorie list is actually valid 
	bool CalorieList::isValid()const
	{
		bool valid = true;

		/* If it's not in the empty state loop through item list and check if all food items are valid,
		return a false value if not*/
		if (m_title[0] != '\0' && food_items != NULL)
		{
			for (int i = 0; i < m_noOfItems; i++)
			{
				if (!food_items[i].isValid())
				{
					valid = false;
				}
			}
		}

		return valid;
	}

	//Display the calorie list
	void CalorieList::display()const
	{
		Title();

		//Loop through entire food item list to display each one
		for (int i = 0; i < m_noOfItems; i++)
		{
			food_items[i].display();
		}

		footer(); //display footer 

		//If this calorie list is valid then print out the total with correct formatting 
		if (isValid())
		{
			cout << "|    Total Calories for today:";
			cout << std::setw(9) << totalCalories() << setw(3) << "| ";
			cout << "           |" << endl;
			cout << "+----------------------------------------------------+" << endl;
		}

		//if calorie list is invalid print out that it is an invalid list 
		if (!isValid())
		{
			cout << "|    Invalid Calorie Consumption list                |" << endl;
			cout << "+----------------------------------------------------+" << endl;
		}
	}

	//Count up the total calories and retrieve that
	int CalorieList::totalCalories()const
	{
		int calorieSum = 0;

		// calculates the sum of calories in a loop from each invidiual food item
		for (int i = 0; i < m_noOfItems; i++)
		{
			calorieSum += food_items[i].getCalories();
		}
		return calorieSum;
	}

	//Deallocate the dynamic memory of the food items list pointer and then set to null in case of future use
	void CalorieList::deallocate()
	{
		delete[] food_items;
		food_items = nullptr;
	}

}