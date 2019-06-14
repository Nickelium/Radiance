#include "pch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Logger.h"


namespace Radiance
{
	Application::Application()
	{
		RAD_CORE_INFO("Creating Engine Application");
	}

	Application::~Application()
	{
		RAD_CORE_INFO("Destroying Engine Application");
	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		RAD_CORE_INFO(event);
		while (true)
			;
	}

}