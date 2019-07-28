#pragma once

#include "Radiance/Renderer/API/FrameBuffer.h"

namespace Radiance
{
	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(int _width, int _height);
		virtual ~GLFrameBuffer();

		virtual void Resize(int _width, int _height) override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual Texture2D* GetColorAttachment() const override;
		virtual Texture2D* GetDepthAtttachment() const override;


	private:
		int m_Width;
		int m_Height;

		Handle m_Handle;

		Texture2D* m_ColorAttachment;
		Texture2D* m_DepthAttachment;
	};
}
