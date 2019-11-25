#pragma once

#include "Radiance/Renderer/API/Texture2D.h"

#include <glad/glad.h>

namespace Radiance
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(const std::string& _filePath);
		//Create Empty Texture => For framebuffer etc..
		GLTexture2D(int _width, int _height, FormatUsage _formatUsage);
		virtual ~GLTexture2D();

		//Only meant for non filetexture, ex. for framebuffers
		virtual void Resize(int _width, int _height) override;

		virtual void SetData(void* _data, size_t _bytes) override;

		virtual void Bind(int _slot = 0) override;
		virtual void UnBind() override;

		inline virtual int GetWidth() const override { return m_Width; }
		inline virtual int GetHeight() const override { return m_Height; }

		inline virtual Handle GetHandle() const { return m_Handle; }

	private:
		void SetInternals();

		Handle m_Handle;

		std::string m_FilePath;
		int m_Width, m_Height, m_BPP;

		//GPU Format
		GLenum m_InternalFormat; 
		//Texture format read from
		GLenum m_DataFormat;
		GLenum m_ElementType;

		const FormatUsage m_FormatUsage;
	};
}
