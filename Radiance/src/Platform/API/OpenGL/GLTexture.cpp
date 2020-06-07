#include "pch.h"
#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Radiance
{
	//Currently only for colorbuffer
	GLTexture2D::GLTexture2D(const std::string& _filePath)
		:m_Handle(0), m_Width(0), m_Height(0), m_BPP(0),
		m_FilePath(_filePath), 
		m_FormatUsage(FormatUsage::COLOR_BUFFER)
	{
		stbi_set_flip_vertically_on_load(false);

		unsigned char* buffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);
		RAD_ASSERT(buffer, "Failed to load Texture2D from {0}", m_FilePath);

		SetInternals();

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
		glTexImage2D(GL_TEXTURE_2D, 0, m_GLInternalFormat, m_Width, m_Height, 0, m_GLDataFormat, m_GLElementType, buffer);
		//Alternative glTextureStorage2D &	glTextureSubImage2D
		//glTextureStorage2D is immutable, meaning can't resize later on
		//glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (buffer)
			stbi_image_free(buffer);
	}

	GLTexture2D::GLTexture2D(int _width, int _height, FormatUsage _formatUsage)
		:m_Handle(0), m_Width(_width), m_Height(_height), m_BPP(4),
		m_FilePath(),
		m_FormatUsage(_formatUsage)
	{
		SetInternals();

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, m_GLInternalFormat, m_Width, m_Height, 0, m_GLDataFormat, m_GLElementType, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void GLTexture2D::SetSize(int _width, int _height)
	{
		m_Width = _width;
		m_Height = _height;

		glBindTexture(GL_TEXTURE_2D, m_Handle);
		glTexImage2D(GL_TEXTURE_2D, 0, m_GLInternalFormat, m_Width, m_Height, 0, m_GLDataFormat, m_GLElementType, nullptr);
	}

	void GLTexture2D::SetData(void* _data, size_t /*_bytes*/)
	{
		//On this little endian architecture, stored as ABGR
		glBindTexture(GL_TEXTURE_2D, m_Handle);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_GLDataFormat, m_GLElementType, _data);
	}

	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &m_Handle);
	}

	void GLTexture2D::Bind(int _slot /*= 0*/)
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void GLTexture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture2D::SetInternals()
	{
		if (m_FormatUsage == FormatUsage::COLOR_BUFFER)
		{
			if (m_BPP == 3)
			{
				m_GLInternalFormat = GL_RGB8;
				m_GLDataFormat = GL_RGB;
			}
			else if (m_BPP == 4)
			{
				m_GLInternalFormat = GL_RGBA8;
				m_GLDataFormat = GL_RGBA;
			}
			m_GLElementType = GL_UNSIGNED_BYTE;
		}
		else if (m_FormatUsage == FormatUsage::DEPTHSTENCIL_BUFFER)
		{
			m_GLInternalFormat = GL_DEPTH24_STENCIL8;
			m_GLDataFormat = GL_DEPTH_STENCIL;
			m_GLElementType = GL_UNSIGNED_INT_24_8;
		}
	}

}