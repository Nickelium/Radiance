#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/RenderDevice.h"

namespace Radiance
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Render() = 0;
		
		void Run();
		
		void OnEvent(Event& _event);
		bool OnWindowClose(WindowCloseEvent& _event);

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _layer);

		Window* GetWindow();
	protected: 
		RenderDevice* m_RenderDevice;

	private:
		Window* m_Window;
		bool m_Running;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	};
}

Radiance::Application* CreateApplication();