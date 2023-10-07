/*****************************************************************************
< Workshop - #3 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-01-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include <iostream>
#include "cstring.h"
#include "Item.h"
using namespace std;

namespace sdds {

	//Set the name of the item using a string copy
	void Item::setName(const char* name)
	{
		

		strCpy(m_itemName, name);//Copy temp name to item name
	}

	//Set to safe empty state by initializing these variables for item
	void Item::setEmpty()
	{
		m_price = 0.0;
		m_itemName[0] = '\0';
		m_taxed = false; 
	}

	//Set up an item with these parameters passed in, the name, price and if it's taxed
	void Item::set(const char* name, double price, bool taxed)
	{
		/*Check if any arguments passed in are invalid if it's not set appropriate variables 
		using the arguments otherwise set to an empty state*/
		if (price >= 0 && name != NULL)
		{
			setName(name);
			m_price = price;
			m_taxed = taxed;
		}
		else
		{
			setEmpty();
		}
	}

	//Return item price 
	double Item::price() const
	{
		return m_price;
	}

	//Calculate tax for item
	double Item::tax()const
	{
		double taxedAmount = 0.0;

		/*If it's taxed calculated tax through multiplication of the price of item with tax rate otherwise
		return zero */
		if (m_taxed)
		{
			taxedAmount = m_price * taxRate;

			return taxedAmount;
		}
		else
		{
			return taxedAmount;
		}
	}

	//Return whether item is valid or not
	bool Item::isValid()const
	{
		//Check whether price is within valid range and the item name is not null
		if (m_price>=0 && m_itemName[0]!='\0')
		{
			return true;
		}
		else
		{
			return false; 
		}
	}

	//Display the item with text 
	void Item::display()const
	{
		//Check if item is valid or not, then print out to console with proper formatting 
		if (isValid())
		{
			cout << "| ";
			cout << m_itemName;
			int paddingLength = 20 - strLen(m_itemName) + 3;//Calculation for the correct padding with the width 
			cout.width(paddingLength); 
			cout.fill('.');
			cout << " | ";

			//Ensures displaying the price here in decimal fomat up to 2 decimal places precision
			cout.setf(ios::fixed);
			cout.precision(2);
			cout.fill(' ');
			cout.width(7);
			cout << m_price;

			if (m_taxed)//Check if the item is taxed or not and display appropriate message
			{
				cout << " | " << "Yes" << " |" << endl;
			}
			else
			{
				cout << " | " << "No" << "  |" << endl;
			}
		}

		if(!isValid())//If it's not valid display this
		{
			cout << "| xxxxxxxxxxxxxxxxxxxx | xxxxxxx | xxx |" <<endl;
		}
		
	}

}