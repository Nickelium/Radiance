#pragma once

namespace Radiance
{
	class Texture2D;

	class RenderTargetBuffer
	{
	public:
		virtual Texture2D* GetTexture() const = 0;
	};

	class DepthBuffer
	{
	public:
		virtual Texture2D* GetTexture() const = 0;
	};
}
