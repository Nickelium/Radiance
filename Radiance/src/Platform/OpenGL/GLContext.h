#pragma once

#include "Radiance/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Radiance
{
	class GLContext : public GraphicsContext
	{
	public:
		GLContext(GLFWwindow* _windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}