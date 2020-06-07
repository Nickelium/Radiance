#pragma once

#include "Radiance/Renderer/API/FrameBuffer.h"
#include "Radiance/Renderer/API/BufferView.h"

#include "GLRenderDevice.h"

#include "GLForwardDecl.h"
#include "GLInclude.h"

namespace Radiance
{
	class GLTexture2D;
	class GLRTBuffer : public RTBuffer
	{
	public:
		GLRTBuffer(int _width, int _height) 
			: m_Width(_width), m_Height(_height)
		{
			CreateInternals();
		}

		virtual Texture2D* GetTexture() const override { return m_Texture; }
		virtual void SetSize(int _width, int _height)
		{
			m_Width = _width;
			m_Height = _height;
			m_Texture->SetSize(m_Width, m_Height);
		}

		Handle GetHandle() const { return m_Texture->GetHandle(); }
	private:
		void CreateInternals()
		{
			GLRenderDevice* renderDevice = GetGLRenderDevice();
			m_Texture = renderDevice->CreateInternalTexture2D(m_Width, m_Height, FormatUsage::COLOR_BUFFER);
		}

		int m_Width, m_Height;
		GLTexture2D* m_Texture;
	};

	class GLDepthBuffer : public DepthBuffer
	{
	public:
		GLDepthBuffer(int _width, int _height) : m_Width(_width), m_Height(_height) { CreateInternals(); }

		virtual Texture2D* GetTexture() const override { return m_Texture; }
		virtual void SetSize(int _width, int _height)
		{
			m_Width = _width;
			m_Height = _height;
			m_Texture->SetSize(m_Width, m_Height);
		}

		Handle GetHandle() const { return m_Texture->GetHandle(); }
	private:
		void CreateInternals()
		{
			GLRenderDevice* renderDevice = GetGLRenderDevice();
			m_Texture = renderDevice->CreateInternalTexture2D(m_Width, m_Height, FormatUsage::DEPTHSTENCIL_BUFFER);
		}
		int m_Width, m_Height;
		GLTexture2D* m_Texture;
	};

	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(int _width, int _height);
		virtual ~GLFrameBuffer();

		virtual void SetSize(int _width, int _height) override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual RTBuffer* GetRTBuffer() const override { return m_RenderTargetBuffer; }
		virtual DepthBuffer* GetDepthBuffer() const override { return m_DepthBuffer; }

	private:
		int m_Width;
		int m_Height;

		Handle m_Handle;

		GLRTBuffer* m_RenderTargetBuffer;
		GLDepthBuffer* m_DepthBuffer;
	};
}
