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

#include<iostream>
#include "LibApp.h"

using namespace std;
namespace sdds {

	LibApp::LibApp() :m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_changed = false;

		m_mainMenu << "Add New Publication";
		m_mainMenu << "Remove Publication";
		m_mainMenu << "Checkout publication from library";
		m_mainMenu << "Return publication to library";

		m_exitMenu << "Save changes and exit";
		m_exitMenu << "Cancel and go back to the main menu";
		load();
	}

	bool LibApp::confirm(const char* message)
	{
		bool status = false;
		Menu m(message);
		m << "Yes";
		int succesfulRun = m.run();

		if (succesfulRun == 1)
		{
			status = true;
		}

		return status;
	}

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}

	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl << endl;
		m_changed = true;
	}

	void LibApp::newPublication()
	{

		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?"))
		{
			m_changed = true;
			cout << "Publication added" << endl;
		}
		cout << endl;
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?"))
		{
			m_changed = true;
			cout << "Publication removed" << endl;
		}
		cout << endl;
	}

	void LibApp::checkOutPub()
	{
		search();
		if (confirm("Check out publication?"))
		{
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
		cout << endl;
	}

	void LibApp::run()
	{
		bool terminate = false;
		int index = 0;
		int exitIndex = 0;

		while (!terminate)
		{
			index = m_mainMenu.run();

			if (index == 0)
			{
				if (!m_changed)
				{
					terminate = true;
					cout << endl;
					cout << "-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
				}
				else
				{
					exitIndex = m_exitMenu.run();
					if (exitIndex == 0)
					{
						terminate = confirm("This will discard all the changes are you sure?");
						if (terminate)
						{
							cout << endl;
							cout << "-------------------------------------------" << endl;
							cout << "Thanks for using Seneca Library Application" << endl;
						}
					}

					if (exitIndex == 1)
					{
						save();
						terminate = true;
						cout << endl;
						cout << "-------------------------------------------" << endl;
						cout << "Thanks for using Seneca Library Application" << endl;

					}

					if (exitIndex == 2)
					{
						cout << endl;
					}
				}
			}

			if (index == 1)
			{
				newPublication();

			}

			if (index == 2)
			{
				removePublication();

			}

			if (index == 3)
			{
				checkOutPub();
			}

			if (index == 4)
			{
				returnPub();
			}
		}
	}
}
