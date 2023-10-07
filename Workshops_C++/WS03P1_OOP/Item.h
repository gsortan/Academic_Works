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

#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_

namespace sdds {
   class Item {
      char m_itemName[21];
      double m_price;
      bool m_taxed;
      void setName(const char* name);//Set the name of the item  
      const double taxRate = 0.13;

   public:
       //Set to safe empty state 
      void setEmpty(); 
      //Set an item and change it's state with these parameters passed in, the name, price and if it's taxed
      void set(const char* name, double price, bool taxed);
      //Check if item is valid or not
      bool isValid()const;
      //Return the price without taxes
      double price()const;
      //Return the tax amount 
      double tax()const;
      //Display the item with text
      void display()const;
   };
}

#endif // !SDDS_SUBJECT_H
