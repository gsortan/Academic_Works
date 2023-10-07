/*****************************************************************************
< Workshop - #10 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: August-07-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include "Collection.h"
#include <iostream>

#ifndef SDDS_SEARCHNLIST_H_
#define SDDS_SEARCHNLIST_H_

using namespace std;
namespace sdds
{
	/// <summary>
	/// Searches an array of template type with the template key value then
	/// adds the object appropriately from the array to the collection of template objects
	/// The == operator has to be defined properly for that object in order to do
	/// the comparison with the key template value for a search. 
	/// </summary>
	/// <typeparam name="T">The type of objects that are going to be stored in the 
	/// Collection template class</typeparam>
	/// <typeparam name="T2">The template type for the search key</typeparam>
	/// <param name="collObj">A reference to a Collection of templated objects</param>
	/// <param name="collectionList">An array of template types to search through that is the 
	/// same type as Collection type</param>
	/// <param name="num">Number of elements in array of objects</param>
	/// <param name="key">A template value to search for in array of objects</param>
	/// <returns>Returns true if the value is actually found with the key in the search</returns>
	template <typename T, typename T2>
	bool search(Collection<T>& collObj, T* collectionList, size_t num, T2 key)
	{
		bool foundFlag = false;

		for (int i = 0; i < num; i++)
		{
			if (collectionList[i] == key)
			{
				foundFlag = true;
				collObj.add(collectionList[i]);
			}
		}
		return foundFlag;
	}

	/// <summary>
	/// Displays elements of an array
	/// The insertion operator has to be properly defined if the type here
	/// were a composite object that uses this function
	/// </summary>
	/// <typeparam name="T">data type of array could be primitive or composite</typeparam>
	/// <param name="title">The title of the list to be printed</param>
	/// <param name="list">The array of templated objects to print</param>
	/// <param name="arraySz">The number of elements in the array</param>
	template <typename T>
	void listArrayElements(const char* title, const T* list, size_t arraySz)
	{
		cout << title << endl;

		for (int i = 0; i < arraySz; i++)
		{
			cout << i+1 << ": " << list[i] << endl;
		}

	}
}
#endif