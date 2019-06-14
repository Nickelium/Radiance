#pragma once
#include "Core.h"

namespace Radiance
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};
}

Radiance::Application* CreateApplication();