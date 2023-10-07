
#pragma once

class Misc
{
public:
	Misc();
	~Misc();

	static float clamp(const float &num, const float &min, const float &max);
	static float max(const float &num1, const float &num2);
	static float min(const float &num1, const float &num2);

private:

};