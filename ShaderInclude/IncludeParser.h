#pragma once

#include <string>
#include <set>

#include <cassert>

inline std::string ReadFile(const std::string& _File)
{
	std::ifstream stream(_File);
	assert(!stream.fail(), _File);
	return std::string((std::istreambuf_iterator<char>(stream)),
		(std::istreambuf_iterator<char>()));
}

class IncludeParser
{
public:
	inline std::string Parse(const std::string& _File, std::set<std::string> _Includes = {}) const
	{
		if (_Includes.find(_File) != _Includes.end())
			return "";
		assert(_Includes.find(_File) == _Includes.end());
		_Includes.insert(_File);
		return ParseSource(ReadFile(_File), _Includes);
	}

	inline std::string ParseSource(const std::string& _Source, const std::set<std::string>& _Includes) const
	{
		std::string currentSource = _Source;
		size_t found;
		size_t offset = 0;
		while ((found = currentSource.find("#include", offset)) != std::string::npos)
		{
			std::string includeLine = currentSource.substr(found);
			size_t quoteStart = includeLine.find("\"");
			size_t quoteLength = includeLine.substr(quoteStart + 1).find("\"");
			assert(quoteStart != std::string::npos);
			assert(quoteLength != std::string::npos);
			std::string includeFile = includeLine.substr(quoteStart + 1, quoteLength);

			std::string firstSourcePart = currentSource.substr(0, found);
			std::string secondSourcePart = currentSource.substr(found + quoteStart + 1 + quoteLength + 1);

			std::string includeSource = Parse(includeFile, _Includes);
			currentSource = firstSourcePart + includeSource + secondSourcePart;

			offset =+ firstSourcePart.length() + includeSource.length();
		}
		return currentSource;
	}
};
