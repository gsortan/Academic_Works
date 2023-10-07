/*****************************************************************************
< Workshop - #9 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: July-31-2023
	Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
*****************************************************************************/

#include "cstring.h"

namespace sdds
{
	void strCpy(char* des, const char* src)
	{
		int srcLength = strLen(src); //obtain string length for source string

		for (int i = 0; i < srcLength; i++)//Copy characters to destination string based on source string length
		{
			des[i] = src[i];
		}

		/*Input null terminator at source string length to wipe out and clear any
		remaining characters left in destination string*/
		des[srcLength] = '\0';
	}

	void strnCpy(char* des, const char* src, int len)
	{
		/*Loop based on len argument and only keep copying characters to destination string if
		it has not reached null terminator*/
		for (int i = 0; i < len; i++)
		{
			if (src[i] != '\0')
			{
				des[i] = src[i];
			}
		}

		//Only insert the null terminator if copied characters are less than the length
		if (strLen(src) < len)
		{
			des[strLen(src)] = '\0';
		}
	}

	int strCmp(const char* s1, const char* s2)
	{
		int s1Length = strLen(s1);
		int s2Length = strLen(s2);

		int compareValue = 0;
		int minStringLen = s1Length;

		/*Quick comparison check if string 1 is greater than string 2 in length
		or vice versa for return value*/

		if (s1Length > s2Length)
		{
			compareValue = 1;
		}
		else if (s1Length < s2Length)
		{
			compareValue = -1;
		}

		/*Loop through and check each indiviual character's value against each other
		if the string length of 1 and 2 are the same. If at any point they are different
		immediately exit loop and give return value otherwise strings are the same.*/

		for (int i = 0; i < minStringLen; i++)
		{
			if (s1[i] == s2[i])
			{
				compareValue = 0;
			}
			else if (s1[i] > s2[i])
			{
				compareValue = 1;
				i = minStringLen;
			}
			else
			{
				compareValue = -1;
				i = minStringLen;
			}
		}
		return compareValue; //return value if strings are the same or not
	}


	int strnCmp(const char* s1, const char* s2, int len)
	{
		int s1Length = strLen(s1);//Get string 1 length
		int s2Length = strLen(s2);//Get string 2 length 

		int compareValue = 0;
		int minStringLen = s1Length;

		/*Quick comparison check if string 1 is greater than string 2 in length
		or vice versa for return value and string 1 is less than len or string 2 is less than len*/
		if (s1Length < len && s1Length > s2Length)
		{
			compareValue = 1;
		}
		else if (s2Length < len && s1Length < s2Length)
		{
			compareValue = -1;
		}

		//First check of string 1 length and string 2 length are bigger than len
		/*Then loop through and check each indiviual character's value against each other
		if the string length of 1 and 2 are the same. If at any point they are different
		immediately exit loop and give return value otherwise strings are the same.*/

		if (s1Length >= len && s2Length >= len)
		{
			for (int i = 0; i < len; i++)
			{
				if (s1[i] == s2[i])
				{
					compareValue = 0;
				}
				else if (s1[i] > s2[i])
				{
					compareValue = 1;
					i = minStringLen;
				}
				else
				{
					compareValue = -1;
					i = minStringLen;
				}
			}
		}
		return compareValue; //return compare value if strings are the same or not
	}

	int strLen(const char* s)
	{
		int length = 0;
		//Count how many characters that string has up to the null terminating character 
		while (s[length] != '\0')
		{
			length++;
		}

		return length; //return total length of string
	}

	const char* strStr(const char* str1, const char* str2)
	{
		int countCheck = 0;

		const char* subString = nullptr; //set substring to null pointer

		int str1Len = strLen(str1); //Get string 1 length
		int str2Len = strLen(str2); //Get string 2 length 

		bool matching = false;

		/*Perform a double loop to find a matching substring within a string. */
		for (int i = 0; i < str1Len; i++)
		{
			//Check if the first character of substring matches the main string being searched
			if (str1[i] == str2[0])
			{
				countCheck = i;
				/*If the first character of main string does match substring then
				loop starting from that index to see if succeeding characters match substring
				if any of them do not, exit loop early and move onto next character in main string
				*/
				for (int j = 0; j < str2Len; j++)
				{
					if (str1[countCheck] == str2[j])
					{
						matching = true;
					}
					else
					{
						j = str2Len;
						matching = false;
					}
					countCheck++;
				}
				/*If there is a match found, exit the outer loopand set substring pointer to the
				address of that index*/
				if (matching)
				{
					subString = &str1[i];
					i = str1Len;
				}

			}
		}

		return subString; //return the substring or null pointer value if not found
	}


	void strCat(char* des, const char* src)
	{
		int desLen = strLen(des); //get destination string length
		int srcLen = strLen(src); //get source string length 

		//concatenate through loop and tack on characters to the end of the destination string
		for (int i = 0; i < srcLen; i++)
		{
			des[desLen + i] = src[i];
		}

		//calculate the maximum length of newly concatenated strnig 
		int maxLength = desLen + srcLen;

		/*Set the null terminator based on concatenated string length to wipeand clear any remaining
		left over characters in destination string*/
		des[maxLength] = '\0';
	}
}

