/*****************************************************************************
< Workshop - #2 (Part - 1)>
Full Name : Gordon Tan
Student ID#  : 147206221
	Email : gtan16@myseneca.ca
	Section : NAA
	Date: May-25-2023
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
		int srcLength = strLen(src);

		for (int i = 0; i < srcLength; i++)
		{
			des[i] = src[i];
		}
		des[srcLength] = '\0';
	}

	void strnCpy(char* des, const char* src, int len)
	{
		for (int i = 0; i < len; i++)
		{
			des[i] = src[i];
		}

	}

	int strCmp(const char* s1, const char* s2)
	{
		int s1Length = strLen(s1);
		int s2Length = strLen(s2);

		int compareValue = 0;
		int minStringLen = s1Length;

		if (s1Length > s2Length)
		{
			compareValue = 1;
		}
		else if (s1Length < s2Length)
		{
			compareValue = -1;
		}

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
		return compareValue;
	}


	int strnCmp(const char* s1, const char* s2, int len)
	{
		int s1Length = strLen(s1);
		int s2Length = strLen(s2);

		int compareValue = 0;
		int minStringLen = s1Length;

		if (s1Length < len && s1Length > s2Length)
		{
			compareValue = 1;
		}
		else

			if (s2Length < len && s1Length < s2Length)
			{
				compareValue = -1;
			}

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
		return compareValue;
	}

	int strLen(const char* s)
	{
		int length = 0;

		while (s[length] != '\0')
		{
			length++;
		}

		return length;
	}

	const char* strStr(const char* str1, const char* str2)
	{
		int countCheck = 0;

		const char* subString = nullptr;

		int str1Len = strLen(str1);
		int str2Len = strLen(str2);

		bool matching = false;

		for (int i = 0; i < str1Len; i++)
		{
			if (str1[i] == str2[0])
			{
				countCheck = i;
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
				if (matching)
				{
					subString = &str1[i];
					i = str1Len;
				}

			}
		}

		return subString;
	}


	void strCat(char* des, const char* src)
	{
		int desLen = strLen(des);
		int srcLen = strLen(src);

		for (int i = 0; i < srcLen; i++)
		{
			des[desLen + i] = src[i];
		}
		int maxLength = desLen + srcLen;

		des[maxLength] = '\0';
	}
}

