#include "pch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Radiance/Application.h"
#include "Radiance/Window.h"

namespace Radiance
{
	std::unique_ptr<Input> Input::s_Instance;

	WindowsInput::WindowsInput(Window* _window)
		: m_Window(_window)
	{
	}

	bool WindowsInput::IsKeyPressedImpl(int _keyCode)
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		auto state = glfwGetKey(pGLFWWindow, _keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
		double x, y;
		glfwGetCursorPos(pGLFWWindow, &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}

}