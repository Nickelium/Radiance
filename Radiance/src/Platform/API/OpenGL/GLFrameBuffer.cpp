#include "pch.h"
#include "GLFrameBuffer.h"

#include "Radiance/Renderer/API/RenderDevice.h"
#include "Radiance/Renderer/API/DeviceContext.h"
#include "GLRenderDevice.h"
#include <glad/glad.h>

namespace Radiance
{
	GLFrameBuffer::GLFrameBuffer(int _width, int _height)
		: m_Width(_width), m_Height(_height), 
		m_Handle(0),
		m_RenderTargetBuffer(nullptr), m_DepthBuffer(nullptr)
	{
		GLRenderDevice* renderDevice = GetGLRenderDevice();
		m_RenderTargetBuffer = renderDevice->CreateInternalRTBuffer(m_Width, m_Height);
		m_DepthBuffer = renderDevice->CreateInternalDepthBuffer(m_Width, m_Height);

		glGenFramebuffers(1, &m_Handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTargetBuffer->GetHandle(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer->GetHandle(), 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			RAD_CORE_ERROR("Failed to create FrameBuffer");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLFrameBuffer::~GLFrameBuffer()
	{
		delete m_RenderTargetBuffer;
		delete m_DepthBuffer;
	}

	void GLFrameBuffer::SetSize(int _width, int _height)
	{
		if (m_Width == _width && m_Height == _height
			|| (_width <= 0 || _height <= 0))
			return;

		m_Width = _width;
		m_Height = _height;

		m_RenderTargetBuffer->SetSize(m_Width, m_Height);
		m_DepthBuffer->SetSize(m_Width, m_Height);

		//TODO move this elsewhere
		Locator::Get<DeviceContext>()->SetViewport(0, 0, m_Width, m_Height);
	}

	void GLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
	}

	void GLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}