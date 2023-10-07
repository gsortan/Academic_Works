//Essentially just a class used to get Cg shader programs which are stored in strings

#pragma once

#include <string>

class Cg
{
public:
	Cg();
	~Cg();

	//Vertex
	static std::string vColor;
	static std::string vDisplacementMap;
	static std::string vLighting;
	static std::string vFragLighting;
	static std::string vFragLightingWithNormalMap;
	static std::string vParticle;
	static std::string vParticle2; 

private:
};