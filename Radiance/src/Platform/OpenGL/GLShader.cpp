#include "pch.h"

#include "GLShader.h"

#include <glad/glad.h>

namespace Radiance
{

	GLShader::GLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			RAD_CORE_ERROR("Vertex Shader Compile Error:");
			RAD_CORE_ERROR("  {0}", &infoLog[0]);
			RAD_CORE_ASSERT(false, "Compilation Failure");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar *)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RAD_CORE_ERROR("Fragment Shader Compile Error:");
			RAD_CORE_ERROR("  {0}", &infoLog[0]);
			RAD_CORE_ASSERT(false, "Compilation Failure");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ID = glCreateProgram();
		GLuint program = m_ID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);
		glValidateProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RAD_CORE_ERROR("Program Linking Error:");
			RAD_CORE_ERROR("  {0}", &infoLog[0]);
			RAD_CORE_ASSERT(false, "Linking Failure");
			return;
		}

		// Always detach shaders after a successful link.
		// Might not want to detach shader to keep shader source to enable debug through nsight etc .. 
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(m_ID);
	}

	void GLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void GLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void GLShader::SetUniformFloat(const std::string& _name, float _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");

		//Bind();
		//glUniform1f(location, _val);
		
		/*glProgram doesn't require binding the shader, and according to 
		https://stackoverflow.com/questions/51648238/what-the-difference-between-glprogramuniform-and-gluniform
		can be efficienter than glUniform but require GL4.1+
		*/
		glProgramUniform1f(m_ID, location, _val);
	}

	void GLShader::SetUniformFloats(const std::string& _name, const std::vector<float>& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform1fv(m_ID, location, (int)_val.size(), _val.data());
	}

	void GLShader::SetUniformInt(const std::string& _name, int _value)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform1i(m_ID, location, _value);
	}

	void GLShader::SetUniformInts(const std::string& _name, const std::vector<int>& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform1iv(m_ID, location, (int)_val.size(), _val.data());
	}

	void GLShader::SetUniformFloat2(const std::string& _name, const glm::vec2& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform2f(m_ID, location, _val.x, _val.y);
	}

	void GLShader::SetUniformFloat3(const std::string& _name, const glm::vec3& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform3f(m_ID, location, _val.x, _val.y, _val.z);
	}

	void GLShader::SetUniformFloat4(const std::string& _name, const glm::vec4& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniform4f(m_ID, location, _val.x, _val.y, _val.z, _val.w);
	}

	void GLShader::SetUniformMat(const std::string& _name, const glm::mat4& _val)
	{
		Location location = GetLocation(_name);
		RAD_CORE_ASSERT(location != s_InvalidLocation, "Invalid Uniform Location");
		glProgramUniformMatrix4fv(m_ID, location, 1, false, &_val[0][0]);
	}

	GLShader::Location GLShader::GetLocation(const std::string& _name)
	{
		auto result = m_MapLocation.find(_name);
		int location = -1;
		if (result != m_MapLocation.end())
			return location = result->second;
		return m_MapLocation[_name] = glGetUniformLocation(m_ID, _name.c_str());
	}

}