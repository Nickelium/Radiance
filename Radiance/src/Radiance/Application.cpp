#include "pch.h"
#include "Application.h"

/**
 * Doesn't contains gl includes due to GLFW_INCLUDE_NONE
 */
//#include <GLFW/glfw3.h>

/**
 * Glad still contains gl includes
 */
#include <glad/glad.h>

namespace Radiance
{
	Application::Application()
		: m_Running(true)
	{
		RAD_CORE_INFO("Creating Engine Application");
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_FN(OnEvent));
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
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
	
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(OnWindowClose));
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (_event.m_Handled)
				break;
			--it;
			(*it)->OnEvent(_event);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& /*_event*/)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* _layer)
	{
		m_LayerStack.PushLayer(_layer);
	}

	void Application::PushOverlay(Layer* _layer)
	{
		m_LayerStack.PushOverlay(_layer);
	}

}