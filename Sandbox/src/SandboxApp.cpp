#include <Radiance.h>

class SandboxApplication : public Radiance::Application
{
public:
	SandboxApplication()
	{
		printf("Creating Sandbox");
	}

	virtual ~SandboxApplication()
	{

	}
};


Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}