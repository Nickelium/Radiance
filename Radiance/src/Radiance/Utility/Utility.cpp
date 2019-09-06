#include "pch.h"
#include "Utility.h"

namespace Radiance
{
	std::string ReadFile(const std::string& _file)
	{
		std::fstream stream(_file);
		RAD_CORE_ASSERT(stream, "Invalid file : {0}", _file);
		return std::string ((std::istreambuf_iterator<char>(stream)),
			(std::istreambuf_iterator<char>()));
	}
}
