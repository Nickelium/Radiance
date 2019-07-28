#pragma once

namespace Radiance
{
	enum class FormatUsage
	{
		COLOR_BUFFER,
		DEPTHSTENCIL_BUFFER
	};

	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;

		virtual void Bind(unsigned int _slot = 0) = 0;
		virtual void UnBind() = 0;

		virtual void Resize(int _width, int _height) = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual Handle GetHandle() const = 0;
	};
}
