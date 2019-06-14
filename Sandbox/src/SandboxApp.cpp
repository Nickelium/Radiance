#include <Radiance.h>

class SandboxApplication : public Radiance::Application
{
public:
	SandboxApplication()
	{
		RAD_INFO("Creating Sandbox Application");
	}

	virtual ~SandboxApplication()
	{
		RAD_INFO("Destroying Sandbox Application");
	}
};


Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}