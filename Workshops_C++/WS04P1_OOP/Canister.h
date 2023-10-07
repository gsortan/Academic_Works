/*****************************************************************************
< Workshop - #4 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
    Email : gtan16@myseneca.ca
    Section : NAA
    Date: June-08-2023
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_BOX_H
#define SDDS_BOX_H

namespace sdds {
   class Canister {
      char* m_contentName; //canister label
      double m_diameter; // in centimeters 
      double m_height;   // in centimeters
      double m_contentVolume;  // in CCs
      bool m_usable;
      //Set to default values for canister
      void setToDefault(); 
      //Set content name of canister 
      void setName(const char* Cstr);
      //Check if canister is empty
      bool isEmpty()const;
      //Check if another canister has the same labelled content
      bool hasSameContent(const Canister& C)const;
   public:
      //No argument constructor initialization
      Canister();
      //Single argument constructor using content name as param passed in
      Canister(const char* contentName);
      //Three argument constructor with the dimensions and content name as params
      Canister(double height, double diameter,
         const char* contentName = nullptr);
     //Destructor to clean up dynamically allocated memory 
      ~Canister();
      //Set the content of canister label and return reference to current object
      Canister& setContent(const char* contentName);
      //Pour the canister into another by quantity amount specified and return reference to current object
      Canister& pour(double quantity);
      //Pour the canister into another using a reference and return reference to current object
      Canister& pour(Canister&);
      //Return the volume of canister 
      double volume()const;
      //Display all the details and information to console
      std::ostream& display()const;
      //Return the total capacity of canister 
      double capacity()const;
      //used to clear up an unusuable canister and set some default values
      void clear();
   };
}

#endif // !SDDS_BOX_H
