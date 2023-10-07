//SFT211_NEE Group 1
//MILESTONE 3 blackbox test for the capPercentage function
#include "pch.h"
#include "assert.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace blackboxtestTB11
{
	TEST_CLASS(blackboxTB11)
	{
		blackboxTB11()
		{
			Truck t;
		}
	public:
		//Test TB11 
		TEST_METHOD(capPercentageTest01)
		{
			double result = capPercentage(t);
			Assert::AreEqual(1.055f, result);
		}
	};
}
