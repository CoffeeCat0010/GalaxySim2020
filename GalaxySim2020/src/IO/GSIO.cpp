#include "GSIO.h"
#include <iostream>
#include <fstream>

namespace IO
{

	std::string sourceToCStr(std::string path)
	{
		std::ifstream file;
		file = std::ifstream(path, std::ifstream::in);
		std::string result;
		char buffer;
		while (file.get(buffer))
		{
			result += buffer;
		}
		return result;
	}
}