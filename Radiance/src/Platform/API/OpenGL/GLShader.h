#pragma once

#include "Radiance/Renderer/API/Shader.h"

namespace Radiance
{
	class GLShader : public Shader
	{
		using Location = int;
		using MapLocation = std::unordered_map<std::string, Location>;
	public:
		GLShader(const std::string& _vertexFile, const std::string& _fragmentFile);
		virtual ~GLShader();

		virtual const ShaderComponents& GetShaderComponents() const override;

		virtual void Load() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetUniform(const std::string& _name, bool _val);
		virtual void SetUniform(const std::string& _name, float _val) override;
		virtual void SetUniform(const std::string& _name, const std::vector<float>& _val) override;
		virtual void SetUniform(const std::string& _name, int _value) override;
		virtual void SetUniform(const std::string& _name, const std::vector<int>& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec2& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec3& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::vec4& _val) override;
		virtual void SetUniform(const std::string& _name, const glm::mat4& _val) override;

	private:
		ShaderComponent CompileShader(const std::string& _source, ShaderType _type);
		Handle LinkShaders(const ShaderComponents& _shaderComponents);
		
		void QueryUniforms();

		Location GetLocation(const std::string& _name) const;
		
		mutable MapLocation m_MapLocation;

		static const Location s_InvalidLocation = -1;

		ShaderComponents m_ShaderComponents;
		Handle m_Handle;
	};
}