#pragma once
#include "Core.h"

namespace Radiance
{
	class RAD_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};
}

Radiance::Application* CreateApplication();