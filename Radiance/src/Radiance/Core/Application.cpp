#include "pch.h"
#include "Application.h"

#include "Radiance/Renderer/API/RenderCommand.h"
#include "Radiance/Renderer/API/RenderDevice.h"

namespace Radiance
{
	Application::Application()
		: m_Running(true)
	{
		RAD_CORE_INFO("Creating Engine Application");
		m_Window = Window::Create({"Radiance Engine", 1600, 900});
		m_Window->SetEventCallback(BIND_FN(Application::RootOnEvent));
		Locator::Set(RenderDevice::Create());
		m_ImGuiLayer = new ImGuiLayer(this);
		PushOverlay(m_ImGuiLayer);

		RenderCommand::EnableDepth(true);
		RenderCommand::EnableBlend(true);
	}

	Application::~Application()
	{
		RAD_CORE_INFO("Destroying Engine Application");
		Locator::Destroy();
		delete m_Window;
	}

	void Application::Run()
	{
		Timer timer;
		while (m_Running)
		{
			timer.Update();
			DataTime ts = timer.GetTimeStep();

			Update(ts);
			Render();
			m_Window->Update();
		}
	}

	void Application::Update(DataTime _time)
	{
		for (Layer* layer : m_LayerStack)
			layer->Update(_time);
	}

	void Application::Render()
	{
		for (Layer* layer : m_LayerStack)
			layer->Render();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->RenderGUI();
		m_ImGuiLayer->End();
	}

	void Application::RootOnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
	
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));

		OnEvent(_event);
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (_event.m_Handled)
				break;
			--it;
			(*it)->OnEvent(_event);
		}
	}

	bool Application::OnWindowClose(Event& /*_event*/)
	{
		CloseWindow();
		return true;
	}

	void Application::CloseWindow()
	{
		m_Running = false;
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