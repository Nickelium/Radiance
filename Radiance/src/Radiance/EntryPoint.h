#pragma once

#include "Radiance/Defines.h"
#include "Radiance/Settings.h"

void CommonMain()
{
	RAD_CORE_INFO("Booting Engine");
	Radiance::Application* app = CreateApplication();
	app->Run();
	delete app;
	RAD_CORE_INFO("Closing Engine");
}

#ifdef RAD_PLATFORM_WINDOWS
#include <Windows.h>

int main(int argc, char** argv)
{
	#ifdef SHOW_CONSOLE
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	#else
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	#endif
	CommonMain();
	return 0;
}
//#endif

#endif