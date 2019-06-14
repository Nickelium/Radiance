#include "Application.h"

#include <stdio.h>

namespace Radiance
{
	Application::Application()
	{
		printf("-- Radiance Engine --\n");
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
			;
	}

}