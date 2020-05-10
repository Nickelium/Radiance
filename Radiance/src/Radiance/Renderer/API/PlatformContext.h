#pragma once

namespace Radiance
{
	class PlatformContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
