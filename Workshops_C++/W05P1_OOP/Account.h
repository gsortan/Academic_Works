/*****************************************************************************
< Workshop - #5 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: June-13-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#ifndef SDDS_ACCOUNT_H_
#define SDDS_ACCOUNT_H_

namespace sdds {
	class Account {
		int m_number;
		double m_balance;
		//Set to empty state
		void setEmpty();
	public:
		// New account
		Account();
		//Constructor to set it to either an invalid state or using the parameters defined
		//if they are valid, set those values appropriately with them
		Account(int number, double balance);
		//Display account to console 
		std::ostream& display()const;
		//Overloaded boolean operator, check if valid account
		operator bool() const;
		//Returns the account number through overloaded int operator
		operator int() const;
		//Returns the account balance through overloaded double operator
		operator double() const;
		//Returns whether this account is a new one or not whether it's zero through 
		//through overloaded ~ operator
		bool operator~() const;
		//Assignment operator overloaded to assign account number to a new account 
		Account& operator=(const int& accNum);
		//Assignment sign operator overloaded to take in reference of account object 
		//to move the balance of this into a new account
		Account& operator=(Account& otherAcc);
		//Deposting into account with overloaded operator by double parameter 
		Account& operator+=(double money);
		//Withdrawing from the account with overloaded operator by double parameter
		Account& operator-=(double money);
		//Overloaded operator for taking in reference to account object and shifting
		//the right operand account's balance to the left operand's balance
		Account& operator<<(Account& otherAcc);
		//Overloaded operator for taking in reference to account object and shifting
		//the left operand account's balance to the right operand's balance
		Account& operator>>(Account& otherAcc);


	};

	//Helper functions 

	//Overloaded operator to sum up the balances of the left and right operand
	//accounts and return that total value
	double operator+(const Account& left, const Account& right);
	//Overloaded operator for a left operand double value to add on the account
	// balance of the right operand object then return that total summed up value
	double operator+=(double& left, const Account& right);

}
#endif // SDDS_ACCOUNT_H_