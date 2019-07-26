#include "pch.h"
#include "GLTexture2D.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Radiance
{
	GLTexture2D::GLTexture2D(const std::string& _filePath)
		:m_Handle(0), m_Width(0), m_Height(0), m_BPP(0),
		m_Buffer(nullptr), m_FilePath(_filePath)
	{
		stbi_set_flip_vertically_on_load(1);

		m_Buffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_Buffer)
			stbi_image_free(m_Buffer);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &m_Handle);
	}

	void GLTexture2D::Bind(unsigned int _slot /*= 0*/)
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void GLTexture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}