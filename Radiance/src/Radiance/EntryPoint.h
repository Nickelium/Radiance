#pragma once

#ifdef RAD_PLATFORM_WINDOWS

//#include <vld.h>

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