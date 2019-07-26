#pragma once

#include "Radiance/Renderer/API/Texture2D.h"

namespace Radiance
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(const std::string& _filePath);
		virtual ~GLTexture2D();

		virtual void Bind(unsigned int _slot = 0) override;
		virtual void UnBind() override;

		inline virtual int GetWidth() const override { return m_Width; }
		inline virtual int GetHeight() const override { return m_Height; }
	private:
		Handle m_Handle;
		std::string m_FilePath;
		unsigned char* m_Buffer;
		int m_Width, m_Height, m_BPP;
	};
}
