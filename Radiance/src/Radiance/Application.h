#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Radiance
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		
		void OnEvent(Event& _event);
		bool OnWindowClose(WindowCloseEvent& _event);

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _layer);

		Window* GetWindow();
	private:
		Window* m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	};
}

Radiance::Application* CreateApplication();