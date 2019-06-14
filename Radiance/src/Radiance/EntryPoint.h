#pragma once

#ifdef RAD_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	RAD_CORE_FATAL("LOGGING");
	RAD_INFO("Info");
	Radiance::Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif