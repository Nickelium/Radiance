#pragma once

#include "pch.h"

namespace Radiance
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};
}