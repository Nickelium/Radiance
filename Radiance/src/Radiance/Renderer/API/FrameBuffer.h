#pragma once

namespace Radiance
{
	class RTBuffer;
	class DepthBuffer;
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void SetSize(int _width, int _height) = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual RTBuffer* GetRTBuffer() const = 0;
		virtual DepthBuffer* GetDepthBuffer() const = 0;
	};
}
