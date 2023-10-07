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

#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_

#define DATAFILE "employees.csv"
namespace sdds {
    struct Employee {
        char* m_name;
        int m_empNo;
        double m_salary;
    };
    //sorts the dynamic array of employees based on the GPA of the employees.
    void sort();
    // loads a employee structue with its values from the file
    bool load();
    // allocates the dyanmic array of employees and loads all the file
    // recoreds into the array
    bool load();

   
    // displays a employee record on the screen:
    void display(const struct Employee &emp);

    // first sorts the employees then displays all the employees on the screen
    void display();
    
    void deallocateMemory();
    // first will deallocate all the names in the employee elements
    // then it will deallocate the employee array 
}
#endif // SDDS_EMPLOYEE_H_