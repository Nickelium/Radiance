#include "pch.h"
#include "Utility.h"

namespace Radiance
{
	class IncludeParser
	{
	public:
		inline std::string Parse(const std::string& _File, std::set<std::string>& _Includes) const
		{
			if (_Includes.find(_File) != _Includes.end())
				return "";
			assert(_Includes.find(_File) == _Includes.end());
			_Includes.insert(_File);
			return ParseSource(ReadFile(_File), _Includes);
		}

		inline std::string ParseSource(const std::string& _Source, std::set<std::string>& _Includes) const
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

				offset = +firstSourcePart.length() + includeSource.length();
			}
			return currentSource;
		}
	};

	std::string ReadFile(const std::string& _file)
	{
		std::fstream stream(_file);
		RAD_CORE_ASSERT(stream, "Invalid file : {0}", _file);
		return std::string ((std::istreambuf_iterator<char>(stream)),
			(std::istreambuf_iterator<char>()));
	}

	std::string Preprocess(const std::string& _source)
	{
		IncludeParser parser;
		std::set<std::string> includes;
		return parser.Parse(_source, includes);
	}

	
}
