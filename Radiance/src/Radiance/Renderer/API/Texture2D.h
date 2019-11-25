#pragma once

namespace Radiance
{
	enum class FormatUsage
	{
		COLOR_BUFFER,
		DEPTHSTENCIL_BUFFER
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Resize(int _width, int _height) = 0;
		virtual void SetData(void* _data, size_t _bytes) = 0;

		virtual void Bind(int _slot = 0) = 0;
		virtual void UnBind() = 0;

		virtual Handle GetHandle() const = 0;	
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
	};
}
