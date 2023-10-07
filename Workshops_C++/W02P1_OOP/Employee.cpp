/*****************************************************************************
< Workshop - #2 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
    Email : gtan16@myseneca.ca
    Section : NAA
    Date: May-25-2023
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include <iostream>
#include "cstring.h"  
#include "Employee.h"
#include "File.h"
using namespace std;
namespace sdds {

   int noOfEmployees;
   Employee* employees;


   void sort() {
      int i, j;
      Employee temp;
      for (i = noOfEmployees - 1; i > 0; i--) {
         for (j = 0; j < i; j++) {
            if (employees[j].m_empNo > employees[j + 1].m_empNo) {
               temp = employees[j];
               employees[j] = employees[j + 1];
               employees[j + 1] = temp;
            }
         }
      }
   }

  
   bool load(Employee &employee) {
      bool ok = false;
      bool readSuccess = false; 

      char name[128];
      int strLenghName = 0;

      readSuccess = read(employee.m_empNo);
      readSuccess = read(employee.m_salary);
      readSuccess = read(name);
     
      
      if (readSuccess)
      {
          strLenghName = strLen(name);
          strLenghName++;

          employee.m_name = new char[strLenghName];
          strCpy(employee.m_name, name);

          ok = true;
      }

      return ok;
   }
  
   bool load() {
      bool ok = false;
      bool dataLoading = false;

     
      if (openFile(DATAFILE)) {
          noOfEmployees = noOfRecords();
          employees = new Employee[noOfEmployees];
          

          for (int i = 0; i < noOfEmployees; i++)
          {
             dataLoading = load(employees[i]);
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
         cout << "Could not open data file: " << DATAFILE<< endl;
      }
    
      return ok;
   }

  
   void display(const struct Employee& emp)
   {
       cout << emp.m_empNo <<": "<<emp.m_name<<", " << emp.m_salary<<endl;
   }

   void display()
   {
       cout << "Employee Salary report, sorted by employee number" << endl;
       cout << "no- Empno, Name, Salary" << endl;
       cout << "------------------------------------------------" << endl;
       sort();
       for (int i = 0; i < noOfEmployees; i++)
       {
           cout << i+1<<"- ";
           display(employees[i]);
       }

   }

   
   void deallocateMemory()
   {
       for (int i = 0; i < noOfEmployees; i++)
       {
           delete[] employees[i].m_name;
           employees[i].m_name = NULL;
       }

       delete[] employees;
       employees = NULL;
   }
}