/*****************************************************************************
< Workshop - #2 (Part - 2)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: May-27-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/


#ifndef SDDS_POPULATION_H_
#define SDDS_POPULATION_H_
namespace sdds {
	struct Population
	{
		char* postalCode;
		int popNumber;
	};
	void sort();
	bool load(const char* fileName);
	
	void display(const struct Population& pop);
	void display();
	void deallocateMemory();
		

}
#endif // SDDS_POPULATION_H_