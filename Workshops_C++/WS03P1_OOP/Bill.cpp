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
#include "Bill.h"
using namespace std;

namespace sdds {

	//Set the empty state with pointer to null and first element of title to null char
	void Bill::setEmpty()
	{
		m_title[0] = '\0';
		m_items = nullptr;
	}

	//Check if valid bill
	bool Bill::isValid()const
	{
		/*Test if title is not null stringand items pointer is not null then
		loop through each item to see if it's valid, return value if it's valid bill or not*/
		bool valid = true; 
		
		if (m_title[0] != '\0' && m_items != NULL)
		{
			for (int i = 0; i < m_noOfItems; i++)
			{
				if (!m_items[i].isValid())
				{
					valid = false;
				}
			}
		}
		return valid; 
	}

	//Return value of calculated total taxes
	double Bill::totalTax()const
	{
		double taxSum = 0;
		/* calculate the total tax by looping through item lists and summing up taxes with calling item's
		tax function */

		for(int i =0; i < m_noOfItems; i++)
		{
			taxSum+= m_items[i].tax();
		}
		return taxSum;
	}

	//Calculate total price without the inclusion of taxes and return value
	double Bill::totalPrice()const
	{
		double totalSum = 0;
		//Loop through entire list of items and add up every single item for total sum which is returned
		for (int i = 0; i < m_noOfItems; i++)
		{
			totalSum += m_items[i].price();
		}
		
		return totalSum; 
	}

	//Display title of bill
	void Bill::Title()const
	{
		int totalPadding = 0;

		cout << "+--------------------------------------+" << endl;

		//Print out title pending on if bill is valid or not
		if(isValid()) 
		{ 
			totalPadding = 36 - strLen(m_title) + 2; //Calculate required correct padding for formatting of text
			cout << "| ";
			cout << m_title;
			
			cout.width(totalPadding);
			cout << " |" << endl;
			
			cout << "+----------------------+---------+-----+" << endl;
			cout << "| Item Name            | Price   + Tax |" << endl;
			cout << "+----------------------+---------+-----+" << endl;
		}
		else
		{
			cout << "| Invalid Bill                         |"<< endl;
			cout << "+----------------------+---------+-----+" << endl;
			cout << "| Item Name            | Price   + Tax |" << endl;
			cout << "+----------------------+---------+-----+" << endl;
		}

	}

	void Bill::footer()const
	{
		cout<<"+----------------------+---------+-----+"<< endl;
	}

	//Bill initialization with title and the number of ites
	void Bill::init(const char* title, int noOfItems)
	{
		/*If upon initialization it is not in the empty state set values of the bill
		with arguments from function otherwise set this to an empty state
		*/
		if (title != NULL && noOfItems > 0)
		{
			m_noOfItems = noOfItems;
			m_itemsAdded = 0;
			strCpy(m_title, title);
			m_items = new Item[noOfItems];

			for (int i = 0; i < noOfItems; i++)
			{
				m_items[i].setEmpty();
			}
		}
		else
		{
			setEmpty();
		}
	}

	//Add an item to the bill with these defined parameters and return if it was succesfully added
	bool Bill::add(const char* item_name, double price, bool taxed)
	{
		/*Check if the number of items added is less than the maximum number defined for the bill
		if it is add to item list and initialize appropriately with set function*/
		if (m_itemsAdded < m_noOfItems)
		{
			m_items[m_itemsAdded].set(item_name, price, taxed);
			m_itemsAdded += 1;

			return true;
		}
		else
		{
			return false; 
		}
	}

	//Display the bill with items
	void Bill::display()const
	{
		Title();//Show the title

		//Loop through individual items and print them out to console
		for (int i = 0; i < m_noOfItems; i++)
		{
			m_items[i].display();
		}

		footer();//Add bottom footer

		//Check if the bill is valid and print out all totals
		if (isValid())
		{
			cout << "|                Total Tax: ";
			cout.width(10);
			cout << totalTax();
			cout << " |" << endl;

			cout << "|              Total Price: ";
			cout.width(10);
			cout << totalPrice();
			cout << " |" << endl;

			cout << "|          Total After Tax: ";
			cout.width(10);
			cout << totalPrice() + totalTax();
			cout << " |" << endl;
			cout << "+--------------------------------------+" << endl;
		}
	
		if (!isValid())
		{
			cout << "| Invalid Bill                         |" << endl;
			cout << "+--------------------------------------+" << endl;
		}
	}
	
	//Clean up the dynamic memory that was allocated with deallocation
	void Bill::deallocate()
	{
		//Delete the list of item list pointer and set that to null for safety in case pointer is used again
		delete[] m_items;
		m_items = NULL;
	}

}