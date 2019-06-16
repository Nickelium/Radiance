#include "pch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>


namespace Radiance
{
	Application::Application()
		: m_Running(true)
	{
		RAD_CORE_INFO("Creating Engine Application");
		m_Window = Window::Create();
	}

	Application::~Application()
	{
		RAD_CORE_INFO("Destroying Engine Application");
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->Update();
		}
	}

}