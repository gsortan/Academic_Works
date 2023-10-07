/*****************************************************************************
< Workshop - #4 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-08-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "cstring.h"  // using strLen, strCpy and strCmp 
#include "Canister.h"

#define PI 3.14159265 //PI constant defined 

using namespace std;
namespace sdds {

	//Set default values for canister with dimensions, name and usability. 
	void Canister::setToDefault()
	{
		m_contentName = NULL;
		m_diameter = 10.0; // in centimeters 
		m_height = 13.0;   // in centimeters
		m_contentVolume = 0.0;  // in CCs
		m_usable = true; // a fl
	}

	//Check if the canister is empty 
	bool Canister::isEmpty()const
	{
		if (m_contentVolume < 0.00001)
		{
			return true;
		}

		return false;
	}

	//Test if another canister has the exact name through a string comparison and it's not null
	bool Canister::hasSameContent(const Canister& C)const
	{
		if (m_contentName != NULL && C.m_contentName != NULL)
		{
			if (strCmp(m_contentName, C.m_contentName) == 0)
			{
				return true;
			}
		}

		return false;
	}

	//Set the name of the canister 
	void Canister::setName(const char* Cstr)
	{
		// Ensure name passed is not invalid and canister is usable before setting the content name here
		if (Cstr != NULL && m_usable) 
		{
			delete [] m_contentName;
			m_contentName = new char[strLen(Cstr) + 1];
			strCpy(m_contentName, Cstr);
		}
	}

	//Default no argument constructer to set to default state
	Canister::Canister()
	{
		setToDefault();
	}

	//One argument constructer setting default values and then setting the name of content
	Canister::Canister(const char* contentName)
	{
		setToDefault();
		setName(contentName);
	}

	//three arguments constructor setting to default and dimensions and content name
	Canister::Canister(double height, double diameter, const char* contentName)
	{
		setToDefault();

		//Check to make sure the dimensions passed in are valid first before setting up this object's dimensions
		//and name else this is set to a non-useable canister
		if (height <= 40 && height >= 10 && diameter <= 30 && diameter >= 10)
		{
			m_height = height;
			m_diameter = diameter;
			setName(contentName);
		}
		else
		{
			m_usable = false; 
		}
	}

	//Destructor for deallocating dynamic memory
	Canister::~Canister()
	{
		//Deallocate dynamic memory for content name and then set to NULL 
		delete [] m_contentName;
		m_contentName = NULL;
	}

	//used to clear an unusable canister back to an empty by deallocating dynamic memory of content name
	//and setting some default values, setting it's state to useable again
	void Canister::clear()
	{
		delete [] m_contentName;
		m_contentName = nullptr;
		m_contentVolume = 0.0;
		m_usable = true;
	}

	//Calculate the capacity and return value
	double Canister::capacity() const
	{
		//the total capacity is calculated through this formula 
		double capacity = PI * (m_height - 0.267) * (m_diameter / 2) * (m_diameter / 2);

		return capacity;
	}

	//Return the content volume of canister 
	double Canister::volume() const
	{
		return m_contentVolume;
	}

	//Set content name of canister and return reference to current object
	Canister& Canister::setContent(const char* contentName)
	{
		//If the name is invalid this canister is set to not usable
		if (contentName == NULL)
		{
			m_usable = false;
		}
		//If it's empty set the name of canister content
		else if (isEmpty()) 
		{
			setName(contentName);
		}

		//If the name of the passed in content does not match this canister set this to an unusable state
		else if (!hasSameContent(contentName))
		{
			m_usable = false;
		}

		return *this;
	}

	//Pour the contents of the canister into another based on the amount specified in argument
	//return a reference to this current object
	Canister& Canister::pour(double quantity)
	{
		int tempAddedQuantity = 0;

		//Add up the current volume and quantity passed in first
		tempAddedQuantity = volume() + quantity; 

		//Check if it's a usable canister and that the quantity is bigger than zero but 
		//also less than the maximum capacity for this canister before adding anything. Else the canister
		//is not useable 
		if (m_usable && quantity > 0 && tempAddedQuantity <= capacity())
		{
			m_contentVolume += quantity;
		}
		else
		{
			m_usable = false; 
		}

		return *this;
	}

	//Pour a canister into another through passing a reference and return reference to current object
	Canister& Canister::pour(Canister& C)
	{
		//set content of canister with content name of arg passed in
		setContent(C.m_contentName); 

		double total = capacity() - volume(); 

		//Check if the volume of the canister passed in is greater than this current canister object
		if (C.volume() > total)
		{
			//Subtract the volume of passed in canister by whatever room is left in this canister
			//Set the volume of this canister to max capacity and it's now full
			C.m_contentVolume -= capacity() - volume(); 
			m_contentVolume = capacity(); 
		}
		else
		{
			//pour entire remaining volume of passed in canister
			//Passed in canister is now completely empty
			pour(C.m_contentVolume);
			C.m_contentVolume = 0.0;
		}

		return *this;
	}

	//Display all information about canisters by printing out to console and properly format with spacing
	//return cout object
	std::ostream& Canister::display()const
	{
		//Set a fixed format to print out to one decimal place
		cout.setf(ios::fixed);
		cout.precision(1);
		cout.width(7);
		cout << capacity();
		
		cout << "cc (";
		cout << m_height;
		cout << "x";
		cout << m_diameter;
		cout << ") Canister";

		if (!m_usable) //print if it's not a useable canister
		{
			cout << " of Unusable content, discard!";
		}
		else if(m_contentName!=NULL) //print the volume if the content name is valid 
		{
			cout << " of ";
			cout.width(7);
			cout << volume();
			cout << "cc   ";
			cout << m_contentName;
		}

		return cout;
	}

   
}