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

		//TODO some magic virtual + template ? although trivially combining is not allowed in C++
		// doing via overloading, but less verbose
		virtual void SetUniform(const std::string& _name, bool _val) = 0;
		virtual void SetUniform(const std::string& _name, float _val) = 0;
		virtual void SetUniform(const std::string& _name, const std::vector<float>& _val) = 0;
		virtual void SetUniform(const std::string& _name, int _value) = 0;
		virtual void SetUniform(const std::string& _name, const std::vector<int>& _val) = 0;
		virtual void SetUniform(const std::string& _name, const glm::vec2& _val) = 0;
		virtual void SetUniform(const std::string& _name, const glm::vec3& _val) = 0;
		virtual void SetUniform(const std::string& _name, const glm::vec4& _val) = 0;
		virtual void SetUniform(const std::string& _name, const glm::mat4& _val) = 0;
	};
}