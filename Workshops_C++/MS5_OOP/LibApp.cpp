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
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <fstream>
#include <cstring>
#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;
namespace sdds {

	LibApp::LibApp(const char * fName) :m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		pubTypeMenu("Choose the type of publication:")
	{
		if (fName)
		{
			strcpy(fileName, fName);
		}

		m_changed = false;

		m_mainMenu << "Add New Publication";
		m_mainMenu << "Remove Publication";
		m_mainMenu << "Checkout publication from library";
		m_mainMenu << "Return publication to library";

		m_exitMenu << "Save changes and exit";
		m_exitMenu << "Cancel and go back to the main menu";

		pubTypeMenu << "Book";
		pubTypeMenu << "Publication";

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

	void prnPub(Publication* p[], int size, int ref) {
		int i;
		for (i = 0; i < size; i++) {
			if (ref == p[i]->getRef()) {
				cout << *p[i] << endl;
				i = size; 
			}
		}
	}

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
		char type{};
		ifstream fileInput(fileName);

		for (int i = 0; fileInput; i++)
		{
			fileInput >> type;
			fileInput.ignore();
			if (type == 'P' && !fileInput.fail())
			{
				pubList[i] = new Publication;				
			}
			else if(type == 'B' && !fileInput.fail())
			{
				pubList[i] = new Book;
			}
			if (pubList[i])
			{
				fileInput >> *pubList[i];
				NOLP++;
				LLRN = pubList[i]->getRef();
			}
		}
		fileInput.close();

	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
		ofstream outFile(fileName);

		for(int i = 0; i < NOLP; i++)
		{
			if (pubList[i]->getRef() != 0)
			{
				outFile << *pubList[i] << '\n';
			}
		}

		outFile.close();
	}

	int LibApp::search(int searchMode)
	{
		PublicationSelector pubSelect("Select one of the following found matches:");
		int index = pubTypeMenu.run();

		char selectedType{};
		char titleToSearch[256];

		int ref = -1;

		if (index == 1)
		{
			selectedType = 'B';
		}
		else if (index == 2)
		{
			selectedType = 'P';
		}

		if (index != 0)
		{
			cout << "Publication Title: ";

			cin.getline(titleToSearch, 256);

			for (int i = 0; i < NOLP; i++)
			{

				if (searchMode == 1 && pubList[i]->getRef()
					&& pubList[i]->type() == selectedType &&
					strstr(*pubList[i], titleToSearch))
				{
					pubSelect << pubList[i];
				}

				if (pubList[i]->onLoan() && searchMode == 2 && pubList[i]->getRef()
					&& pubList[i]->type() == selectedType && strstr(*pubList[i], titleToSearch))
				{
					pubSelect << pubList[i];
				}

				if (!pubList[i]->onLoan() && searchMode == 3 && pubList[i]->getRef()
					&& pubList[i]->type() == selectedType && strstr(*pubList[i], titleToSearch))
				{
					pubSelect << pubList[i];
				}
			}

			if (pubSelect)
			{
				pubSelect.sort();
				ref = pubSelect.run();
				if (ref)
				{			
					prnPub(pubList, NOLP, ref);
				}
				else
				{
					ref = -1;
					cout << "Aborted!" << endl << endl;
				}
			}
			else
			{
				cout << "No matches found!" << endl << endl;
			}
		}
		else
		{
			cout << "Aborted!" << endl << endl;
		}
		return ref;
	}

	Publication* LibApp::getPub(int libRef)
	{
		Publication* pubF = nullptr;

		for (int i = 0; i < NOLP && !pubF; i++)
		{
			if (pubList[i]->getRef() == libRef)
			{
				pubF = pubList[i];
			}
		}
		return pubF;
	}

	void LibApp::returnPub()
	{
		cout << "Return publication to the library" << endl;
		int pubReturnNum = search(2);
		Date curDay; 
		int numOfCheckOutDays = 0;
		int numOfLateDays = 0;
		double lateFee = 0.0;

		if (pubReturnNum != -1)
		{
			if (confirm("Return Publication?"))
			{
				numOfCheckOutDays = curDay - getPub(pubReturnNum)->checkoutDate();
				numOfLateDays = numOfCheckOutDays - SDDS_MAX_LOAN_DAYS;

				if (numOfCheckOutDays > SDDS_MAX_LOAN_DAYS)
				{
					lateFee = numOfLateDays * 0.50;
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << "Please pay $" << lateFee<<" penalty for being " << numOfLateDays
						<<" days late!" << endl;
				}
				getPub(pubReturnNum)->set(0);
				m_changed = true;
			
				cout << "Publication returned" << endl << endl;
			}
		}
	}

	void LibApp::newPublication()
	{
		Publication* newPub = nullptr;
		int index = -1;

		if (NOLP == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!"<<endl << endl;
		} 
		else
		{
			cout << "Adding new publication to the library" << endl;

			index = pubTypeMenu.run();

			if (index == 1)
			{
				newPub = new Book;
				cin >> *newPub;
			}

			if (index == 2)
			{
				newPub = new Publication;
				cin >> *newPub;
				cin.ignore();
			}

			if (index != 0)
			{
				if (confirm("Add this publication to the library?"))
				{
					if (newPub)
					{
						m_changed = true;
						LLRN++;
						newPub->setRef(LLRN);
						pubList[NOLP] = newPub;
						NOLP++;
						cout << "Publication added" << endl;
					}
					else
					{
						cout << "Failed to add publication!" << endl;
						delete newPub;
						newPub = nullptr;
					}
				}
				else
				{
					cout << "Aborted!" << endl;
				}
				cout << endl;
			}
			
		}
		if (index == 0)
		{
			cout << "Aborted!" << endl << endl;
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		int refNumToRemove = search();
		if (refNumToRemove != -1)
		{
			if (confirm("Remove this publication from the library?"))
			{
				getPub(refNumToRemove)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
			cout << endl;
		}
	}

	int LibApp::validateMembershipNum()
	{
		int memNum = 0;
		cout << "Enter Membership number: ";

		while (!memNum)
		{
			cin >> memNum;
			
			if (!cin || memNum < 10000 || memNum > 99999)
			{
				cin.clear();
				cin.ignore(1000,'\n');
				cout << "Invalid membership number, try again: ";
			}
		}
		cin.ignore(1000, '\n');
		return memNum;
	}

	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;
		int pubToCheckOut = search(3);

		if (pubToCheckOut != -1)
		{
			if (confirm("Check out publication?"))
			{
				getPub(pubToCheckOut)->set(validateMembershipNum());
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
			cout << endl;
		}
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

	LibApp::~LibApp()
	{
		for (int i = 0; i < NOLP; i++)
		{
			delete pubList[i];
		}
	}
}
