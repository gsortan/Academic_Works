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

#include "Truck.h"

using namespace std;
namespace sdds
{
	Truck::Truck(const char* lPlatNum, int y, double cap, const char* addr) :
		MotorVehicle(lPlatNum, y)
	{
		capacity = cap;
		curCargoLoad = 0;
		moveTo(addr);
	}

	bool Truck::addCargo(double cargo)
	{
		bool changedLoad = false; 
			if (curCargoLoad < capacity)
			{
				curCargoLoad += cargo;
				changedLoad = true;
			}

			if (curCargoLoad > capacity)
			{
				curCargoLoad = capacity;
			}

		return changedLoad;
	}

	bool Truck::unloadCargo()
	{
		bool changedLoad = false;

		if (curCargoLoad != 0)
		{
			curCargoLoad = 0;
			changedLoad = true;
		}
		return changedLoad;
	}

	ostream& Truck::write(ostream& os) const
	{
		MotorVehicle::write(os) << " | "<<curCargoLoad<<"/"<< capacity;
		return os; 
	}


	istream& Truck::read(istream& in)
	{
		MotorVehicle::read(in);
		cout << "Capacity: ";
		in >> capacity;
		cout << "Cargo: ";
		in >> curCargoLoad;
		return in; 
	}

	ostream& operator<<(ostream& ostr, const Truck& m_truck)
	{
		return m_truck.write(ostr);

	}
	istream& operator>>(istream& istr, Truck& m_truck)
	{
		return m_truck.read(istr);
	}
}