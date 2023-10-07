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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Account.h"

using namespace std;
namespace sdds {

	//Set to empty state
	void Account::setEmpty() {
		m_number = -1;
		m_balance = 0.0;
	}
	// New account
	Account::Account() {
		m_number = 0;
		m_balance = 0.0;
	}

	//Constructor to set it to either an invalid state or using the parameters defined
	//if they are valid, set those values appropriately with them
	Account::Account(int number, double balance) {
		setEmpty();
		if (number >= 10000 && number <= 99999
			&& balance > 0) {
			m_number = number;
			m_balance = balance;
		}
	}

	//Display account to console 
	std::ostream& Account::display() const {
		if (*this) {
			cout << " ";
			cout << m_number;
			cout << " | ";
			cout.width(12);
			cout.precision(2);
			cout.setf(ios::right);
			cout.setf(ios::fixed);
			cout << m_balance;
			cout.unsetf(ios::right);
			cout << " ";
		}
		else if (~*this) {
			cout << "  NEW  |         0.00 ";
		}
		else {
			cout << "  BAD  |    ACCOUNT   ";
		}
		return cout;
	}

	//Overloaded boolean operator, check if valid account
	Account::operator bool() const
	{
		//If it's a 5 digit number for the account number and balance is not negative
		//it returns true as valid else false
		if (m_number >= 10000 && m_number <= 99999
			&& m_balance >= 0) {
			return true;
		}

		return false;
	}

	//Returns the account number through overloaded int operator
	Account::operator int() const
	{
		return m_number;
	}

	//Returns the account balance through overloaded double operator
	Account::operator double() const
	{
		return m_balance;
	}

	//Returns whether this account is a new one or not whether it's zero through 
	//through overloaded ~ operator
	bool Account::operator ~() const
	{
		if (m_number)
		{
			return false;
		}

		return true;
	}

	//Assignment operator overloaded to assign an account number to a new account 
	Account& Account::operator=(const int& accNum)
	{
		//See if it's a valid 5 digit number for the account and the account is new
		//If the account number passed in is valid but the account is not new don't do anything
		if (accNum >= 10000 && accNum <= 99999 && m_number == 0)
		{
			m_number = accNum;
		}

		//if the account number passed in is invalid set to empty state
		if (accNum < 10000 && accNum > 99999)
		{
			setEmpty();
		}

		return *this;
	}

	//Assignment operator overloaded to take in reference of account object 
	//to move the balance of this into a new account
	Account& Account::operator=(Account& otherAcc)
	{
		//Check if this is a new account and that the incoming account object
		//is also valid before transfering everything to this account
		//and emptying out the account passed in
		if (!m_number && otherAcc.m_number != -1)
		{
			m_number = otherAcc.m_number;
			m_balance = otherAcc.m_balance;
			otherAcc.m_balance = 0;
			otherAcc.m_number = 0;
		}

		return *this;
	}

	//Deposting into account with overloaded operator by double parameter 
	Account& Account::operator+=(double money) {
		//Check if this is a valid account and that the deposit number is
		//not a negative value before making changes 
		if (m_number != -1 && money >= 0) {
			m_balance += money;
		}
		return *this;
	}

	//Withdrawing from the account with overloaded operator by double parameter
	Account& Account::operator-=(double money) {
		//Check if this is a valid account and the withdrawal is not a negative
		//value. Also make sure the withdrawal is not bigger than the current
		//balance. 
		if (m_number != -1 && money >= 0 && money <= m_balance)
		{
			m_balance -= money;
		}
		return *this;
	}

	//Overloaded operator for taking in reference to account object and shifting
	//the right operand account's balance to the left operand's balance
	Account& Account::operator<<(Account& otherAcc)
	{
		//Do a self-check to make sure this is not the same object before
		//transfer of balance 
		if (this != &otherAcc)
		{
			m_balance += otherAcc.m_balance;
			otherAcc.m_balance = 0;
		}

		return *this;
	}

	//Overloaded operator for taking in reference to account object and shifting
   //the left operand account's balance to the right operand's balance
	Account& Account::operator>>(Account& otherAcc)
	{
		//Do a self-check to make sure this is not the same object before
		//transfer of balance 
		if (this != &otherAcc)
		{
			otherAcc.m_balance += m_balance;
			m_balance = 0;
		}

		return *this;
	}

	//Overloaded operator to sum up the balances of the left and right operand
	//accounts and return that total value
	double operator+(const Account& left, const Account& right)
	{
		double totalSum = 0;
		//Ensure that both accounts are valid 
		if (int(left) != -1 && int(right) != -1)
		{
			totalSum = double(left) + double(right);
		}

		return totalSum;
	}

	//Overloaded operator for a left operand double value to add on the account
	// balance of the right operand object then return that total summed up value
	double operator+=(double& left, const Account& right)
	{
		//Check to make sure the account is a valid one before operation
		if (int(right) != -1)
		{
			left += double(right);
		}

		return left;
	}


}