#pragma once

#ifdef RAD_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	Radiance::Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif