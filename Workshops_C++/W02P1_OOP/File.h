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

#ifndef SDDS_FILE_H_
#define SDDS_FILE_H_
namespace sdds {
   bool openFile(const char filename[]);
   void closeFile();
   int noOfRecords();

   bool read(char* fileName);
   bool read(int& employeeNumber);
   bool read(double& employeeSalary);

}
#endif // !SDDS_FILE_H_
