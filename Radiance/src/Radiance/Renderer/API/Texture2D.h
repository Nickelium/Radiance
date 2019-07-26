#pragma once

namespace Radiance
{
	class Texture2D
	{
	public:
		virtual ~Texture2D() = default;

		virtual void Bind(unsigned int _slot = 0) = 0;
		virtual void UnBind() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	};
}
