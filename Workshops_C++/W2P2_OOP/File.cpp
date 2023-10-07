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

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "File.h"

namespace sdds {
   FILE* fptr;
   bool openFile(const char filename[]) {
      fptr = fopen(filename, "r");
      return fptr != NULL;
   }
   int noOfRecords() {
      int noOfRecs = 0;
      char ch;
      while (fscanf(fptr, "%c", &ch) == 1) {
         noOfRecs += (ch == '\n');
      }
      rewind(fptr);
      return noOfRecs;
   }
   void closeFile() {
      if (fptr) fclose(fptr);
   }
  
   bool read(char* postalCode) {
       int success = 0;

       success = fscanf(fptr, " %[^,]", postalCode);

       if (success)
       {
           return true;
       }
       else
       {
           return false;
       }
   }

   bool read(int &population) {
       int success = 0;

       success = fscanf(fptr, ",%d", &population);

       if (success)
       {
           return true;
       }
       else
       {
           return false;
       }
   }
}