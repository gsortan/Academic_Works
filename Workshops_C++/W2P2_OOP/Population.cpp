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

#include <iostream>
#include "Population.h"
#include "File.h"
#include "cstring.h"

using namespace std;
namespace sdds {
    int noOfPostalCodes; 
    Population* populations;

    void sort() {
        int i, j;
        Population temp;
        for (i = noOfPostalCodes - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (populations[j].popNumber > populations[j + 1].popNumber) {
                    temp = populations[j];
                    populations[j] = populations[j + 1];
                    populations[j + 1] = temp;
                }
            }
        }
    }

    bool load(Population &pop)
    {
        bool ok = false;
        bool readSuccess = false;

        char name[128];
        int strLenghName = 0;

        readSuccess = read(name);
        readSuccess = read(pop.popNumber);

        if (readSuccess)
        {
            strLenghName = strLen(name);
            strLenghName++;

            pop.postalCode = new char[strLenghName];
            strCpy(pop.postalCode, name);

            ok = true;
        }        

        return ok;
    }

    bool load(const char* fileName)
    {
        bool ok = false;
        bool dataLoading = false;


        if (openFile(fileName)) {
            noOfPostalCodes = noOfRecords();
            populations = new Population[noOfPostalCodes];


            for (int i = 0; i < noOfPostalCodes; i++)
            {
                 dataLoading = load(populations[i]);
            }

            if (dataLoading)
            {
                ok = true;
            }
            else
            {
                cout << "Error: incorrect number of records read; the data is possibly corrupted" << endl;
            }

            closeFile();
        }

        else {
            cout << "Could not open data file: " << fileName << endl;
        }

        return ok;
    }

  

    void display()
    {
        int totalPopulation = 0;
        cout << "Postal Code: population" << endl;
        cout << "-------------------------" << endl;
      
        sort();
      
        for (int i = 0; i < noOfPostalCodes; i++)
        {
            cout << i+1 << "- "<< populations[i].postalCode << ":  " << populations[i].popNumber << endl;
           
            totalPopulation += populations[i].popNumber;
        }
        cout << "-------------------------" << endl;
        cout << "Population of Canada: " << totalPopulation<< endl;

    }

    void deallocateMemory()
    {
        for (int i = 0; i < noOfPostalCodes; i++)
        {
            delete[] populations[i].postalCode;
        }

        delete[] populations;
    }
}

