#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/API/RenderDevice.h"

namespace Radiance
{
	class Application 
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void Update(DataTime _time);
		void Render();

		virtual void OnEvent(Event& /*_event*/) {};
		
		void RootOnEvent(Event& _event);
		void CloseWindow();

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _layer);

		inline Window* GetWindow() const { return m_Window; }

	private:
		bool OnWindowClose(Event& _event);

		Window* m_Window;
		bool m_Running;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	};
}

Radiance::Application* CreateApplication();