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

#ifndef SDDS_FOOD_H_
#define SDDS_FOOD_H_

namespace sdds {
	class Food {

		char m_foodName[30];
		int calories;
		int timeOfConsumption;
		void setName(const char* name);//Set the name of the food item  

	public:
		//Set to safe empty state 
		void setEmpty();
		//Set the food item variables with the name, calories and time of consumption
		void set(const char* name, int cal, int timeOfCons);
		//Display and print out food item to console
		void display()const;
		//Check and see if this food item is valid or the safe empty state
		bool isValid()const;
		//Return the number of calories of this food item
		int getCalories()const;
	};
}

#endif // !SDDS_SUBJECT_H
