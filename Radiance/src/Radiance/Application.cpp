#include "pch.h"
#include "Application.h"

namespace Radiance
{
	Application::Application()
		: m_Running(true)
	{
		RAD_CORE_INFO("Creating Engine Application");
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
		m_RenderDevice = RenderDevice::Create();
		m_ImGuiLayer = new ImGuiLayer(this);
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		RAD_CORE_INFO("Destroying Engine Application");

		delete m_Window;
		delete m_RenderDevice;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Render();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
	
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
	
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
		_layer->OnAttach();
	}

	void Application::PushOverlay(Layer* _layer)
	{
		m_LayerStack.PushOverlay(_layer);
		_layer->OnAttach();
	}

	Window* Application::GetWindow()
	{
		return m_Window; 
	}

}