#include "pch.h"
#include "WindowsWindow.h"

#include "Radiance/Events/ApplicationEvent.h"
#include "Radiance/Events/MouseEvent.h"
#include "Radiance/Events/KeyEvent.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

//#include "Platform/OpenGL/OpenGLContext.h"

namespace Radiance
{
	static bool s_GLFWInitialized = false;

	//None member function
	void GLFWErrorCallback(int _error, const char* _description)
	{
		RAD_CORE_ERROR("GLFW Error ({0}): {1}", _error, _description);
	}

	Window* Window::Create(const WindowDesc& _desc)
	{
		return new WindowsWindow(_desc);
	}

	WindowsWindow::WindowsWindow(const WindowDesc& _desc)
	{
		Init(_desc);
		Input::s_Instance = std::make_unique<WindowsInput>(this);
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
			RAD_CORE_ASSERT(success, "Failed to intialize GLFW");
			RAD_CORE_TRACE("{0}", "GLFW Initialized");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)_desc.Width, (int)_desc.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RAD_CORE_ASSERT(status, "Failed to initialize Glad");
		RAD_CORE_TRACE("{0}", "Glad Initialized");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	
		// Set GLFW Callback functions
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* _window, int _width, int _height)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			data.Width = _width;
			data.Height = _height;

			WindowResizeEvent event(_width, _height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window,
		[](GLFWwindow* _window)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* _window, int _key, int /*_scancode*/, int _action, int /*_mods*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			switch (_action)
			{
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(_key);
					data.EventCallback(event);
					break;
				}
				case GLFW_PRESS:
				{
					KeyPressedEvent event(_key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(_key, 1);
					data.EventCallback(event);
					break;
				}
				default:break;
			}
		});

		glfwSetCharCallback(m_Window,
			[](GLFWwindow* _window, unsigned int _ch)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			KeyTypedEvent event(_ch);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* _window, int _button, int _action, int /*_mod*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			switch (_action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(_button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(_button);
				data.EventCallback(event);
				break;
			}
			default:break;
			}
		});

		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* _window, double _xScroll, double /*yScroll*/)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);

			MouseScrolledEvent event(static_cast<float>(_xScroll));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, 
			[](GLFWwindow* _window, double _x, double _y)
		{
			auto pUserPtr = glfwGetWindowUserPointer(_window);
			auto& data = *reinterpret_cast<WindowData*>(pUserPtr);
			MouseMovedEvent event(static_cast<float>(_x), static_cast<float>(_y));
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		s_GLFWInitialized = false;
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