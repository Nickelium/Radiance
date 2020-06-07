#include "pch.h"
#include "Application.h"

#include "Radiance/Renderer/API/DeviceFactory.h"
#include "Radiance/Renderer/API/RenderDevice.h"
#include "Radiance/Renderer/API/DeviceContext.h"
#include "Radiance/Resources/ResourceLibrary.h"

#include "Radiance/Core/GPUTimer.h"


namespace Radiance
{
	Application::Application(const std::string& _name, unsigned int _width, unsigned int _height)
		: m_Running(true), m_Minimized(false)
	{
		RAD_CORE_INFO("Creating Engine Application");

		Locator::Set(DeviceFactory::Create());

		Locator::Set(Locator::Get<DeviceFactory>()->CreateRenderDevice());
		Locator::Set(Locator::Get<DeviceFactory>()->CreateDeviceContext());

		m_Window = Window::Create({_name, _width, _height});
		m_Window->SetEventCallback(BIND_FN(Application::RootOnEvent));

		Locator::Set(new ResourceLibrary);

		//m_GPUTimer = Locator::Get<RenderDevice>()->CreateGPUTimer();

		//m_ImGuiLayer = new ImGuiLayer(this);
		//PushOverlay(m_ImGuiLayer);

/*		Locator::Get<DeviceContext>()->EnableDepth(true);
		Locator::Get<DeviceContext>()->EnableBlend(true);	*/	
	}

	Application::~Application()
	{
		RAD_CORE_INFO("Destroying Engine Application");
		// Destroy factory as last
		Locator::Destroy();
		delete m_Window;
		delete m_GPUTimer;
	}

	void Application::Run()
	{
		Timer timer;
		ResourceLibrary* resLib = Locator::Get<ResourceLibrary>();
		RAD_CORE_ASSERT(resLib, "Resource Library Service is nullptr");

		while (m_Running)
		{
			timer.Update();
			DataTime ts = timer.GetTimeStep();

			resLib->Update();

			Update(ts);

			Render();

			//m_GPUTimer->Update();
			m_Window->Update();
		}
	}

	void Application::Update(DataTime _time)
	{
		if (m_Minimized)
			return;

		for (Layer* layer : m_LayerStack)
			layer->Update(_time);
	}

	void Application::Render()
	{
		if(!m_Minimized)
			for (Layer* layer : m_LayerStack)
				layer->Render();

		if (m_ImGuiLayer)
		{
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->RenderGUI();
			m_ImGuiLayer->End();
		}
	}

	void Application::RootOnEvent(Event& _event)
	{
		EventDispatcher dispatcher(_event);
	
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Application::OnWindowResize));

		OnEvent(_event);
	
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
		CloseWindow();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& _event)
	{
		if (_event.GetWidth() == 0 || _event.GetHeight() == 0)
			m_Minimized = true;
		else m_Minimized = false;

		return false;
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