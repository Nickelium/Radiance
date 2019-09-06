#pragma once

#include "pch.h"

namespace Radiance
{
	enum class ShaderType
	{
		VERTEX = 0,
		FRAGMENT,
		GEOMETRY,
		NONE
	};

	struct ShaderComponent
	{
		ShaderType type;
		std::string fileName;
		Handle handle;
	};

	using ShaderComponents = std::vector<ShaderComponent>;

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Load() = 0;

		virtual const ShaderComponents& GetShaderComponents() const = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

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