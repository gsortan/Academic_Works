/*****************************************************************************
< Final Project Milestone #2 >
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-14-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS 
#include<string>
#include<cstring>
#include "Menu.h"

using namespace std;

namespace sdds
{
	MenuItem::MenuItem()
	{
		content = NULL;
	}

	MenuItem::MenuItem(const char* contentDesc)
	{
		if (contentDesc != NULL)
		{
			content = new char[strlen(contentDesc) + 1];
			strcpy(content, contentDesc);
		}
		else
		{
			content = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] content;
	}

	MenuItem::operator bool()const
	{
		if (content == NULL)
		{
			return false;
		}

		return true;
	}
	MenuItem::operator const char* ()const
	{
		return content;
	}

	ostream& MenuItem::view(std::ostream& ostr)const
	{
		if (content != NULL)
		{
			ostr << content;
		}

		return ostr;
	}

	Menu::Menu()
	{
		titleOfMenu = nullptr;

		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
		{
			menuItemList[i] = nullptr;
		}
		m_itemsCount = 0;
	}

	Menu::Menu(const char* titleName)
	{
		titleOfMenu = new MenuItem(titleName);

		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++)
		{
			menuItemList[i] = nullptr;
		}

		m_itemsCount = 0;
	}

	Menu::~Menu()
	{
		delete titleOfMenu;

		for (int i = 0; i < m_itemsCount; i++)
		{
			delete menuItemList[i];
		}
	}

	ostream& Menu::displayTitle(std::ostream& ostr)const
	{
		if (titleOfMenu != NULL)
		{
			titleOfMenu->view(ostr);
		}
		return ostr;
	}

	ostream& Menu::displayFullMenu(std::ostream& ostr) const
	{
		if (titleOfMenu != NULL)
		{
			titleOfMenu->view(ostr) << endl;
		}

		for (int i = 0; i < m_itemsCount; i++)
		{
			ostr << " " << i + 1 << "- " << menuItemList[i]->content << endl;
		}

		ostr << " 0- Exit" << endl;
		ostr << "> ";
		return ostr;
	}

	unsigned int Menu::run() const
	{
		bool validIntInput = false;
		string input;
		char* errCheck;

		bool succesConver = false;

		int integerCheck = -1; 
		
		displayFullMenu(cout);

		while (!validIntInput)
		{
			getline(cin, input);

			if (input[0] == '\n')
			{
				getline(cin, input);
			}

			//Test if valid integer is input for conversion
			//and store the invalid chars in a char pointer for that purpose 
			integerCheck = strtol(input.c_str(),&errCheck,10);

			if (input == "0")
			{
				succesConver = true;
			}
			
			if (integerCheck > 0 && strcmp(errCheck, "\0") == 0)
			{
				succesConver = true;
			}

			if (succesConver && integerCheck <= m_itemsCount)
			{
				validIntInput = true;
			}
			else
			{
				cout << "Invalid Selection, try again: ";
			}
		}
		
		return (unsigned int)integerCheck;
	}

	unsigned int Menu::operator~() 
	{
		return run();
	}

	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if ((unsigned int)m_itemsCount < MAX_MENU_ITEMS)
		{
			menuItemList[m_itemsCount] = new MenuItem(menuitemConent);
			m_itemsCount++;
		}
		return *this;
	}

	Menu::operator int()const
	{
		return m_itemsCount;
	}

	Menu::operator unsigned int()const
	{
		return m_itemsCount;
	}

	Menu::operator bool()const
	{
		bool valid = false;

		if (m_itemsCount > 0)
		{
			valid = true;
		}

		return valid; 
	}

	const char* Menu::operator[](unsigned index)const
	{
		//Use modulus division to loop the index back to the start from 0
		index %= MAX_MENU_ITEMS;

		return (const char*)(*menuItemList[index]);
	}


	ostream& operator<<(ostream& ostr, const Menu& m_title)
	{
		return m_title.displayTitle(ostr);
	}


}