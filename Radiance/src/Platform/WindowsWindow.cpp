#include "pch.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>


//#include "Radiance/Events/ApplicationEvent.h"
//#include "Radiance/Events/MouseEvent.h"
//#include "Radiance/Events/KeyEvent.h"

//#include "Platform/OpenGL/OpenGLContext.h"

namespace Radiance
{
	static bool s_GLFWInitialized = false;

	//static void GLFWErrorCallback(int error, const char* description)
	//{
	//	RAD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	//}

	Window* Window::Create(const WindowDesc& _desc)
	{
		return new WindowsWindow(_desc);
	}

	WindowsWindow::WindowsWindow(const WindowDesc& _desc)
	{
		Init(_desc);
	}

	WindowsWindow::~WindowsWindow()
	{
		Destroy();
	}

	void WindowsWindow::Init(const WindowDesc& _desc)
	{
		m_Data.Title = _desc.Title;
		m_Data.Width = _desc.Width;
		m_Data.Height = _desc.Height;

		RAD_CORE_INFO("Creating window {0} ({1}, {2})", _desc.Title, _desc.Width, _desc.Height);

		//Initialize once, system might have multiple windows
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			RAD_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)_desc.Width, (int)_desc.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Destroy()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool _enabled)
	{
		if (_enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = _enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}