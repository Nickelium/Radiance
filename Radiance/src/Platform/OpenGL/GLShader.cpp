#include "pch.h"

#include "GLShader.h"

#include <glad/glad.h>

namespace Radiance
{
	GLShader::GLShader(const std::string& _vertexSource, const std::string& _fragmentSource)
	{
		Handle vertexShader = CreateShader(_vertexSource, ShaderType::VERTEX);
		Handle fragmentShader = CreateShader(_fragmentSource, ShaderType::FRAGMENT);

		m_Handle = CreateProgram(vertexShader, fragmentShader);

		QueryUniforms();
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(m_Handle);
	}

	void GLShader::Bind() const
	{
		glUseProgram(m_Handle);
	}

	void GLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void GLShader::SetUniform(const std::string& _name, float _val)
	{
		Location location = GetLocation(_name);

		//Bind();
		//glUniform1f(location, _val);
		
		/*
		glProgram doesn't require binding the shader, and according to 
		https://stackoverflow.com/questions/51648238/what-the-difference-between-glprogramuniform-and-gluniform
		can be efficienter than glUniform but require GL4.1+
		*/
		glProgramUniform1f(m_Handle, location, _val);
	}

	void GLShader::SetUniform(const std::string& _name, bool _val)
	{
		SetUniform(_name, (int)_val);
	}

	void GLShader::SetUniform(const std::string& _name, int _value)
	{
		Location location = GetLocation(_name);

		glProgramUniform1i(m_Handle, location, _value);
	}

	void GLShader::SetUniform(const std::string& _name, const std::vector<float>& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniform1fv(m_Handle, location, (int)_val.size(), _val.data());
	}

	void GLShader::SetUniform(const std::string& _name, const std::vector<int>& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniform1iv(m_Handle, location, (int)_val.size(), _val.data());
	}

	void GLShader::SetUniform(const std::string& _name, const glm::vec2& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniform2f(m_Handle, location, _val.x, _val.y);
	}

	void GLShader::SetUniform(const std::string& _name, const glm::vec3& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniform3f(m_Handle, location, _val.x, _val.y, _val.z);
	}

	void GLShader::SetUniform(const std::string& _name, const glm::vec4& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniform4f(m_Handle, location, _val.x, _val.y, _val.z, _val.w);
	}

	void GLShader::SetUniform(const std::string& _name, const glm::mat4& _val)
	{
		Location location = GetLocation(_name);

		glProgramUniformMatrix4fv(m_Handle, location, 1, false, &_val[0][0]);
	}

	Handle GLShader::CreateShader(const std::string& _source, ShaderType _type)
	{
		// Create an empty shader handle
		Handle shaderHandle = 0;
		switch (_type)
		{
			case ShaderType::VERTEX: shaderHandle = glCreateShader(GL_VERTEX_SHADER); break;
			case ShaderType::FRAGMENT: shaderHandle = glCreateShader(GL_FRAGMENT_SHADER); break;
			default: break;
		}

		// Send the shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = _source.c_str();
		glShaderSource(shaderHandle, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(shaderHandle);

		GLint isCompiled = 0;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderHandle, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderHandle);

			switch (_type)
			{
				case ShaderType::VERTEX: RAD_CORE_ERROR("Vertex Shader Compile Error:"); break;
				case ShaderType::FRAGMENT: RAD_CORE_ERROR("Fragment Shader Compile Error:"); break;
				default: break;
			}
			
			RAD_CORE_ERROR("  {0}", &infoLog[0]);
			RAD_CORE_ASSERT(false, "Compilation Failure");
			return 0;
		}

		return shaderHandle;
	}

	Handle GLShader::CreateProgram(unsigned int _vertexID, unsigned int _fragmentID)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		Handle programHandle = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(programHandle, _vertexID);
		glAttachShader(programHandle, _fragmentID);

		// Link our program
		glLinkProgram(programHandle);
		glValidateProgram(programHandle);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(programHandle, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programHandle, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(programHandle);
			// Don't leak shaders either.
			glDeleteShader(_vertexID);
			glDeleteShader(_fragmentID);

			RAD_CORE_ERROR("Program Linking Error:");
			RAD_CORE_ERROR("  {0}", &infoLog[0]);
			RAD_CORE_ASSERT(false, "Linking Failure");
			return 0;
		}

		// Always detach shaders after a successful link.
		// Might not want to detach shader to keep shader source to enable debug through nsight etc .. 
		glDetachShader(programHandle, _vertexID);
		glDetachShader(programHandle, _fragmentID);

		glDeleteShader(_vertexID);
		glDeleteShader(_fragmentID);

		return programHandle;
	}

	void GLShader::QueryUniforms()
	{
		int nbUniforms;
		glGetProgramiv(m_Handle, GL_ACTIVE_UNIFORMS, &nbUniforms);

		constexpr int size = 128;
		char name[size];
		for (int i = 0; i < nbUniforms; ++i)
		{
			int length;
			glGetActiveUniformName(m_Handle, i, size, &length, name);
			m_MapLocation[name] = glGetUniformLocation(m_Handle, name);
		}
	}

	GLShader::Location GLShader::GetLocation(const std::string& _name) const
	{
		auto res = m_MapLocation.find(_name);
		if (res == m_MapLocation.end())
		{
			RAD_CORE_WARN("Uniform var {0} not found/used", _name);
			return s_InvalidLocation;
		}

		return res->second;
	}
}
