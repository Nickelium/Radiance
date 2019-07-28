#include "pch.h"
#include "GLFrameBuffer.h"

#include "Radiance/Renderer/API/RenderDevice.h"
#include <glad/glad.h>

namespace Radiance
{

	GLFrameBuffer::GLFrameBuffer(int _width, int _height)
		: m_Width(_width), m_Height(_height), 
		m_Handle(0),
		m_ColorAttachment(nullptr), m_DepthAttachment(nullptr)
	{
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();
		m_ColorAttachment = renderDevice->CreateTexture2D(m_Width, m_Height, FormatUsage::COLOR_BUFFER);
		m_DepthAttachment = renderDevice->CreateTexture2D(m_Width, m_Height, FormatUsage::DEPTHSTENCIL_BUFFER);

		glGenFramebuffers(1, &m_Handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->GetHandle(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment->GetHandle(), 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			RAD_CORE_ERROR("Failed to create FrameBuffer");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLFrameBuffer::~GLFrameBuffer()
	{
		delete m_ColorAttachment;
		delete m_DepthAttachment;
	}

	void GLFrameBuffer::Resize(int _width, int _height)
	{
		if (m_Width == _width && m_Height == _height)
			return;

		m_Width = _width;
		m_Height = _height;

		m_ColorAttachment->Resize(m_Width, m_Height);
		m_DepthAttachment->Resize(m_Width, m_Height);
	}

	void GLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
		//Currently hard coded origin
		glViewport(0, 0, m_Width, m_Height);
	}

	void GLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Texture2D* GLFrameBuffer::GetColorAttachment() const
	{
		return m_ColorAttachment;
	}

	Texture2D* GLFrameBuffer::GetDepthAtttachment() const
	{
		return m_DepthAttachment;
	}

}