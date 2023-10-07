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

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>

namespace sdds {

	class MenuItem
	{
		MenuItem();
		MenuItem(const char* contentDesc);
		~MenuItem();

		char* content;
		friend class Menu;

		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem&) = delete;

		operator bool()const;
		operator const char* ()const;
		std::ostream& view(std::ostream& ostr)const;
	};

	const unsigned int MAX_MENU_ITEMS = 20;

	class Menu
	{
		MenuItem* titleOfMenu;
		MenuItem* menuItemList[MAX_MENU_ITEMS];
		int m_itemsCount;

	public:
		Menu();
		Menu(const char* contentDesc);
		~Menu();

		std::ostream& displayTitle(std::ostream& ostr)const;
		std::ostream& displayFullMenu(std::ostream& ostr) const;

		Menu(const Menu&) = delete;
		void operator=(const Menu&) = delete;

		unsigned int run() const;
		unsigned int operator~();
		Menu& operator<<(const char* menuitemConent);
		operator int() const;
		operator unsigned int()const;
		operator bool()const;
		const char* operator[](unsigned index)const;

	};

	std::ostream& operator<<(std::ostream& ostr, const Menu& m_title);

}
#endif