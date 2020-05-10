#include <iostream>
#include <string>
#include <fstream>

#include "IncludeParser.h"



int main(int argc, char** argv)
{
	IncludeParser parser;
	std::string parsedFile = parser.Parse("shader.glsl");
	std::cout << "\n -- PARSED FILE -- \n";
	std::cout << parsedFile;
	return 0;
}