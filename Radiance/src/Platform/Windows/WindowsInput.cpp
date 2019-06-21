#include "pch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Radiance/Application.h"

namespace Radiance
{
	Input* Input::s_Instance = nullptr;

	WindowsInput::WindowsInput(Application& _application)
		: m_Application(_application)
	{
	}

	bool WindowsInput::IsKeyPressedImpl(int _keyCode)
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Application.GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(pGLFWWindow, _keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto pGLFWWindow = static_cast<GLFWwindow*>(m_Application.GetWindow()->GetNativeWindow());
		double x, y;
		glfwGetCursorPos(pGLFWWindow, &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}

}