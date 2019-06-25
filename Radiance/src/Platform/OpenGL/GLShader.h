#pragma once

#include "Radiance/Renderer/Shader.h"

namespace Radiance
{
	class GLShader : public Shader
	{
	public:
		GLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~GLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		ID m_ID;
	};
}