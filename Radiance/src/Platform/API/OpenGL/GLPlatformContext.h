#pragma once

#include "Radiance/Renderer/API/PlatformContext.h"

struct GLFWwindow;

namespace Radiance
{
	class GLPlatformContext : public PlatformContext
	{
	public:
		GLPlatformContext(GLFWwindow* _windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}