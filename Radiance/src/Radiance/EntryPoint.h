#pragma once

#include "Radiance/Defines.h"
#include "Radiance/Settings.h"

#ifdef RAD_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	RAD_CORE_INFO("Booting Engine");
	Radiance::Application* app = CreateApplication();
	app->Run();
	delete app;
	RAD_CORE_INFO("Closing Engine");
	return 0;
}
#endif