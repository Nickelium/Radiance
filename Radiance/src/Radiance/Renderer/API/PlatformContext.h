#pragma once

#include "Radiance/Core/Locator.h"

namespace Radiance
{
	class Texture2D;
	class PlatformContext : public Service
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual Texture2D* GetBackBufferTexture() = 0;

		SERVICE_CLASS(PlatformContext)
	};
}
