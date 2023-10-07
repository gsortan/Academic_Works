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
#include "Food.h"
#ifndef SDDS_CALORIELIST_H_
#define SDDS_CALORIELIST_H_

namespace sdds {
	class CalorieList {

		char m_title[37] = "Daily Calorie Consumption";
		Food* food_items;
		int m_noOfItems;
		int m_addedItems;

		//Set the name of the item  
		void setName(const char* name);
		//Display the title of calorie list
		void Title()const;
		//Display the footer
		void footer()const;
		//Set to a safe empty state
		void setEmpty();
		//Check if this is valid or not
		bool isValid() const;
		//Return the total calories summed up by adding all food items
		int totalCalories() const;

	public:
		// sets the CalorieList to accept the "size" number of Food Items. 
		// This function is called to prepare the CalorieList for accepting food items
		void init(int size);
		// Adds Food Items using their Name, Calorie count and time of consumption up to 
		// the number set in the init() function, returns true if successful.
		bool add(const char* item_name, int calories, int when);
		// Displays the report with food information and the total calorie consumed in the day
		// as shown in the report sample
		void display()const;
		// Releases all the memory used. After this function init() can be called for another
		// report;
		void deallocate();
	};
}

#endif // !SDDS_SUBJECT_H
