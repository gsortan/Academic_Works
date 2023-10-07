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

#ifndef SDDS_CSTRING_H 
#define SDDS_CSTRING_H

namespace sdds
{
	// Copies the srouce character string into the destination
	void strCpy(char* des, const char* src);
	// Copies the source character string into the destination upto "len"
	// characters. The destination will be null terminated only if the number
	// of the characters copied is less than "len"
	void strnCpy(char* des, const char* src, int len);
	// Compares two C-strings 
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strCmp(const char* s1, const char* s2);
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strnCmp(const char* s1, const char* s2, int len);
	// returns the lenght of the C-string in characters
	int strLen(const char* s);
	// returns the address of first occurance of "str2" in "str1"
	// returns nullptr if no match is found
	const char* strStr(const char* str1, const char* str2);
	// Concantinates "src" C-string to the end of "des"
	void strCat(char* des, const char* src);
}

#endif // !SDDS_CSTRING_H_



