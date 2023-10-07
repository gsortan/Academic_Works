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


#ifndef SDDS_MOTORVEHICLE_H 
#define SDDS_MOTORVEHICLE_H

#include<iostream>

namespace sdds
{
	class MotorVehicle
	{
		char licensePlateNum[9];
		char address[64];
		int yearBuilt;

	public:

		MotorVehicle(const char * lPlatNum, int y);
		void moveTo(const char* newAddress);
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& in);
	};
	std::ostream& operator<<(std::ostream& ostr, const MotorVehicle& mVehicle) ;
	std::istream& operator>>(std::istream& istr, MotorVehicle& mVehicle);

}
#endif
