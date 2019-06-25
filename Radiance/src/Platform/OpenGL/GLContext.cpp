#include "pch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Radiance
{
	GLContext::GLContext(GLFWwindow* _windowHandle)
		: m_WindowHandle(_windowHandle)
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");	
	}

	void GLContext::Init()
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RAD_CORE_ASSERT(status, "Failed to initialize Glad");
		RAD_CORE_TRACE("{0}", "Glad Initialized");

		RAD_CORE_INFO("OpenGL GPU:");
		RAD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		RAD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		RAD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void GLContext::SwapBuffers()
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwSwapBuffers(m_WindowHandle);
	}

}