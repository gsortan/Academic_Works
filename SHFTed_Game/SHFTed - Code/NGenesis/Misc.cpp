#include "Misc.h"

Misc::Misc()
{
}

Misc::~Misc()
{
}

float Misc::clamp(const float &num, const float &min, const float &max)
{
	if (num <= min)
	{
		return min;
	}
	else if (num >= max)
	{
		return max;
	}
	else
	{
		return num;
	}
}

float Misc::max(const float &num1, const float &num2)
{
	if (num1 > num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}

float Misc::min(const float &num1, const float &num2)
{
	if (num1 > num2)
	{
		return num2;
	}
	else
	{
		return num1;
	}
}