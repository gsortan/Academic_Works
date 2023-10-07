/*****************************************************************************
< Final Project Milestone #5 >
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: August-6th-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"

namespace sdds {
	class LibApp {
		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;
		Menu pubTypeMenu;

		char fileName[256]{};
		Publication* pubList[SDDS_LIBRARY_CAPACITY]{};
		int NOLP{};
		int LLRN{};

		bool confirm(const char* message);
		void load();  // prints: "Loading Data"<NEWLINE>
		void save();  // prints: "Saving Data"<NEWLINE>
		int search(int searchMode = 1);  // prints: "Searching for publication"<NEWLINE>
		int validateMembershipNum();

		Publication* getPub(int libRef);

		void returnPub();  /*  Calls the search() method.
							   prints "Returning publication"<NEWLINE>
							   prints "Publication returned"<NEWLINE>
							   sets m_changed to true;*/

		void newPublication();
		void removePublication();
		void checkOutPub();
		

	public:
		
		LibApp(const char* fName);
		virtual ~LibApp();
		void run();
	};
}
#endif // !SDDS_LIBAPP_H



