#pragma once

#include "Radiance/Renderer/Shader.h"

namespace Radiance
{
	class GLShader : public Shader
	{
		using Location = int;
		using MapLocation = std::unordered_map<std::string, Location>;
	public:
		GLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~GLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetUniformFloat(const std::string& _name, float _val) override;
		virtual void SetUniformFloats(const std::string& _name, const std::vector<float>& _val) override;
		virtual void SetUniformInt(const std::string& _namee, int _value) override;
		virtual void SetUniformInts(const std::string& _name, const std::vector<int>& _val) override;
		virtual void SetUniformFloat2(const std::string& _name, const glm::vec2& _val) override;
		virtual void SetUniformFloat3(const std::string& _name, const glm::vec3& _val) override;
		virtual void SetUniformFloat4(const std::string& _name, const glm::vec4& _val) override;
		virtual void SetUniformMat(const std::string& _name, const glm::mat4& _val) override;

	private:
		Location GetLocation(const std::string& _name);
		
		MapLocation m_MapLocation;
		ID m_ID;

		static const Location s_InvalidLocation = -1;
	};
}