/*****************************************************************************
< Workshop - #3 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
    Email : gtan16@myseneca.ca
    Section : NAA
    Date: June-01-2023
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_BILL_H_
#define SDDS_BILL_H_
#include "Item.h"

namespace sdds {
   class Bill {
      char m_title[37];
      Item* m_items;
      int m_noOfItems;
      int m_itemsAdded;

      //Return the total taxed amount
      double totalTax()const;
      //Return the total price amount without tax inclusion
      double totalPrice()const;
      //Display and print title of bill
      void Title()const;
      //Display and print footer of bill
      void footer()const;
      //Set to safe empty state with initialization
      void setEmpty();
      //Check if this bill is valid or not
      bool isValid()const;
   public:
       //Initialize bill item with these parameters passed in 
      void init(const char* title, int noOfItems);
      //Add an item to the bill with these defined parameters
      bool add(const char* item_name, double price, bool taxed);
      //Display and print full entire bill with all items
      void display()const;
      //Clean up and deallocate the memory of dynamically allocated item list
      void deallocate();
   };
}
#endif // !SDDS_TRANSCRIPT_H
