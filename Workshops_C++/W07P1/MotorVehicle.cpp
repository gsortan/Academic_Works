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

#define _CRT_SECURE_NO_WARNINGS

#include "MotorVehicle.h"
#include "cstring.h"

using namespace std;

namespace sdds
{
	MotorVehicle::MotorVehicle(const char * lPlateNum, int y)
	{
		strCpy(licensePlateNum, lPlateNum);
		yearBuilt = y;
		strCpy(address, "Factory");
	}

	void MotorVehicle::moveTo(const char* newAddress)
	{
		
		cout << "|";
		cout.width(8); 
		cout << licensePlateNum;
		cout << "| |";
		cout.width(20);
		cout << address; 
		cout << " ---> ";
		cout.unsetf(ios::right);
		cout.setf(ios::left);
		cout.width(20);
		cout << newAddress << "|" <<endl;
		strCpy(address, newAddress);
		cout.unsetf(ios::left);
		cout.setf(ios::right);
		
	}

	ostream& MotorVehicle::write(ostream& os) const
	{
		os << "| " << yearBuilt<<" | "<< licensePlateNum << " | " << address;
		return os;
	}

	istream& MotorVehicle::read(istream& in)
	{
		cout << "Built year: ";
		in >> yearBuilt;
		cout << "License plate: ";
		in >> licensePlateNum;
		cout << "Current location: ";
		in >> address;

		return in;
	}

	ostream& operator<<(ostream& ostr,  const MotorVehicle& mVehicle)
	{
		return mVehicle.write(ostr);

	}
	istream& operator>>(istream& istr, MotorVehicle& mVehicle)
	{
		return mVehicle.read(istr);
	}
}
