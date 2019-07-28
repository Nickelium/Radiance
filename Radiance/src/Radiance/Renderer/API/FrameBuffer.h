#pragma once

namespace Radiance
{
	class Texture2D;
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Resize(int _width, int _height) = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual Texture2D* GetColorAttachment() const = 0;
		virtual Texture2D* GetDepthAtttachment() const = 0;
	};
}
