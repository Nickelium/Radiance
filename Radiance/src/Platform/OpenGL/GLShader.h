#pragma once

#include "Radiance/Renderer/API/Shader.h"

namespace Radiance
{
	class GLShader : public Shader
	{
		enum class ShaderType
		{
			VERTEX = 0,
			FRAGMENT,
			NONE
		};

		using Location = int;
		using MapLocation = std::unordered_map<std::string, Location>;
	public:
		GLShader(const std::string& _vertexSource, const std::string& _fragmentSource);
		virtual ~GLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetUniform(const std::string& _name, bool _val);
		virtual void SetUniform(const std::string& _name, float _val) override;
		virtual void SetUniform(const std::string& _name, const std::vector<float>& _val) override;
		virtual void SetUniform(const std::string& _namee, int _value) override;
		virtual void SetUniform(const std::string& _name, const std::vector<int>& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec2& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec3& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec4& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::mat4& _val) override;

	private:
		Handle CreateShader(const std::string& _source, ShaderType _type);
		Handle CreateProgram(unsigned int _vertexID, unsigned int _fragmentID);

		Location GetLocation(const std::string& _name) const;
		
		mutable MapLocation m_MapLocation;
		Handle m_Handle;

		static const Location s_InvalidLocation = -1;
	};
}