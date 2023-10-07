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

#ifndef SDDS_TEXT_H__
#define SDDS_TEXT_H__
#include <iostream>
namespace sdds {
	class Text {
		char* m_filename{};
		char* m_content{};
		int getFileLength()const;
	protected:
		const char& operator[](int index)const;
	public:

		Text(const char* filename = nullptr);
		Text(const Text& copyText);
		Text& operator=(const Text& copyText);
		virtual ~Text();

		void read();
		virtual void write(std::ostream& os)const;
	};
	std::ostream& operator<<(std::ostream& os, const Text& textObj);
}
#endif // !SDDS_TEXT_H__

