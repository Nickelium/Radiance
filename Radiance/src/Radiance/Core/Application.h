#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Radiance/Events/ApplicationEvent.h"
#include "Radiance/ImGui/ImGuiLayer.h"
#include "Radiance/Core/GPUTimer.h"

#include "Radiance/Renderer/API/RenderDevice.h"

namespace Radiance
{
	class Application 
	{
	public:
		Application(const std::string& _name, unsigned int _width, unsigned int _height);
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
		inline GPUTimer* GetGPUTimer() const { return m_GPUTimer; }

	private:
		bool OnWindowClose(WindowCloseEvent& _event);
		bool OnWindowResize(WindowResizeEvent& _event);

		Window* m_Window;
		bool m_Running;
		bool m_Minimized;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		GPUTimer* m_GPUTimer;
	};
}

Radiance::Application* CreateApplication();