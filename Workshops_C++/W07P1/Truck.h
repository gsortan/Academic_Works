/*****************************************************************************
< Workshop - #7 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
    Email : gtan16@myseneca.ca
    Section : NAA
    Date: July-17-2023
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_TRUCK_H 
#define SDDS_TRUCK_H

#include "MotorVehicle.h"
namespace sdds
{
    class Truck :public MotorVehicle
    {
        double capacity{}; //in kilograms
        double curCargoLoad;
        
    public:
        Truck(const char* lPlatNum, int y, double cap, const char* addr);
        bool addCargo(double cargo);
        bool unloadCargo();

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& in);
    };

    std::ostream& operator<<(std::ostream& ostr, const Truck& mVehicle);
    std::istream& operator>>(std::istream& istr, Truck& mVehicle);
}
#endif