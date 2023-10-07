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

#ifndef SDDS_HTMLTEXT_H__
#define SDDS_HTMLTEXT_H__
#include "Text.h"
namespace sdds {
	class HtmlText : public Text {
		char* m_title{};
	public:
		HtmlText(const char* filename = nullptr, const char* title = nullptr);
		HtmlText(const HtmlText& copy);
		HtmlText& operator=(const HtmlText& copy);
		~HtmlText();

		void write(std::ostream& os)const;

	};
}
#endif // !SDDS_HTMLTEXT_H__
