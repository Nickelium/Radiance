#pragma once

#include "pch.h"

//Read file into string
namespace Radiance
{
	std::string ReadFile(const std::string& _file);
	std::string Preprocess(const std::string& _source);
}
