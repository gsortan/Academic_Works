#pragma once

#include <string>
#include <sstream>
#include <math.h>

#define NG_PI 3.14159
#define mRadToDeg(radians) ((radians) * (180 / NG_PI)) //Macro
#define mDegToRad(degrees) ((degrees) * (NG_PI / 180)) //Macro

class Quaternion; //wtfmagic
class Matrix;

class Conversion
{
public:
	Conversion();
	~Conversion();

	//String and Char Arrays
	static std::string intToString(int num);
	static std::string floatToString(float num);
	static int stringToInt(const char* string);
	static float stringToFloat(const char* string);
	static char* numToCharArray(float &num);	
	static char* stringToCharArray(std::string string);
	static void combineCharArrays(char* array1, char* array2);

	//Quaternion and Matrix Conversion
	static Quaternion matrixToQuaternion(Matrix &matrix);
	static Matrix quaternionToMatrix(Quaternion &quaternion);

private:
};