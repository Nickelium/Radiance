#pragma once

#include "Window.h"

namespace Radiance
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	private:
		Window* m_Window;
		bool m_Running;
	};
}

Radiance::Application* CreateApplication();