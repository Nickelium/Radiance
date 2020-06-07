#pragma once

namespace Radiance
{
	class Texture2D;

	class RTBuffer
	{
	public:
		virtual Texture2D* GetTexture() const = 0;
		virtual void SetSize(int _width, int _height) = 0;
	};

	class DepthBuffer
	{
	public:
		virtual Texture2D* GetTexture() const = 0;
		virtual void SetSize(int _width, int _height) = 0;
	};
}
