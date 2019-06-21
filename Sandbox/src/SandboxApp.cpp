#include <Radiance.h>

class ExampleLayer : public Radiance::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	virtual void OnUpdate()
	{
		//RAD_TRACE("{0}", "ExampleLayer : Update");
	}

	virtual void OnEvent(Radiance::Event& _event)
	{
		//RAD_TRACE("{0}", _event);
	}
};

class SandboxApplication : public Radiance::Application
{
public:
	SandboxApplication()
	{
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer);
		PushOverlay(new Radiance::ImGuiLayer(*this));
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